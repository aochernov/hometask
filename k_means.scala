import scala.util.Random
import scala.annotation.tailrec
import scala.collection._

class Point(val x: Double, val y: Double) {
  def distance(point: Point): Double = {
    val dif_x = point.x - x
    val dif_y = point.y - y
    dif_x * dif_x + dif_y * dif_y
  }
  def printpoint(): Unit = {
    println(x, y)
  }
  def equal(point: Point): Boolean = {
    (point.x == x) && (point.y == y)
  }
}

object k_means {
  def generatePoints(k: Int, num: Int): Seq[Point] = {
    val random = scala.util.Random
    val max = Math.abs(k)
    val min = -max
    var sequence: Seq[Point] = Seq()
    for (i <- 0 until num) {
      val x = min + (max - min) * random.nextDouble
      val y = min + (max - min) * random.nextDouble
      sequence = sequence :+ new Point(x, y)
    }
    sequence
  }
  def initializeMeans(k: Int, points: Seq[Point]): Seq[Point] = {
    val random = scala.util.Random
    var var_points = points
    var sequence: Seq[Point] = Seq()
    var l = points.length
    for (i <- 0 until k) {
      val num = Math.abs(random.nextInt % l)
      sequence = sequence :+ var_points.drop(num).head
      l = l - 1
      var_points = var_points.take(num) ++ var_points.drop(num + 1)
    }
    sequence
  }
  def findClosest(p: Point, means: GenSeq[Point]): Point = {
    var closest = means(0)
    var min_dist = closest.distance(p)
    for (i <- 0 until means.length) {
      val dist = means(i).distance(p)
      if (dist < min_dist) {
        min_dist = dist
        closest = means(i)
      }
    }
    closest
  }
  def classify(points: GenSeq[Point], means: GenSeq[Point]): GenSeq[(Point, GenSeq[Point])] = {
    val closest = points.groupBy(findClosest(_, means))
    val empty = points.take(0)
    means.map(i => i -> closest.getOrElse(i, empty))
  }
  def findAverage(oldMean: Point, points: GenSeq[Point]): Point = {
    if (points.isEmpty) {
      oldMean
    }
    else {
      val x = points.foldLeft(0.0)((num, P) => num + P.x)
      val y = points.foldLeft(0.0)((num, P) => num + P.y)
      val length = points.length
      new Point(x / length, y / length)
    }
  }
  def update(classified: GenSeq[(Point, GenSeq[Point])]): GenSeq[Point] = {
    classified.map(i => findAverage(i._1, i._2))
  }
  def converged(eta: Double)(oldMeans: GenSeq[Point], newMeans: GenSeq[Point]): Boolean = {
    val means = oldMeans.zip(newMeans)
    means.forall(i => i._1.distance(i._2) < eta)
  }
  @tailrec
  final def kMeans(points: GenSeq[Point], means: GenSeq[Point], eta: Double): GenSeq[Point] = {
    val newMeans = update(classify(points, means))
    if (converged(eta)(means, newMeans)) {
      newMeans
    }
    else {
      kMeans(points, newMeans, eta)
    }
  }
}