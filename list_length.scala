object list_length {
  def main (args: Array[String]): Unit = {
    def list_length[A] (list: List[A]): Int = {
      if (list.tail.isEmpty)
      {
        1
      }
      else {
        1 + list_length (list.tail)
      }
    }
  }
}
