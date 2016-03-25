object sum_of_elements {
  def main (args: Array[String]): Unit = {
    def sum_of_elements (list: List[Int]): Int = {
      if (list.tail.isEmpty) {
        list.head
      }
      else {
        list.head + sum_of_elements(list.tail)
      }
    }
  }
}
