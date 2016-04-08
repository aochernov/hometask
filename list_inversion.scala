object list_inversion {
  def main (args: Array[String]): Unit = {
    def inversion[A] (list: List[A]): List[A] = {
      def invert (start_list: List[A], end_list: List[A]): List[A] = {
        if (start_list.isEmpty) {
          end_list
        }
        else {
          invert (start_list.tail, start_list.head :: end_list)
        }
      }
      invert (list, Nil)
    }
  }
}
