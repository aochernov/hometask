object roots {
  def main (args: Array[String]): Unit = {
    def roots_of_equation (a: Double, b: Double, c: Double, d: Double): List[Double] = {
      def square_equation (a: Double, b: Double, c: Double): List[Double] = {
        val D = b * b - 4 * a * c
        if (D > 0) {
          ((-b + Math.sqrt(D)) / (2 * a)) :: ((-b - Math.sqrt(D)) / (2 * a)) :: Nil
        }
        else if (D == 0) {
          (-b / (2 * a)) :: Nil
        }
        else {
          Nil
        }
      }
      def cubic_equation (a: Double, b: Double, c: Double, d: Double): List[Double] = {
        val a1 = b / a
        val a2 = c / a
        val a3 = d / a
        val p = (a1 * a1 - 3 * a2) / 9
        val q = (2 * a1 * a1 * a1 - 9 * a1 * a2 + 27 * a3) / 54
        if (q * q < p * p * p) {
          val t = Math.acos (q / Math.sqrt (p * p * p)) / 3
          val x1 = -2 * Math.sqrt (p) * Math.cos (t) - a1 / 3
          val x2 = -2 * Math.sqrt (p) * Math.cos (t + 2 * Math.PI / 3) - a1 / 3
          val x3 = -2 * Math.sqrt (p) * Math.cos (t - 2 * Math.PI / 3) - a1 / 3
          x1 :: x2 :: x3 ::Nil
        }
        else {
          val A = -Math.signum (q) * Math.pow (Math.sqrt (q * q - p * p * p), 1/3)
          var B: Double = 0
          if (A != 0) {
            B = p / A
          }
          val x = (A + B) - a1 / 3
          if (A != B) {
            x :: Nil
          }
          else {
            val y = -A - a1 / 3
            x :: y :: Nil
          }
        }
      }
      if (a == 0) {
        square_equation (b, c, d)
      }
      else if (a == 0 && b == 0) {
        (- (d / c)) :: Nil
      }
      else if (a == 0 && b == 0 && c == 0) {
        Nil
      }
      else {
        cubic_equation (a, b, c, d)
      }
    }
  }
}
