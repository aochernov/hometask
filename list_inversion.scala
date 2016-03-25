object list_inversion {
  def main (args: Array[String]): Unit = {
    def inversion[A] (list: List[A]): List[A] = {
      if (list.isEmpty) {
        Nil
      }
      else if (list.tail.isEmpty) {
        list
      }
      else {
        inversion (list.tail) ::: list.head :: Nil
      }
    }
  }
}
