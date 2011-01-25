/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 27 [analysis] (Tue Jan 25 02:37:51 EST 2011)
 * @parent 7e2b7f0eec705d6755a8679bda9052873660306e
 *
 * @section DESCRIPTION
 *
 * Listen for the Elbow Bend movement, which looks at the parameters of arm
 * extension, arm direction and how close the arms are to the torse to
 * determine the speed of the activity and the maximum extension.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 */
import java.util.Observer;
import java.util.Observable;

import java.util.ArrayList;


import peasy.*;
import processing.core.*;

public class ElbowBendListener extends GestureListener
{

  ArrayList<Float> larm_dist;
  ArrayList<Float> larm_dist_smooth;
  ArrayList<Float> rarm_dist;

  ElbowBendListener()
  {
    System.out.println("Elbow Gesture Listener Instantiated");

    larm_dist = new ArrayList<Float>(pts_t);
    larm_dist_smooth = new ArrayList<Float>(pts_t);
    rarm_dist = new ArrayList<Float>(pts_t);

    for (int i = 0; i < pts_t; i++){
      larm_dist.add(0.0f);
      rarm_dist.add(0.0f);
      larm_dist_smooth.add(0.0f);
    }

  }

  public void update(Observable skeleton, Object o){
    larm_dist.remove(0);
    rarm_dist.remove(0);
    larm_dist.add(this.getPercentExtension(3, ((Skeleton) skeleton).getSkeleton()));
    rarm_dist.add(this.getPercentExtension(6, ((Skeleton) skeleton).getSkeleton()));

    smpl_offset = (smpl_offset + 1) % smpl;
    if (smpl_offset == 0)
      smoothingFilter();


    //cam.beginHUD();
    //draw();
    //cam.endHUD();
  }

  /**
   * Savitzky-Golay Smoothing filter of nine points.
   *
   * Paper:
   * Savitzky and Golay. Smoothing and differentiation of data by simplified
   * least squares procedures. Analytical chemistry (1964)
   *
   * @param array Array to filter
   */
  protected void smoothingFilter()
  {
    float sum;
    int[] consts = {-21,14,39,54,59,54,39,14,-21};  // 9-point SG filter coefficients
    int znorm = 231;
    int L=9;
    int iloop = (L-1)/2;

    for (int i=pts_t-smpl-iloop; i < (pts_t-iloop); i++)
    {
      sum=0;
      for (int j=0 ; j<L ; j++) // loop c(0) to c(8) = 9 points
        sum = sum + (consts[j] * larm_dist.get(i-iloop+j));

      larm_dist_smooth.remove(0);
      larm_dist_smooth.add(sum / znorm);
    }

  }

  protected void draw()
  {

  }

} // end class
