import java.io.{BufferedReader, FileReader}

object Log_analyzer {
  def parse (str: BufferedReader): List[String] = {
    var line = str.readLine
    var log = List[String]()
    while (line != null) {
      log = line :: log
      line = str.readLine
    }
    log.reverse
  }
  def all_jobs_finished (num: Int, strings: List[String], max: Int): Boolean = {
    if (strings.isEmpty) {
      (num == 0)
    }
    else {
      if (strings.head.contains("cutting")) {
        if (strings.head.contains("takes")) {
          if (num + 1 > max) {
            println("Error! Number of finished jobs is bigger than started ones!")
            return false
          }
          all_jobs_finished(num + 1, strings.tail, max)
        }
        else {
          if (num - 1 < 0) {
            println("Error! Number of started jobs is bigger than started ones!")
            return false
          }
          all_jobs_finished(num - 1, strings.tail, max)
        }
      }
      else {
        all_jobs_finished(num, strings.tail, max)
      }
    }
  }
  def no_overflow (num: Int, strings: List[String]): Boolean = {
    if (strings.isEmpty) {
      true
    }
    else {
      if (strings.head.contains("sofa")) {
        val occ = strings.head.split(' ')(3)
        if (occ.toInt > num) {
          println("Error! Sofa is overflowed!")
          return false
        }
        if (occ.toInt < 0) {
          println("Error! Number of waiting clients is less than zero!")
          return false
        }
        no_overflow(num, strings.tail)
      }
      else {
        no_overflow(num, strings.tail)
      }
    }
  }
  def no_same_clients (strings: List[String]): Boolean = {
    def get_names (lines: List[String], names: List[String]): List[String] = {
      if (lines.isEmpty) {
        names
      }
      else {
        if (lines.head.contains("takes")) {
          val name = lines.head.split(' ')(4)
          get_names(lines.tail, name :: names)
        }
        else {
          get_names(lines.tail, names)
        }
      }
    }
    def no_same_elems (list: List[String]): Boolean = {
      if (list.isEmpty) {
        true
      }
      else {
        if (list.tail.contains(list.head)) {
          false
        }
        else {
          no_same_elems(list.tail)
        }
      }
    }
    val names = get_names(strings, List())
    no_same_elems(names)
  }
  def main (args: Array[String]) = {
    val log = parse(new BufferedReader(new FileReader("log.txt")))
    val seats = (log(1).split(' '))(5).toInt
    val hairdressers = (log(2).split(' '))(3).toInt
    val clients = (log(3).split(' '))(3).toInt
    val drop_log = log.drop(5 + hairdressers)
    if (all_jobs_finished(0, drop_log, hairdressers)) {
      println("All hairdressers have finished their jobs\nThe number of started and finished jobs has matched")
      if (no_overflow(seats, drop_log)) {
        println("No errors with number of clients on sofa")
        if (no_same_clients(drop_log)) {
          println("No errors in log file")
        }
        else {
          println("Error! There is a client with two different hairdressers at the same time")
        }
      }
    }
    else {
      println("Error! Not all hairdressers have finished their job!")
    }
  }
}