object Triangle {
  def main (args: Array[String]): Unit = {
    def pascal_triangle (i: Int, j: Int): Int = {
      if (i == 1 || j == 1) {
        1
      }
      else {
        pascal_triangle (i - 1, j) + pascal_triangle (i, j - 1)
      }
    }
  }
}
