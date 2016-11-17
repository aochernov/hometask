object brackets {
  def solo_version(parentheses: Array[Char]): Boolean = {
    var par_match = 0
    var is_correct = true
    for (i <- 0 until parentheses.length) {
      if(parentheses(i) == '(') {
        par_match = par_match + 1
      }
      else {
        if(par_match > 0) {
          par_match = par_match - 1
        }
        else {
          is_correct = false
        }
      }
    }
    if(par_match != 0) {
      is_correct = false
    }
    is_correct
  }
  def mult_version(parentheses: Array[Char], proc_num: Int): Boolean = {
    val length = parentheses.length
    var period = length / proc_num
    if(period * proc_num != length) {
      period = period + 1
    }
    val part_balance = new Array[Int](proc_num)
    val closing_brackets_in_row = new Array[Int](proc_num)
    val part_balance_task_list = Range(0, length, period)
    val part_balance_task = part_balance_task_list.map(k => {
      new Thread {
        override def run(): Unit = {
          var up = k + period
          if (up > length) {
            up = length
          }
          var balance = 0
          var in_row = true
          var close_in_row = 0
          var x = 0
          for (i <- k until up) {
            x = x + 1
            if(parentheses(i) == '(') {
              balance = balance + 1
              in_row = false
            }
            else {
              balance = balance - 1
              if(in_row) {
                close_in_row = close_in_row - 1
              }
            }
          }
          part_balance(k / period) = balance
          closing_brackets_in_row(k / period) = close_in_row
        }
      }
    })
    part_balance_task.foreach(k => k.start)
    part_balance_task.foreach(k => k.join)
    var result = 0
    for(i <- 0 until proc_num) {
      result = result + part_balance(i)
    }
    if(result != 0) {
      false
    }
    else {
      var close_check = true
      var sum = part_balance(0)
      for(i <- 1 until proc_num) {
        if(sum + closing_brackets_in_row(i) < 0) {
          close_check = false
        }
        sum = sum + part_balance(i)
      }
      close_check
    }
  }
}