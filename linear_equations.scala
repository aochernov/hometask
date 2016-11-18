object linear_equations {
  def solo_version(linear_coef: Array[Int], free_coef: Array[Int]): Int = {
    var result = free_coef(0)
    for (i <- 1 until free_coef.length) {
      result = linear_coef(i) * result + free_coef(i)
    }
    result
  }
  def mult_version(linear_coef: Array[Int], free_coef: Array[Int], proc_num: Int): Int = {
    val size = free_coef.length
    var prod = 0
    var period = size / proc_num
    if(period * proc_num != size) {
      period = period + 1
    }
    var linear_parts = new Array[Int](size + 1)
    val product_tasks_list = Range(0, size, period)
    val product_tasks = product_tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          var up = k + period
          if (up > size) {
            up = size
          }
          for(i <- k until up) {
            prod = prod + free_coef(i) * linear_parts(size - 1 - i)
          }
        }
      }
    })
    left_scan.scan(linear_coef.reverse, 1, linear_parts, (x: Int, y: Int) => x * y, period)
    product_tasks.foreach(k => k.start)
    product_tasks.foreach(k => k.join)
    prod
  }
}