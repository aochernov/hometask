import scala.io.StdIn.readLine
import swing.{MainFrame, Panel, SimpleSwingApplication}
import java.awt.{Color, Dimension, Graphics2D}

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

object Draw extends SimpleSwingApplication {
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
    val number_of_processes = readLine("Choose the number of processes:\n")
    val input = readLine("Type the name of input image:\n")
    val image = BLUR.get_image(input)
    val picture_before = image_for_render(image)
    var picture_after: Array[Array[Color]] = Array.ofDim[Color](image.w, image.h)
    blur_type match {
      case "v" => val apply_blur = BLUR.vertical_blur(image, radius.toInt, number_of_processes.toInt)
        picture_after = image_for_render(apply_blur)
      case "h" => val apply_blur = BLUR.horizontal_blur(image, radius.toInt, number_of_processes.toInt)
        picture_after = image_for_render(apply_blur)
    }
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