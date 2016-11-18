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
    var res_x = 0
    var res_y = 0
    var period = number / proc_num
    if (period * proc_num != number) {
      period = period + 1
    }
    val correct_angles = new Array[Int](number + 1)
    val to_radian = Math.PI / 180
    val trig_tasks_list = Range(0, number, period)
    val trig_tasks = trig_tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          var up = k + period
          if (up > number) {
            up = number
          }
          for(i <- k until up) {
            res_x = res_x + (dist(i) * Math.cos(correct_angles(i + 1) * to_radian)).toInt
            res_y = res_y + (dist(i) * Math.sin(correct_angles(i + 1) * to_radian)).toInt
          }
        }
      }
    })
    left_scan.scan(ang, 0, correct_angles, (x: Int, y: Int) => x + y, period)
    trig_tasks.foreach(k => k.start)
    trig_tasks.foreach(k => k.join)
    (res_x, res_y)
  }
}