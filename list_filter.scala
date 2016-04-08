object list_filter {
  def main (args: Array[String]): Unit = {
    def filter (list: List[Int]): List[Int] = {
      if (list.isEmpty) {
        Nil
      }
      else {
        if (list.head < 100) {
          list.head :: filter (list.tail)
        }
        else {
          filter (list.tail)
        }
      }
    }
  }
}
