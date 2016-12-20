import org.scalatest.FunSuite

class unit_tests extends FunSuite {
  test("K-means") {
    val seq = Seq(new Point(5, 1), new Point(7, 3), new Point(7, 4), new Point(3, 4), new Point(4, 5), new Point(5, 5), new Point(8, 5), new Point(3, 6), new Point(4, 7), new Point(3, 8))
    val means = Seq(new Point(3, 8), new Point(8, 5))
    val res = k_means.kMeans(seq, means, 1)
    assert(res(0).x < 4 && res(0).x > 3 && res(0).y < 6.5 && res(0).y > 5.5)
    assert(res(1).x < 6.5 && res(1).x > 5.5 && res(1).y < 4.5 && res(1).y > 3.5)
  }
  test("Closest") {
    val point = new Point(5, 5)
    val means = Seq(new Point(0, 0), new Point(3, 4), new Point(6, 8))
    val res = k_means.findClosest(point, means)
    assert(res.x == 3 && res.y == 4)
  }
  test("Classify") {
    val points = Seq(new Point(5, 5), new Point(-1, 1))
    val means = Seq(new Point(0, 0), new Point(6, 8))
    val res = k_means.classify(points, means)
    assert(res(0)._2.length == 1)
    assert(res(0)._2(0).x == -1 && res(0)._2(0).y == 1)
  }
  test("Average") {
    val points = Seq(new Point(5, 5), new Point(-1, 1), new Point(5, 0))
    val mean = new Point(6, 8)
    val res = k_means.findAverage(mean, points)
    assert(k_means.findAverage(mean, Seq()) == mean)
    assert(res.x == 3 && res.y == 2)
  }
}
