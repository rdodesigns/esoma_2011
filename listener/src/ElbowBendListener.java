/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 42 [cleanup] (Sun Feb 13 00:23:04 EST 2011)
 * @parent d0c6fbc0092683979cf734d67ad2e0c07cda2048
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
import java.util.Arrays;
import java.lang.Math;

public class ElbowBendListener extends GestureListener
{

  ArrayList<Float> larm_dist;
  ArrayList<Float> larm_dist_smooth;
  ArrayList<Float> larm_dist_der;
  ArrayList<Float> larm_dist_conv;
  ArrayList<Float> rarm_dist;

  ArrayList<Integer> peaks;
  ArrayList<Integer> peaks_der_max;
  ArrayList<Integer> peaks_der_min;

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

  }

} // end class
