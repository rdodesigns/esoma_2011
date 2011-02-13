/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 38 [analysis] (Sat Feb 12 20:44:05 EST 2011)
 * @parent d212d6477193323b0efe69c45e874c10fe85d10d
 *
 * @section DESCRIPTION
 *
 * Listen for Gestures parent class.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
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

  protected void setSampleOffset(int offset){
    smpl_offset = offset;
  }


}
