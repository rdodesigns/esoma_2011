/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 43 [draw] (Sun Feb 13 04:13:01 EST 2011)
 * @canvas d0c6fbc0092683979cf734d67ad2e0c07cda2048
 *
 * @section DESCRIPTION
 *
 * Draw the skeleton based on a series of PVectors.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */

import processing.core.*;

public class DrawSkeleton extends DrawableObject
{
  private final int larm_color = 0xffE41A1C; ///< Red
  private final int rarm_color = 0xff377EB8; ///< Blue
  private final int lleg_color = 0xff4DAF4A; ///< Green
  private final int rleg_color = 0xff984EA3; ///< Purple

  PVector[] joints;

  DrawSkeleton(PVector[] joints)
  {
    this.joints = joints;
  }

  public void draw()
  {
    canvas.pushStyle();
    canvas.fill(255,255,255);

    //for (PVector vec: joints) {
    for (int i = 0; i < joints.length; i++){
      canvas.pushMatrix();
      canvas.translate(joints[i].x,joints[i].y,joints[i].z);

      if (i == 1)
        canvas.ambientLight(255,255,255);

      if ( i >=3 && i <=5)
        canvas.fill(larm_color);
      else if ( i >=6 && i <=8)
        canvas.fill(rarm_color);
      else if ( i >=9 && i <=11)
        canvas.fill(lleg_color);
      else if ( i >=12 && i <=14)
        canvas.fill(rleg_color);

      canvas.box(50);
      canvas.popMatrix();
    }
    canvas.popStyle();
  }


}
