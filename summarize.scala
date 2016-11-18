object summarize {
  def solo_version(first_int: Array[Int], second_int: Array[Int]): Array[Int] = {
    var carry = 0
    var sum = new Array[Int](first_int.length)
    for(i <- 0 until first_int.length) {
      sum(i) = (first_int(i) + second_int(i) + carry) % 10
      carry = (first_int(i) + second_int(i) + carry) / 10
    }
    sum
  }
  def mult_version(first_int: Array[Int], second_int: Array[Int], proc_num: Int): Array[Int] = {
    def det(prev: Int, next: Int): Int = {
      if (next == 2) {
        prev
      }
      else {
        next
      }
    }
    val max_size = first_int.length
    var period = max_size / proc_num
    if(period * proc_num != max_size) {
      period = period + 1
    }
    val non_determined_array = new Array[Int](max_size)
    var determined_array = new Array[Int](max_size + 1)
    var sum = new Array[Int](max_size)
    var need_det = false
    val set_nda_tasks_list = Range(0, max_size, period)
    val set_nda_tasks = set_nda_tasks_list.map(k => {
      new Thread {
        override def run():Unit = {
          var up = k + period
          if (up > max_size) {
            up = max_size
          }
          for(i <- k until up) {
            val num = first_int(i) + second_int(i)
            if(num == 9) {
              non_determined_array(k) = 2
              need_det = true
            }
            else if (num < 9) {
              non_determined_array(i) = 0
            }
            else {
              non_determined_array(i) = 1
            }
            sum(i) = num % 10
          }
        }
      }
    })
    val add_list = Range(0, max_size, period)
    val add = add_list.map(l => {
      new Thread {
        override def run(): Unit = {
          var up = l + period
          if (up > max_size) {
            up = max_size
          }
          for (i <- l until up) {
            if(i != 0) {
              sum(i) = sum(i) + determined_array(i)
            }
          }
        }
      }
    })
    set_nda_tasks.foreach(k => k.start)
    set_nda_tasks.foreach(k => k.join)
    left_scan.scan(non_determined_array, 0, determined_array, det, period)
    add.foreach(l => l.start)
    add.foreach(l => l.join)
    sum
  }
}