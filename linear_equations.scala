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
    if (period * proc_num != size) {
      period = period + 1
    }
    val linear_parts = new Array[Int](size + 1)

    def up(input: Array[Int], from: Int, to: Int, period: Int): TreeRes[Int] = {
      if (to - from <= period) {
        var a = input(to - 1)
        for (i <- to - 2 until from - 1 by (-1)) {
          a = a * input(i)
        }
        Leaf(from, to, a)
      }
      else {
        val mid = from + (to - from) / 2
        var tL: TreeRes[Int] = Leaf[Int](0, 0, input(0))
        var tR: TreeRes[Int] = Leaf[Int](0, 0, input(0))
        val left = new Thread {
          override def run(): Unit = {
            tL = up(input, from, mid, period)
          }
        }
        left.start
        tR = up(input, mid, to, period)
        left.join
        Node(tL, tL.res * tR.res, tR)
      }
    }
    def down(input: Array[Int], a0: Int, t: TreeRes[Int], out: Array[Int]): Unit = t match {
      case Leaf(from, to, res) => {
        if (from < to) {
          var a = a0
          for (i <- to - 1 until from - 1 by (-1)) {
            a = a * input(i)
            out(i) = a
          }
        }
      }
      case Node(l, _, r) => {
        val left = new Thread {
          override def run(): Unit = {
            down(input, a0 * r.res, l, out)
          }
        }
        left.start
        down(input, a0, r, out)
        left.join
      }
    }
    def summation(start: Int, end: Int): Int = {
      if (end - start <= period) {
        var sum = 0
        for (i <- start until end) {
          sum = sum + (free_coef(i) * linear_parts(i + 1))
        }
        sum
      }
      else {
        var right = 0
        val mid = (start + end) / 2
        val task = new Thread {
          override def run(): Unit = {
            right = summation(mid, end)
          }
        }
        task.start
        val left = summation(start, mid)
        task.join
        left + right
      }
    }

    val tree = up(linear_coef, 1, size, period)
    down(linear_coef, 1, tree, linear_parts)
    linear_parts(size) = 1
    summation(0, size)
  }
}