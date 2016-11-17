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
    var period = size / proc_num
    if(period * proc_num != size) {
      period = period + 1
    }
    val linear_parts = new Array[Int](size)
    val product = new Array[Int](size)
    val product_tasks_list = Range(0, size, period)
    val product_tasks = product_tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          var up = k + period
          if (up > size) {
            up = size
          }
          for(i <- k until up) {
            product(i) = free_coef(i) * linear_parts(i)
          }
        }
      }
    })
    val part_sum = new Array[Int](proc_num)
    val part_sum_tasks_list = Range(0, size, period)
    val sum_tasks = part_sum_tasks_list.map(n => {
      new Thread {
        override def run(): Unit = {
          var up = n + period
          if (up > size) {
            up = size
          }
          var sum = 0
          for(i <- n until up) {
            sum = sum + product(i)
          }
          part_sum(n / period) = sum
        }
      }
    })
    linear_parts(size - 1) = 1
    for(i <- size - 2 until -1 by (-1)) {
      linear_parts(i) = linear_parts(i + 1) * linear_coef(i + 1)
    }
    product_tasks.foreach(k => k.start)
    product_tasks.foreach(k => k.join)
    sum_tasks.foreach(n => n.start)
    sum_tasks.foreach(n => n.join)
    var prod = 0
    for(i <- 0 until proc_num) {
      prod = prod + part_sum(i)
    }
    prod
  }
}