/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * Listen for the Elbow Bend movement, which looks at the parameters of arm
 * extension, arm direction and how close the arms are to the torse to
 * determine the speed of the activity and the maximum extension.
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
import java.util.Observable;

import java.util.ArrayList;

public class ElbowBendListener extends GestureListener
{

  private ArrayList<Float> larm_dist;
  private ArrayList<Float> larm_dist_smooth;
  private ArrayList<Float> larm_dist_der;
  private ArrayList<Float> larm_dist_conv;
  private ArrayList<Float> rarm_dist;

  private ArrayList<Integer> peaks;
  private ArrayList<Integer> peaks_der_max;
  private ArrayList<Integer> peaks_der_min;

  ElbowBendListener()
  {
    System.out.println("Elbow Gesture Listener Instantiated");

    larm_dist = new ArrayList<Float>(pts_t);
    larm_dist_smooth = new ArrayList<Float>(pts_t);
    larm_dist_der = new ArrayList<Float>(pts_t);
    larm_dist_conv = new ArrayList<Float>(pts_t);
    rarm_dist = new ArrayList<Float>(pts_t);

    peaks = new ArrayList<Integer>();
    peaks_der_max = new ArrayList<Integer>();
    peaks_der_min = new ArrayList<Integer>();


    // Pad arrays with 256 0s as a start. This size is held constant.
    for (int i = 0; i < pts_t; i++){
      larm_dist.add(0.0f);
      rarm_dist.add(0.0f);
      larm_dist_smooth.add(0.0f);
      larm_dist_der.add(0.0f);
      larm_dist_conv.add(0.0f);
    }

  }

  public void update(Observable skeleton, Object o){
    larm_dist.remove(0);
    rarm_dist.remove(0);
    larm_dist.add(this.getPercentExtension(3, ((Skeleton) skeleton).getSkeleton()));
    rarm_dist.add(this.getPercentExtension(6, ((Skeleton) skeleton).getSkeleton()));

    smpl_offset = (smpl_offset + 1) % smpl;
    if (smpl_offset == 0){

      // This exists because removeRange is a protected void, requiring the
      // class to extend ArrayList
      for (int i = 0; i < smpl; i++){
        larm_dist_smooth.remove(0);
        larm_dist_der.remove(0);
      }

      // Calculate the smoothed spectrum and derivative.
      larm_dist_smooth.addAll(Filters.smoothing(larm_dist, smpl));
      larm_dist_der.addAll(Filters.derivative(larm_dist, smpl));

      // Find peaks in signal and signal's derivative.
      Filters.peakDetection(larm_dist_smooth, 0.1f, peaks, null);
      Filters.peakDetection(larm_dist_der, 0.1f, peaks_der_max, peaks_der_min);
    }

    // Add left arm extension to the drawing stack.
    draw_stack.add(new DrawGraph(larm_dist_smooth, 10, 400, 0xffE41A1C));

  }

} // end class
