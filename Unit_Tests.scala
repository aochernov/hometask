import org.scalatest.FunSuite

class Unit_Tests extends FunSuite{
  test("Compounding") {
    val red = 0x15
    val green = 0xb9
    val blue = 0x03
    val alpha = 0x57
    val color = 0x15b90357
    assert(BLUR.compound(red, green, blue, alpha) == color)
  }
  test("Separation") {
    val red = 0x15
    val green = 0xb9
    val blue = 0x03
    val alpha = 0x57
    val color = 0x15b90357
    assert(BLUR.separate(color) == (red, green, blue, alpha))
  }
  test("Blur") {
    val pic = new BLUR.IMG(3, 3)
    pic.picture = Array(0x097f3abb, 0x8112c2d0, 0x35ff0017, 0xab54fd00, 0x3fdb7800, 0xdd137600, 0xa5801673, 0xffffff00, 0xdbbcda4e)
    assert(BLUR.Blur(pic, 1, 1, 1) == 0x8f908a44)
  }
}