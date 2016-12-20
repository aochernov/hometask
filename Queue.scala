class Queue (seats: Int) {
  val max = seats
  var occupied = 0
  var queue = List[Int]()
  def sit (name: Int) = {
    this.synchronized {
      if (occupied <= max - 1) {
        occupied = occupied + 1
        queue = queue :+ name
        Barbers.log.write("Client " + name + " has arrived" + "\r\n")
        Barbers.log.write("On sofa now " + occupied + " clients" + "\r\n")
      }
      else {
        Barbers.log.write("Client " + name + " has arrived. But there is no free seats on sofa" + "\r\n")
      }
    }
  }
  def take (): Int = {
    var client = 0
    this.synchronized {
      if (occupied > 0) {
        occupied = occupied - 1
        client = queue.head
        queue = queue.tail
      }
    }
    client
  }
}