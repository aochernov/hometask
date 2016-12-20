import scala.io.StdIn.readLine
import java.io.{File, PrintWriter}

object Barbers {
  val log = new PrintWriter(new File("log.txt"))
  def main(args: Array[String]) = {
    log.write("New launch" + "\r\n")
    val seats = readLine("Enter the number of seats on sofa: ")
    log.write("Number of seats on sofa: " + seats + "\r\n")
    val hairdressers_num = readLine("Enter the number of hairdressers: ")
    log.write("Number of hairdressers: " + hairdressers_num + "\r\n")
    val clients = readLine("Enter the number of clients: ")
    log.write("Number of clients: " + clients + "\r\n")
    val random = scala.util.Random
    val sofa = new Queue (seats.toInt)
    val Hairdresser = new Array[Hairdresser](hairdressers_num.toInt + 1)
    for ( i <- 1 until (hairdressers_num.toInt + 1)) {
      val time = (Math.abs(random.nextInt) % 6) + 5
      Hairdresser(i) = new Hairdresser(time, sofa, i)
      log.write("New hairdresser with name " + i + " created. Time needed for work is " + time + "\r\n")
    }
    var num = 1
    for ( i <- 1 until (hairdressers_num.toInt + 1)) {
      Hairdresser(i).start
    }
    log.write("Work is started" + "\r\n")
    Thread.sleep(1000)
    while (num != (clients.toInt + 1)) {
      new Client(sofa, num).start
      num = num + 1
      val time = (Math.abs(random.nextInt) % 15) + 1
      Thread.sleep(time * 1000)
    }
    sofa.occupied = -1
    for ( i <- 1 until (hairdressers_num.toInt + 1)) {
      Hairdresser(i).join
    }
    log.write("Finished successfully" + "\r\n")
    log.close
  }
}
