/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 43 [draw] (Sun Feb 13 04:13:01 EST 2011)
 * @canvas d0c6fbc0092683979cf734d67ad2e0c07cda2048
 *
 * @section DESCRIPTION
 *
 * Draw an arbitrary ArrayList.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */

import processing.core.*;

import java.util.ArrayList;

public class DrawGraph extends DrawableObject
{
  private ArrayList<Float> array;
  private int color;
  private int pos_x, pos_y;

  DrawGraph(ArrayList<Float> array, int pos_x, int pos_y, int color)
  {
    this.array    = array;
    this.color    = color;
    this.pos_x = pos_x;
    this.pos_y = pos_y;
  }

  public void draw()
  {
    camera.beginHUD();

    canvas.pushStyle();
    canvas.pushMatrix();

      canvas.translate(pos_x, pos_y);

      canvas.strokeWeight(2);
      canvas.stroke(0xffE41A1C);


      for (int j = 0; j < array.size() - 1; j++){
        float pt1 = array.get(j);
        float pt2 = array.get(j+1);
        canvas.line(j, -(canvas.height/4)*pt1, j + 1, -(canvas.height/4)*pt2);
      }

    canvas.popMatrix();
    canvas.popStyle();

    camera.endHUD();
  }


}
