object add_to_end {
  def main (args: Array[String]): Unit = {
    def add_to_end[A] (list: List[A], element: A): List[A] = {
      if (list.tail.isEmpty) {
        list.head :: element :: Nil
      }
      else {
        list.head :: add_to_end (list.tail, element)
      }
    }
  }
}
