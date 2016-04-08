object function_filter {
  def main (args: Array[String]): Unit = {
    def function_filter (list: List[Int], filter: Int => Boolean): List[Int] = {
      if (list.isEmpty) {
        Nil
      }
      else {
        if (filter (list.head)) {
          list.head :: function_filter (list.tail, filter)
        }
        else {
          function_filter (list.tail, filter)
        }
      }
    }
  }
}
