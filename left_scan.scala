sealed abstract class TreeRes[A] {val res: A}
case class Leaf[A] (from: Int, to: Int, override val res: A) extends TreeRes[A]
case class Node[A] (l: TreeRes[A], override val res: A, r: TreeRes[A]) extends TreeRes[A]