import scala.io.StdIn.readLine
import java.io.File
import javax.imageio.ImageIO
import java.awt.image.BufferedImage
import swing.{MainFrame, Panel, SimpleSwingApplication}
import java.awt.{Color, Dimension, Graphics2D}
import org.scalameter._
import org.scalatest.FunSuite

class DataPanel(data: Array[Array[Color]]) extends Panel {
  override def paintComponent(g: Graphics2D) {
    val width = data.length
    val height = data.map(_.length).max
    val dx = g.getClipBounds.width.toFloat  / width
    val dy = g.getClipBounds.height.toFloat / height
    for {
      x <- 0 until data.length
      y <- 0 until data(x).length
      x1 = (x * dx).toInt
      y1 = (y * dy).toInt
      x2 = ((x + 1) * dx).toInt
      y2 = ((y + 1) * dy).toInt
    } {
      data(x)(y) match {
        case c: Color => g.setColor(c)
        case _ => g.setColor(Color.WHITE)
      }
      g.fillRect(x1, y1, x2 - x1, y2 - y1)
    }
  }
}
object Measurements extends Bench.LocalTime {
  val test_image = BLUR.get_image("test.jpg")
  def vertical_blur_measurement(period: Int): Unit = {
    val blured_test_image = BLUR.vertical_blur(test_image, 10, period)
  }
  def horizontal_blur_measurement(period: Int): Unit = {
    val blured_test_image = BLUR.vertical_blur(test_image, 10, period)
  }
  val periods: Gen[Int] = Gen.range("Periods")(1, 1000, 250)
  performance of "Periods" in {
    measure method "map" in {
      using (periods) in {
        r => vertical_blur_measurement(r)
      }
    }
  }
  performance of "Periods" in {
    measure method "map" in {
      using (periods) in {
        r => horizontal_blur_measurement(r)
      }
    }
  }
}
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
object BLUR extends SimpleSwingApplication {
  type RGBA = (Int, Int, Int, Int)
  class IMG(width: Int, height: Int) {
    val w = width
    val h = height
    var picture = new Array[Int](width * height)

    def apply(x: Int, y: Int) = {
      picture(x + width * y)
    }

