class Hairdresser (time: Int, sofa: Queue, num: Int) extends Thread {
  val duration = time
  val name = num
  val queue = sofa
  override def run() = {
    val client = queue.take()
    if (client != 0) {
      Barbers.log.write("Hairdresser " + name + " takes client " + client + " to cutting" + "\r\n")
      Thread.sleep (duration * 1000)
      Barbers.log.write("Hairdresser " + name + " has finished cutting client " + client + "\r\n")
      if (queue.occupied != -1) {
        Barbers.log.write("On sofa remains " + queue.occupied + " clients" + "\r\n")
      }
      run()
    }
    else {
      Barbers.log.write("Hairdresser " + name + " is waiting" + "\r\n")
      var clients = queue.occupied
      while (clients == 0) {
        Thread.sleep (100)
        clients = queue.occupied
      }
      if (clients != -1) {
        run()
      }
    }
  }
}