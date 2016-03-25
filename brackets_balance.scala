object brackets_balance {
  def main (args: Array[String]): Unit = {
    def brackets_balance (list: List[Char]): Boolean = {
      def balance (list: List[Char], b: Int): Int = {
        if (list.isEmpty) {
          b
        }
        else {
          if (b < 0) {
            -1
          }
          else if (list.head == '(') {
            balance (list.tail, b + 1)
          }
          else if (list.head == ')') {
            balance (list.tail, b - 1)
          }
          else {
            balance (list.tail, b)
          }
        }
      }
      if (balance (list, 0) == 0) {
        true
      }
      else {
        false
      }
    }
  }
}
