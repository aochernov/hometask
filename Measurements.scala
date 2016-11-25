import org.scalameter._

object Measurements extends Bench.LocalTime {
  val test_image = BLUR.get_image("test.jpg")
  def vertical_blur_measurement(period: Int): Unit = {
    val blured_test_image = BLUR.vertical_blur(test_image, 10, period)
  }
  def horizontal_blur_measurement(period: Int): Unit = {
    val blured_test_image = BLUR.vertical_blur(test_image, 10, period)
  }
  val periods: Gen[Int] = Gen.range("Periods")(1, 4, 1)
  performance of "Number of processes" in {
    measure method "map" in {
      using (periods) in {
        r => vertical_blur_measurement(r)
      }
    }
  }
  performance of "Number of processes" in {
    measure method "map" in {
      using (periods) in {
        r => horizontal_blur_measurement(r)
      }
    }
  }
}
