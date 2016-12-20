class Client (sofa: Queue, number: Int) extends Thread {
  val queue = sofa
  val name = number
  override def run() = {
    queue.sit(name)
  }
}