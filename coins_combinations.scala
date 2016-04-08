object coins_combinations {
  def main (args: Array[String]): Unit = {
    def countChange (money: Int, coins: List[Int]): Int = {
      def combinations (money: Int, coins: List[Int]): Int = {
        if (coins.tail.isEmpty || money == 0) {
          if (money % coins.head == 0 || money != 0) {
            1
          }
          else {
            0
          }
        }
        else {
          if (coins.head <= money) {
            combinations (money - coins.head, coins) + combinations (money, coins.tail)
          }
          else {
            combinations (money, coins.tail)
          }
        }
      }
      val sorted_coins = coins.reverse
      combinations (money, sorted_coins)
    }
  }
}
