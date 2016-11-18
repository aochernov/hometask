object left_scan {
  sealed abstract class TreeRes[A] {val res: A}
  case class Leaf[A] (from: Int, to: Int, override val res: A) extends TreeRes[A]
  case class Node[A] (l: TreeRes[A], override val res: A, r: TreeRes[A]) extends TreeRes[A]
  def reduce[A] (input: Array[A], left: Int, right: Int, a0: A, f: (A, A) => A): A = {
    var a = a0
    var i = left
    while (i < right) {
      a = f(a, input(i))
      i = i + 1
    }
    a
  }
  def scan_left_segment[A](input: Array[A], left: Int, right: Int, a0: A, f: (A, A) => A, out: Array[A]) = {
    if (left < right) {
      var i = left
      var a = a0
      while (i < right) {
        a = f (a, input(i))
        i = i + 1
        out(i) = a
      }
    }
  }
  def upsweep[A](input: Array[A], from: Int, to: Int, f: (A, A) => A, period: Int): TreeRes[A] = {
    if (to - from < period) {
      Leaf(from, to, reduce(input, from + 1, to, input(from), f))
    }
    else {
      val mid = from + (to - from) / 2
      var tL: TreeRes[A] = Leaf[A](0, 0, input(0))
      var tR: TreeRes[A] = Leaf[A](0, 0, input(0))
      val first = new Thread {
        override def run(): Unit = {
          tL = upsweep(input, from, mid, f, period)
        }
      }
      val second = new Thread {
        override def run(): Unit = {
          tR = upsweep(input, mid, to, f, period)
        }
      }
      first.start
      second.start
      first.join
      second.join
      Node(tL, f(tL.res, tR.res), tR)
    }
  }
  def downsweep[A](input: Array[A], a0: A, f: (A, A) => A, t: TreeRes[A], out: Array[A]): Unit = t match {
    case Leaf(from, to, res) => scan_left_segment(input, from, to, a0, f, out)
    case Node(l, _, r) => {
      val first = new Thread {
        override def run(): Unit = {
          downsweep(input, a0, f, l, out)
        }
      }
      val second = new Thread {
        override def run(): Unit = {
          downsweep(input, f(a0, l.res), f, r, out)
        }
      }
      first.start
      second.start
      first.join
      second.join
    }
  }
  def scan[A](input: Array[A], a0: A , out: Array[A], f: (A, A) => A, period: Int) = {
    val t = upsweep(input, 0, input.length, f, period)
    downsweep(input, a0, f, t, out)
    out(0) = a0
  }
}
