/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * Draw the skeleton based on a series of PVectors.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 *
 * Contact Information
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
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
