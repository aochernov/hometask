import org.scalameter._

object measurements extends Bench.LocalTime {
  val points = Array(k_means.generatePoints(100, 50), k_means.generatePoints(100, 100), k_means.generatePoints(100, 500), k_means.generatePoints(100, 1000), k_means.generatePoints(100, 5000), k_means.generatePoints(100, 10000), k_means.generatePoints(100, 50000))
  val means_5 = points.map(k_means.initializeMeans(5, _))
  val means_10 = points.map(k_means.initializeMeans(10, _))
  val means_25 = points.map(k_means.initializeMeans(25, _))
  val points_par = points.map(_.par)
  val means_par_5 = means_5.map(_.par)
  val means_par_10 = means_10.map(_.par)
  val means_par_25 = means_25.map(_.par)
  val number: Gen[Int] = Gen.range("Number of sequence")(0, points.length - 1, 1)

  performance of "Sequences with 5 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points(r), means_5(r), 1.0)
      }
    }
  }
  performance of "Parallel Sequences with 5 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points_par(r), means_par_5(r), 1.0)
      }
    }
  }
  performance of "Sequences with 10 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points(r), means_10(r), 1.0)
      }
    }
  }
  performance of "Parallel Sequences with 10 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points_par(r), means_par_10(r), 1.0)
      }
    }
  }
  performance of "Sequences with 25 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points(r), means_25(r), 1.0)
      }
    }
  }
  performance of "Parallel Sequences with 25 clusters" in {
    measure method "map" in {
      using (number) in {
        r => k_means.kMeans(points_par(r), means_par_25(r), 1.0)
      }
    }
  }
}