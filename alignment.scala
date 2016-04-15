object alignment {
  abstract class ParagraphElement {
    def is_word: Boolean
    def printelement: String
  }
  class Word(string: String) extends ParagraphElement {
    def is_word: Boolean = true
    def printelement: String = string
  }
  class Space(number: Int) extends ParagraphElement {
    def is_word: Boolean = false
    def printelement: String = number.toString
  }
  def print_paragraph (main_list: List[List[ParagraphElement]]): String = {
    def print_line (list: List[ParagraphElement]): String = {
      if (list.tail.isEmpty) {
        list.head.printelement
      }
      else {
        list.head.printelement + " " + print_line (list.tail)
      }
    }
    if (main_list.tail.isEmpty) {
      print_line (main_list.head)
    }
    else {
      print_line (main_list.head) + " | " + print_paragraph (main_list.tail)
    }
  }
  def align_paragraph (text: List[String], screen: Int, al: Char): List[List[ParagraphElement]] = {
    def alignment (word_list: List[String], width: Int, align: Char): List[ParagraphElement] = {
      def get_line (list: List[String], new_list: List[String], remaining_width: Int): List[ParagraphElement] = {
        if (list.isEmpty) {
          if (align == 'f') {
            align_line(new_list, remaining_width, 'l')
          }
          else {
            align_line(new_list, remaining_width, align)
          }
        }
        else if (list.head.length <= remaining_width) {
          get_line (list.tail, list.head :: new_list, remaining_width - (list.head.length + 1))
        }
        else {
          align_line(new_list, remaining_width, align)
        }
      }
      def align_line (list: List[String], space: Int, line_alignment: Char): List[ParagraphElement] = {
        def conv_list (stringlist: List[String], list: List[ParagraphElement]): List[ParagraphElement] = {
          if (stringlist.tail.isEmpty) {
            new Word(stringlist.head) :: list
          }
          else {
            val singlespace = new Space(1)
            val word = new Word(stringlist.head)
            conv_list (stringlist.tail, singlespace :: word :: list)
          }
        }
        def rigth_align (words: List[String], empty_space: Int) = {
          if (empty_space != 0) {
            new Space(empty_space) :: conv_list (words, Nil)
          }
          else {
            conv_list (words, Nil)
          }
        }
        def left_align (words: List[String], empty_space: Int) = {
          if (empty_space != 0) {
            conv_list (words, Nil) ::: List(new Space(empty_space))
          }
          else {
            conv_list (words, Nil)
          }
        }
        def centre_align (words: List[String], empty_space: Int) = {
          if (empty_space != 0) {
            var left_spaces = 0
            var rigth_spaces = 0
            if (empty_space % 2 == 0) {
              left_spaces = empty_space / 2
              rigth_spaces = empty_space / 2
            }
            else {
              left_spaces = 1 + empty_space / 2
              rigth_spaces = empty_space / 2
            }
            new Space(left_spaces) :: conv_list (words, Nil) ::: List(new Space(rigth_spaces))
          }
          else {
            conv_list (words, Nil)
          }
        }
        def fit_align (words: List[String], empty_space: Int) = {
          if (empty_space != 0) {
            val converted_list = conv_list(words, Nil)
            if (converted_list.tail.isEmpty) {
              converted_list.head :: new Space(1 + empty_space) :: Nil
            }
            else {
              converted_list.head :: new Space(1 + empty_space) :: converted_list.tail.tail
            }
          }
          else {
            conv_list(words, Nil)
          }
        }
        val real_space = space + 1
        if (line_alignment == 'r') {
          rigth_align (list, real_space)
        }
        else if (line_alignment == 'c') {
          centre_align (list, real_space)
        }
        else if (line_alignment == 'f') {
          fit_align (list, real_space)
        }
        else {
          left_align (list, real_space)
        }
      }
      get_line (word_list, Nil, width)
    }
    def get_paragraph (word_list: List[String], width: Int, align: Char, final_list: List[List[ParagraphElement]]): List[List[ParagraphElement]] = {
      def number_of_words (list: List[ParagraphElement], number: Int): Int = {
        if (list.isEmpty) {
          number
        }
        else {
          if (list.head.is_word) {
            number_of_words (list.tail, number + 1)
          }
          else {
            number_of_words (list.tail, number)
          }
        }
      }
      if (word_list.isEmpty) {
        final_list.reverse
      }
      else {
        val line = alignment(word_list, width, align)
        get_paragraph (word_list.drop(number_of_words(line, 0)), width, align, line :: final_list)
      }
    }
    def max_width (list: List[String], maximum: Int): Int = {
      if (list.isEmpty) {
        maximum
      }
      else {
        if (list.head.length >= maximum) {
          max_width (list.tail, list.head.length)
        }
        else {
          max_width (list.tail, maximum)
        }
      }
    }
    val max = max_width (text, screen)
    if ( max >= screen) {
      align_paragraph (text, max, al)
    }
    else {
      get_paragraph (text, screen, al, Nil)
    }
  }
}