    def update(x: Int, y: Int, z: Int) = {
      picture(x + width * y) = z
    }
  }
  def separate(color: Int): RGBA = {
    val hex = 0x000000FF
    val A = color & hex
    val B = (color >>> 8) & hex
    val G = (color >>> 16) & hex
    val R = color >>> 24
    (R, G, B, A)
  }
  def compound(color: RGBA): Int = {
    (color._1 << 24) | (color._2 << 16) | (color._3 << 8) | color._4
  }
  def Blur(picture: IMG, radius: Int, x: Int, y: Int): Int = {
    def mixer(colors: List[Int], R_sum: Int, G_sum: Int, B_sum: Int, A_sum: Int): RGBA = {
      if (colors.isEmpty) {
        (R_sum, G_sum, B_sum, A_sum)
      }
      else {
        val (r, g, b, a) = separate(colors.head)
        mixer(colors.tail, r + R_sum, g + G_sum, b + B_sum, a + A_sum)
      }
    }
    var neighbours: List[Int] = List()
    var w_l = x - radius
    var w_u = x + radius
    var h_l = y - radius
    var h_u = y + radius
    if (w_l < 0) {
      w_l = 0
    }
    if (h_l < 0) {
      h_l = 0
    }
    if (w_u > picture.w - 1) {
      w_u = picture.w - 1
    }
    if (h_u > picture.h - 1) {
      h_u = picture.h - 1
    }
    for (i <- w_l until w_u + 1; j <- h_l until h_u + 1) {
      neighbours = picture(i, j) :: neighbours
    }
    val divisor = neighbours.length
    val (r_sum, g_sum, b_sum, a_sum) = mixer(neighbours, 0, 0, 0, 0)
    compound((r_sum / divisor, g_sum / divisor, b_sum / divisor, a_sum / divisor))
  }
  def horizontal_blur(pic: IMG, r: Int, period: Int): IMG = {
    val new_img = new IMG(pic.w, pic.h)
    val tasks_list = Range(0, pic.h) by period
    val tasks = tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          if ((k + period) > pic.h) {
            for (i <- 0 until pic.w; j <- k until pic.h) {
              new_img(i, j) = Blur(pic, r, i, j)
            }
          }
          else {
            for (i <- 0 until pic.w; j <- k until (k + period)) {
              new_img(i, j) = Blur(pic, r, i, j)
            }
          }
        }
      }
    })
    tasks.foreach(k => k.start)
    tasks.foreach(k => k.join)
    new_img
  }
  def vertical_blur(pic: IMG, r: Int, period: Int): IMG = {
    var new_img = new IMG(pic.w, pic.h)
    val tasks_list = Range(0, pic.w) by period
    val tasks = tasks_list.map(k => {
      new Thread {
        override def run(): Unit = {
          if ((k + period) > pic.w) {
            for (i <- 0 until pic.h; j <- k until pic.w) {
              new_img(j, i) = Blur(pic, r, j, i)
            }
          }
          else {
            for (i <- 0 until pic.h; j <- k until (k + period)) {
              new_img(j, i) = Blur(pic, r, j, i)
            }
          }
        }
      }
    })
    tasks.foreach(k => k.start)
    tasks.foreach(k => k.join)
    new_img
  }
  def get_image(name: String): IMG = {
    val jpg: BufferedImage = ImageIO.read(new File(name))
    val image = new IMG(jpg.getWidth, jpg.getHeight)
    for (i <- 0 until image.w; j <- 0 until image.h) {
      image(i, j) = (jpg.getRGB(i, j) << 8)
    }
    image
  }
  def image_for_render(image: BLUR.IMG): Array[Array[Color]] = {
    val acc: Array[Array[Color]] = Array.ofDim[Color](image.w, image.h)
    def get_color(col: Int): Color = {
      val color = BLUR.separate(col)
      new Color(color._1, color._2, color._3)
    }
    for (i <- 0 until image.w; j <- 0 until image.h) {
      acc(i)(j) = get_color(image(i, j))
    }
    acc
  }
  def unite_pics_hor(first: Array[Array[Color]], second: Array[Array[Color]], width: Int, height: Int): Array[Array[Color]] = {
    val acc: Array[Array[Color]] = Array.ofDim[Color](width * 2 + 1, height)
    for (i <- 0 until width; j <- 0 until height) {
      acc(i)(j) = first(i)(j)
    }
    for(i <- 0 until height) {
      acc(width)(i) = Color.BLACK
    }
    for(i <- width + 1 until width * 2 + 1; j <- 0 until height) {
      acc(i)(j) = second(i - width - 1)(j)
    }
    acc
  }
  def unite_pics_ver(first: Array[Array[Color]], second: Array[Array[Color]], width: Int, height: Int): Array[Array[Color]] = {
    val acc: Array[Array[Color]] = Array.ofDim[Color](width, height * 2 + 1)
    for (i <- 0 until width; j <- 0 until height) {
      acc(i)(j) = first(i)(j)
    }
    for(i <- 0 until width) {
      acc(i)(height) = Color.BLACK
    }
    for(i <- 0 until width; j <- height + 1 until height * 2 + 1) {
      acc(i)(j) = second(i)(j - height - 1)
    }
    acc
  }
  def top = new MainFrame {
    val blur_type = readLine("Choose one of the blur types:\nv - for vertical\nh - for horizontal\n")
    val radius = readLine("Choose the radius of blur:\n")
    val period = readLine("Choose the number of lines/columns processed in one thread:\n")
    val input = readLine("Type the name of input image:\n")
    val output = readLine("Type the name of output file:\n")
    val jpg: BufferedImage = ImageIO.read(new File(input))
    val image = new IMG(jpg.getWidth, jpg.getHeight)
    for (i <- 0 until image.w; j <- 0 until image.h) {
      image(i, j) = (jpg.getRGB(i, j) << 8)
    }
    val picture_before = image_for_render(image)
    var picture_after: Array[Array[Color]] = Array.ofDim[Color](image.w, image.h)
    blur_type match {
      case "v" => val apply_blur = vertical_blur(image, radius.toInt, period.toInt)
        for (i <- 0 until image.w; j <- 0 until image.h) {
          jpg.setRGB(i, j, (apply_blur(i, j) >>> 8))
        }
        picture_after = image_for_render(apply_blur)
      case "h" => val apply_blur = horizontal_blur(image, radius.toInt, period.toInt)
        for (i <- 0 until image.w; j <- 0 until image.h) {
          jpg.setRGB(i, j, (apply_blur(i, j) >>> 8))
        }
        picture_after = image_for_render(apply_blur)
    }
    ImageIO.write(jpg, "jpg", new File(output))
    if (image.h >= image.w) {
      val compound = unite_pics_hor(picture_before, picture_after, image.w, image.h)
      contents = new DataPanel(compound) {
        preferredSize = new Dimension(image.w * 2 + 1, image.h)
      }
    }
    else {
      val compound = unite_pics_ver(picture_before, picture_after, image.w, image.h)
      contents = new DataPanel(compound) {
        preferredSize = new Dimension(image.w, image.h * 2 + 1)
      }
    }
  }
}