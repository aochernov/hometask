import org.scalatest.FunSuite

class unit_tests extends FunSuite {
  test("Summation") {
    val first_int = Array(8, 3, 6, 0, 2, 1, 9, 1, 1, 5)
    val second_int = Array(1, 9, 6, 3, 7, 7, 5, 2, 1, 3)
    val sum = Array(9, 2, 3, 4, 9, 8, 4, 4, 2, 8)
    assert(summarize.solo_version(first_int, second_int) == sum)
    assert(summarize.mult_version(first_int, second_int, 2) == sum)
    assert(summarize.mult_version(first_int, second_int, 4) == sum)
  }
  test("Linear equation") {
    val linear = Array(7, 3, 2, 1, 4)
    val free = Array(5, 2, 0, 9, 3)
    val result = 175
    assert(linear_equations.solo_version(linear, free) == result)
    assert(linear_equations.mult_version(linear, free, 2) == result)
    assert(linear_equations.mult_version(linear, free, 4) == result)
  }
  test("Brackets balance") {
    val first = "()()()()()()()()"
    val second = "(()()()()()()"
    val third = "())(()()()()()"
    assert(brackets.solo_version(first.toCharArray) == true)
    assert(brackets.solo_version(second.toCharArray) == false)
    assert(brackets.solo_version(third.toCharArray) == false)
    assert(brackets.mult_version(first.toCharArray, 2) == true)
    assert(brackets.mult_version(second.toCharArray, 4) == false)
    assert(brackets.mult_version(third.toCharArray, 2) == false)
  }
  test("Turtle") {
    val angles = Array(45, 30, 105, 90)
    val distance = Array(40, 50, 40, 20)
    val result = (0, 56)
    assert(my_turtle.solo_version(distance, angles) == result)
    assert(my_turtle.mult_version(distance, angles, 2) == result)
    assert(my_turtle.mult_version(distance, angles, 4) == result)
  }
}