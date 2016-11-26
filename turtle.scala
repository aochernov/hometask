object my_turtle {
  def solo_version(dist: Array[Int], ang: Array[Int]): (Int, Int) = {
    var x = 0
    var y = 0
    var angle = 0
    val to_radian = Math.PI / 180
    for (i <- 0 until dist.length) {
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

    def up(input: Array[Int], from: Int, to: Int, period: Int): TreeRes[Int] = {
      if (to - from <= period) {
        var a = input(from)
        for (i <- from + 1 until to) {
          a = a + input(i)
        }
        Leaf(from, to, a)
      }
      else {
        val mid = from + (to - from) / 2
        var tL: TreeRes[Int] = Leaf[Int](0, 0, input(0))
        var tR: TreeRes[Int] = Leaf[Int](0, 0, input(0))
        val right = new Thread {
          override def run(): Unit = {
            tR = up(input, mid, to, period)
          }
        }
        right.start
        tL = up(input, from, mid, period)
        right.join
        Node(tL, tL.res + tR.res, tR)
      }
    }
    def down(input: Array[Int], a0: Int, t: TreeRes[Int], out: Array[Int]): Unit = t match {
      case Leaf(from, to, res) => {
        if (from < to) {
          var a = a0
          for (i <- from until to) {
            a = a + input(i)
            out(i) = a
          }
        }
      }
      case Node(l, _, r) => {
        val right = new Thread {
          override def run(): Unit = {
            down(input, a0 + l.res, r, out)
          }
        }
        right.start
        down(input, a0, l, out)
        right.join
      }
    }
    def calculate(start: Int, end: Int): (Int, Int) = {
      if (end - start <= period) {
        var x = 0
        var y = 0
        for (i <- start until end) {
          x = x + (dist(i) * Math.cos(correct_angles(i) * to_radian)).toInt
          y = y + (dist(i) * Math.sin(correct_angles(i) * to_radian)).toInt
        }
        (x, y)
      }
      else {
        var xy_right: (Int, Int) = (0, 0)
        val mid = (start + end) / 2
        val task = new Thread {
          override def run(): Unit = {
            xy_right = calculate(mid, end)
          }
        }
        task.start
        val (x_left, y_left) = calculate(start, mid)
        task.join
        (x_left + xy_right._1, y_left + xy_right._2)
      }
    }

    val tree = up(ang, 0, number, period)
    down(ang, 0, tree, correct_angles)
    calculate(0, number)
  }
}