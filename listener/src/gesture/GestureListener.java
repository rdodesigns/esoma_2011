/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 44 [master] (Sun Feb 13 04:17:21 EST 2011)
 * @parent 426daa04f78e6e09361d6fccffd6e0c548cf4f24
 *
 * @section DESCRIPTION
 *
 * Listen for Gestures parent class.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 *
 */
import processing.core.PVector;

import java.util.Observer;

public abstract class GestureListener implements Observer
{

  static final int pts_t = 256;
  static final int smpl  = 32;
  int smpl_offset; // Define differently for each class
  DrawStack draw_stack;

  protected float getPercentExtension(int limb, PVector[] joints)
  {
    PVector origin = joints[limb];
    PVector second = joints[limb+1];
    PVector third  = joints[limb+2];

    float hyp_dist  =  PVector.dist(origin, third);
    float side_dist = PVector.dist(origin, second)
                    + PVector.dist(second, third);

    return hyp_dist/side_dist;

  }

  void addDrawStack(DrawStack draw_stack)
  {
    this.draw_stack = draw_stack;
  }



  protected void setSampleOffset(int offset){
    smpl_offset = offset;
  }


}
