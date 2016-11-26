object summarize {
  def solo_version(first_int: Array[Int], second_int: Array[Int]): Array[Int] = {
    var carry = 0
    var sum = new Array[Int](first_int.length)
    for (i <- 0 until first_int.length) {
      sum(i) = (first_int(i) + second_int(i) + carry) % 10
      carry = (first_int(i) + second_int(i) + carry) / 10
    }
    sum
  }
  def mult_version(first_int: Array[Int], second_int: Array[Int], proc_num: Int): Array[Int] = {
    val max_size = first_int.length
    var period = max_size / proc_num
    if (period * proc_num != max_size) {
      period = period + 1
    }
    val sum = new Array[Int](max_size)
    val carry = new Array[Int](max_size)
    val det_carry = new Array[Int](max_size + 1)

    def add(start: Int, end: Int): Unit = {
      if (end - start <= period) {
        for (i <- start until end) {
          val summation = first_int(i) + second_int(i)
          sum(i) = summation % 10
          if (summation == 9) {
            carry(i) = 2
          }
          else if (summation < 9) {
            carry(i) = 0
          }
          else {
            carry(i) = 1
          }
        }
      }
      else {
        val mid = (end + start) / 2
        val task = new Thread {
          override def run(): Unit = {
            add(mid, end)
          }
        }
        task.start
        add(start, mid)
        task.join
      }
    }
    def up(input: Array[Int], from: Int, to: Int, period: Int): TreeRes[Int] = {
      if (to - from <= period) {
        var a = input(from)
        for (i <- from + 1 until to) {
          if (a == 2) {
            a = input(i)
          }
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
        var res = tR.res
        if (res == 2) {
          res = tL.res
        }
        Node(tL, res, tR)
      }
    }
    def down(input: Array[Int], a0: Int, t: TreeRes[Int], out: Array[Int]): Unit = t match {
      case Leaf(from, to, res) => {
        if (from < to) {
          var a = a0
          for (i <- from until to) {
            if (input(i) != 2) {
              a = input(i)
            }
            out(i + 1) = a
          }
        }
      }
      case Node(l, _, r) => {
        var a = l.res
        if (a == 2) {
          a = a0
        }
        val right = new Thread {
          override def run(): Unit = {
            down(input, a, r, out)
          }
        }
        right.start
        down(input, a0, l, out)
        right.join
      }
    }
    def summation(start: Int, end: Int): Unit = {
      if (end - start <= period) {
        for (i <- start until end) {
          sum(i) = (sum(i) + det_carry(i)) % 10
        }
      }
      else {
        val mid = (start + end) / 2
        val task = new Thread {
          override def run(): Unit = {
            summation(mid, end)
          }
        }
        task.start
        summation(start, mid)
        task.join
      }
    }

    add(0, max_size)
    val tree = up(carry, 0, max_size, period)
    down(carry, 0, tree, det_carry)
    summation(0, max_size)
    sum
  }
}