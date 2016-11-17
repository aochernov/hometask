import org.scalameter._

object measurements extends Bench.LocalTime {
  val array_length = 1000000
  val random = scala.util.Random
  val first_int = new Array[Int](array_length)
  val second_int = new Array[Int](array_length)
  val linear_coef = new Array[Int](array_length)
  val free_coef = new Array[Int](array_length)
  val parentheses = new Array[Char](array_length)
  val angle = new Array[Int](array_length)
  val dist = new Array[Int](array_length)
  for(i <- 0 until array_length) {
    val first = Math.abs(random.nextInt())
    val second = Math.abs(random.nextInt())
    first_int(i) = first % 10
    second_int(i) = second % 10
    linear_coef(i) = first % 25
    free_coef(i) = second % 25
    if((first + second) % 2 == 0) {
      parentheses(i) = '('
    }
    else {
      parentheses(i) = ')'
    }
    angle(i) = first % 360
    dist(i) = second % 100
  }
  def sum_m(period: Int) = {
    val sum = summarize.mult_version(first_int, second_int, period)
  }
  def lin_eq_m(period: Int) = {
    val res = linear_equations.mult_version(linear_coef, free_coef, period)
  }
  def par_m(period: Int) = {
    val res = brackets.mult_version(parentheses, period)
  }
  def turtle_m(period: Int) = {
    val res = my_turtle.mult_version(dist, angle, period)
  }
  def sum_s(period: Int) = {
    val sum = summarize.solo_version(first_int, second_int)
  }
  def lin_eq_s(period: Int) = {
    val res = linear_equations.solo_version(linear_coef, free_coef)
  }
  def par_s(period: Int) = {
    val res = brackets.solo_version(parentheses)
  }
  def turtle_s(period: Int) = {
    val res = my_turtle.solo_version(dist, angle)
  }
  val periods: Gen[Int] = Gen.range("Number of Processes")(1, 16, 1)
  val solo: Gen[Int] = Gen.range("Solo")(1, 1, 1)
  performance of "Single process addition" in {
    measure method "map" in {
      using (solo) in {
        r => sum_s(r)
      }
    }
  }
  performance of "Multi process addition" in {
    measure method "map" in {
      using (periods) in {
        r => sum_m(r)
      }
    }
  }
  performance of "Single process equations sequence" in {
    measure method "map" in {
      using (solo) in {
        r => lin_eq_s(r)
      }
    }
  }
  performance of "Multi process equations sequence" in {
    measure method "map" in {
      using (periods) in {
        r => lin_eq_m(r)
      }
    }
  }
  performance of "Single process bracket balance" in {
    measure method "map" in {
      using (solo) in {
        r => par_s(r)
      }
    }
  }
  performance of "Multi process bracket balance" in {
    measure method "map" in {
      using (periods) in {
        r => par_m(r)
      }
    }
  }
  performance of "Single process turtle" in {
    measure method "map" in {
      using (solo) in {
        r => turtle_s(r)
      }
    }
  }
  performance of "Multi process turtle" in {
    measure method "map" in {
      using (periods) in {
        r => turtle_m(r)
      }
    }
  }
}
