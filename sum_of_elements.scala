object sum_of_elements {
  def main (args: Array[String]): Unit = {
    def sum_of_elements (list: List[Int]): Int = {
      def summarize (list: List[Int], sum: Int): Int = {
        if (list.isEmpty) {
          sum
        }
        else {
          summarize (list.tail, sum + list.head)
        }
      }
      summarize (list, 0)
    }
  }
}
