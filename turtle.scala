object my_turtle {
  def solo_version(dist: Array[Int], ang: Array[Int]): (Int, Int) = {
    var x = 0
    var y = 0
    var angle = 0
    val to_radian = Math.PI / 180
    for(i <- 0 until dist.length) {
      angle = (angle + ang(i)) % 360
      x = x + (dist(i) * Math.cos(angle * to_radian)).toInt
      y = y + (dist(i) * Math.sin(angle * to_radian)).toInt
    }
    (x, y)
  }
  def mult_version(dist: Array[Int], ang: Array[Int], proc_num: Int): (Int, Int) = {
    val number = dist.length
    var period = number / proc_num
    if (period * proc_num != number) {
      period = period + 1
    }
    val correct_angles = new Array[Int](number)
    val to_radian = Math.PI / 180
    val x = new Array[Int](number)
    val y = new Array[Int](number)
    val trig_tasks_list = Range(0, number, period)
    val trig_tasks = trig_tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          var up = k + period
          if (up > number) {
            up = number
          }
          for(i <- 0 until up) {
            x(i) = (dist(i) * Math.cos(correct_angles(i) * to_radian)).toInt
            y(i) = (dist(i) * Math.sin(correct_angles(i) * to_radian)).toInt
          }
        }
      }
    })
    val part_x_sum = new Array[Int](proc_num)
    val part_y_sum = new Array[Int](proc_num)
    val x_tasks_list = Range(0, number, period)
    val y_tasks_list = Range(0, number, period)
    val x_tasks = x_tasks_list.map(n => {
      new Thread {
        override def run(): Unit = {
          var up = n + period
          if (up > number) {
            up = number
          }
          var sum = 0
          for(i <- n until up) {
            sum = sum + x(i)
          }
          part_x_sum(n / period) = sum
        }
      }
    })
    val y_tasks = y_tasks_list.map(m => {
      new Thread {
        override def run(): Unit = {
          var up = m + period
          if (up > number) {
            up = number
          }
          var sum = 0
          for(i <- m until up) {
            sum = sum + y(i)
          }
          part_y_sum(m / period) = sum
        }
      }
    })
    var angle = 0
    for(i <- 0 until number) {
      angle = angle + ang(i)
      correct_angles(i) = angle % 360
    }
    trig_tasks.foreach(k => k.start)
    trig_tasks.foreach(k => k.join)
    x_tasks.foreach(n => n.start)
    y_tasks.foreach(m => m.start)
    x_tasks.foreach(n => n.join)
    y_tasks.foreach(m => m.join)
    var res_x = 0
    var res_y = 0
    for(i <- 0 until proc_num) {
      res_x = res_x + part_x_sum(i)
      res_y = res_y + part_y_sum(i)
    }
    (res_x, res_y)
  }
}