object brackets {
  def solo_version(parentheses: Array[Char]): Boolean = {
    var par_match = 0
    var is_correct = true
    for (i <- 0 until parentheses.length) {
      if (parentheses(i) == '(') {
        par_match = par_match + 1
      }
      else {
        if (par_match > 0) {
          par_match = par_match - 1
        }
        else {
          is_correct = false
        }
      }
    }
    if (par_match != 0) {
      is_correct = false
    }
    is_correct
  }
  def mult_version(parentheses: Array[Char], proc_num: Int): Boolean = {
    val length = parentheses.length
    var period = length / proc_num
    if (period * proc_num != length) {
      period = period + 1
    }
    val brackets = new Array[(Int, Int)](proc_num)
    var check = true

    def balance(start: Int, end: Int): Int = {
      if (end - start <= period) {
        var row = true
        var in_row = 0
        var sum = 0
        for (i <- start until end) {
          if(start == 0) {
          }
          if (parentheses(i) == '(') {
            sum = sum + 1
            row = false
          }
          else {
            if (row) {
              in_row = in_row - 1
            }
            sum = sum - 1
            if (start == 0 && sum < 0) {
              check = false
            }
          }
        }
        if (end == length) {
          brackets(proc_num - 1) = (sum, in_row)
        }
        else {
          brackets((start + 1) / period) = (sum, in_row)
        }
        sum
      }
      else {
        var right = 0
        val mid = (start + end) / 2
        val task = new Thread {
          override def run(): Unit = {
            right = balance(mid, end)
          }
        }
        task.start
        val left = balance(start, mid)
        task.join
        left + right
      }
    }

    val result = balance(0, length)
    if (result != 0 || check == false) {
      false
    }
    else {
      var sum = 0
      for (i <- 0 until proc_num) {
        if (sum + brackets(i)._2 < 0) {
          check = false
        }
        sum = sum + brackets(i)._1
      }
      check
    }
  }
}
