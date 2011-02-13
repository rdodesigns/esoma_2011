/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 41 [cleanup] (Sun Feb 13 00:10:46 EST 2011)
 * @parent 8c6c36a1702a453a8237d2068e86ebfda6a11196
 *
 * @section DESCRIPTION
 *
 * The algorithms used for analysis of the skeleton.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 */

import java.util.ArrayList;

public class Filters
{

  /**
   * Savitzky-Golay smoothing filter of nine points.
   *
   * Smooth a spectrum with a least squares fit over the entire spectrum.
   *
   * Paper:
   * Savitzky and Golay. Smoothing and differentiation of data by simplified
   * least squares procedures. Analytical chemistry (1964)
   *
   * @param array Array to filter
   */
  static public ArrayList<Float> smoothing(ArrayList<Float> array)
  {
    return smoothing(array, array.size() + 8); // The 8 is for 2*iloop
  }


  /**
   * Savitzky-Golay smoothing filter of nine points.
   *
   * Smooth a spectrum with a least squares fit over the last smpl points
   * of the spectrum.
   *
   * @param array Array to filter
   * @param smpl  Number of points from the end to look at.
   */
  static public ArrayList<Float> smoothing(ArrayList<Float> array, int smpl)
  {
    System.out.println("Array size = " + array.size());
    ArrayList<Float> output = new ArrayList<Float>(array.size());
    float sum;
    int[] consts = {-21,14,39,54,59,54,39,14,-21};  // 9-point SG filter coefficients
    int znorm = 231;
    int L=9;
    int iloop = (L-1)/2;

    for (int i=array.size()-smpl-iloop; i < (array.size()-iloop); i++)
    {
      sum=0;
      for (int j=0 ; j<L ; j++) // loop c(0) to c(8) = 9 points
        sum = sum + (consts[j] * array.get(i-iloop+j));

      output.add(sum / znorm);
    }

    return output;
  }

  /**
   * Savitzky-Golay derivative filter of nine points.
   *
   * First derivative a spectrum with a least squares fit over the entire
   * spectrum
   *
   * @param array Array to filter
   */
  static public ArrayList<Float> derivative(ArrayList<Float> array)
  {
    return derivative(array, array.size() + 8); // The 8 is for 2*iloop
  }

  /**
   * Savitzky-Golay derivative filter of nine points.
   *
   * First derivative a spectrum with a least squares fit over the last smpl
   * points of the spectrum.
   *
   * @param array Array to filter
   * @param smpl  Number of points from the end to look at.
   */
  static public ArrayList<Float> derivative(ArrayList<Float> array, int smpl)
  {
    ArrayList<Float> output = new ArrayList<Float>(array.size());
    float sum;
    int[] consts = {-4, -3, -2, -1, 0, 1, 2, 3, 4};  // 9-point SG filter coefficients
    int znorm = 60;
    int L=9;
    int iloop = (L-1)/2;

    for (int i=array.size()-smpl-iloop; i < (array.size()-iloop); i++)
    {
      sum=0;
      for (int j=0 ; j<L ; j++) // loop c(0) to c(8) = 9 points
        sum = sum + (consts[j] * array.get(i-iloop+j));

      output.add(sum / znorm);
    }

    return output;
  }


  static public void peakDetection(ArrayList<Float> array, float delta, ArrayList<Integer> output_max, ArrayList<Integer> output_min)
  {
    float mn = 1.5f;
    float mx = -1.5f;
    int mnpos = -1, mxpos = -1;

    if (output_max != null) output_max.clear();
    if (output_min != null) output_min.clear();

    boolean lookformax = true;

    for (int i = 0; i < array.size(); i++) {
      float instance = array.get(i);

      if (instance > mx) {
        mx = instance;
        mxpos = i;
        continue;
      }
      if (instance < mn) {
        mn = instance;
        mnpos = i;
        continue;
      }

      if (lookformax){
        if (instance < mx - delta){
          if (output_max != null) output_max.add(mnpos);
          mn = instance;
          mnpos = i;
          lookformax = false;
        }
      } else {
        if (instance > mn + delta) {
          if (output_min != null) output_min.add(mnpos);
          mx = instance;
          mxpos = i;
          lookformax = true;
        }
      }

    }
  }

  //static public float calculateSpeed()
  //{
    //float speed =0;
    //int i;
    //for (i = 0; i < peaks.size() - 1; i++) {
      //speed += (peaks.get(i+1) - peaks.get(i));
    //}

    //return (speed/i)/30;
  //}

  //protected float calculateLengthTime()
  //{
    //float speed = 0;
    //int i;
    //int smaller = (peaks_der_max.size() > peaks_der_min.size()) ? peaks_der_min.size() : peaks_der_max.size();

    //for (i = 0; i < smaller; i++) {
      //speed += peaks_der_min.get(i) - peaks_der_max.get(i);
    //}

    //return (speed/i)/30;
  //}



  //static public void convolution()
  //{
    //float sum;

    //for (int i = 0; i < smpl; i++) {
      //larm_dist_conv.remove(0);
      //sum = 0;
      //for (int j = 0; j < smpl; j++) {
        //if (64 + j - i >=80) continue;
        //sum += larm_dist_der.get(pts_t-smpl+j)*gen_norm_2[64-i+j];
      //}
      //larm_dist_conv.add(sum);
    //}

  //}
}