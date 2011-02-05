/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 31 [analysis] (Fri Feb  4 22:22:29 EST 2011)
 * @parent 0ee25ddad17d29497f8062587f6bfc5ec26d1b87
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

import peasy.*;
import processing.core.*;

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

  float[] gen_norm_2;

  PeasyCam cam;
  PApplet parent;

  ElbowBendListener(PApplet parent, PeasyCam cam)
  {
    this.parent = parent;
    this.cam = cam;
    System.out.println("Elbow Gesture Listener Instantiated");

    larm_dist = new ArrayList<Float>(pts_t);
    larm_dist_smooth = new ArrayList<Float>(pts_t);
    larm_dist_der = new ArrayList<Float>(pts_t);
    larm_dist_conv = new ArrayList<Float>(pts_t);
    rarm_dist = new ArrayList<Float>(pts_t);

    peaks = new ArrayList<Integer>();
    peaks_der_max = new ArrayList<Integer>();
    peaks_der_min = new ArrayList<Integer>();


    for (int i = 0; i < pts_t; i++){
      larm_dist.add(0.0f);
      rarm_dist.add(0.0f);
      larm_dist_smooth.add(0.0f);
      larm_dist_der.add(0.0f);
      larm_dist_conv.add(0.0f);
    }

    gen_norm_2 = new float[80];

    for (int i = 0; i < 48; i++)
      gen_norm_2[i] = 0;
    for (int i = 0; i < 32; i++)
      gen_norm_2[i+48] = (float)(-2*(-3+0.1875*i)*Math.exp(-(Math.pow(-3+0.1875*i,2))));

  }

  public void update(Observable skeleton, Object o){
    larm_dist.remove(0);
    rarm_dist.remove(0);
    larm_dist.add(this.getPercentExtension(3, ((Skeleton) skeleton).getSkeleton()));
    rarm_dist.add(this.getPercentExtension(6, ((Skeleton) skeleton).getSkeleton()));

    smpl_offset = (smpl_offset + 1) % smpl;
    if (smpl_offset == 0){
      smoothingFilter();
      derivativeFilter();
      convolutionArm();
      peakDetection(larm_dist_smooth, 0.1f, peaks, null);
      peakDetection(larm_dist_der, 0.1f, peaks_der_max, peaks_der_min);
    }


    cam.beginHUD();
    draw();
    cam.endHUD();
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

  protected void derivativeFilter()
  {
    float sum;
    //int[] consts = {-21,14,39,54,59,54,39,14,-21};  // 9-point SG filter coefficients
    int[] consts = {-4, -3, -2, -1, 0, 1, 2, 3, 4};  // 9-point SG filter coefficients
    int znorm = 60;
    //int znorm = 231;
    int L=9;
    int iloop = (L-1)/2;

    for (int i=pts_t-smpl-iloop; i < (pts_t-iloop); i++)
    {
      sum=0;
      for (int j=0 ; j<L ; j++) // loop c(0) to c(8) = 9 points
        sum = sum + (consts[j] * larm_dist.get(i-iloop+j));

      larm_dist_der.remove(0);
      larm_dist_der.add(sum / znorm);
    }

  }

  protected void convolutionArm()
  {
    float sum;

    for (int i = 0; i < smpl; i++) {
      larm_dist_conv.remove(0);
      sum = 0;
      for (int j = 0; j < smpl; j++) {
        if (64 + j - i >=80) continue;
        sum += larm_dist_der.get(pts_t-smpl+j)*gen_norm_2[64-i+j];
      }
      larm_dist_conv.add(sum);
    }

  }

  protected void peakDetection(ArrayList<Float> array, float delta, ArrayList<Integer> output_max, ArrayList<Integer> output_min)
  {
    float mn = 1.5f;
    float mx = -1.5f;
    int mnpos = -1, mxpos = -1;

    output_max.clear();
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
          output_max.add(mxpos);
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

  protected float calculateSpeed()
  {
    float speed =0;
    int i;
    for (i = 0; i < peaks.size() - 1; i++) {
      speed += (peaks.get(i+1) - peaks.get(i));
    }

    return (speed/i)/30;
  }

  protected float calculateLengthTime()
  {
    float speed = 0;
    int i;
    int smaller = (peaks_der_max.size() > peaks_der_min.size()) ? peaks_der_min.size() : peaks_der_max.size();

    for (i = 0; i < smaller; i++) {
      speed += peaks_der_min.get(i) - peaks_der_max.get(i);
    }

    return (speed/i)/30;
  }

  protected void draw()
  {
    parent.pushStyle();

    parent.pushStyle();
    parent.pushMatrix();
      parent.fill(255,255,255);
      parent.text(Float.toString(calculateSpeed()) + " sec/rep", 190, 10);
    parent.popMatrix();
    parent.popStyle();

    parent.pushMatrix();

      parent.translate(10, parent.height/4 + 20);

      parent.strokeWeight(2);
      parent.stroke(0xffE41A1C);


      for (int j = 0; j < larm_dist_smooth.size() - 1; j++){
        float pt1 = (Float) larm_dist_smooth.get(j);
        float pt2 = (Float) larm_dist_smooth.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }

      parent.stroke(255,255,255);
      parent.ellipseMode(parent.CENTER);
      for (Integer value: peaks){
        parent.ellipse(value, larm_dist_smooth.get(value) * -(parent.height/4), 4, 4);
      }

    parent.popMatrix();

    parent.pushMatrix();

      parent.translate(10, parent.height/4 + 20);

      parent.text(Float.toString(calculateLengthTime()) + " sec (length of bend)", 120, 30);
      parent.strokeWeight(1);
      parent.stroke(255,255,255, 192);
      parent.line(0,0,larm_dist_der.size(), 0);
      parent.strokeWeight(2);
      parent.stroke(0xff377EB8);


      for (int j = 0; j < larm_dist_der.size() - 1; j++){
        float pt1 = (Float) larm_dist_der.get(j);
        float pt2 = (Float) larm_dist_der.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }

      parent.stroke(255,255,255);
      for (Integer value: peaks_der_max)
        parent.ellipse(value, larm_dist_der.get(value)*-(parent.height/4), 4, 4);
      for (Integer value: peaks_der_min)
        parent.ellipse(value, larm_dist_der.get(value)*-(parent.height/4), 4, 4);


    parent.popMatrix();


    //parent.pushMatrix();

      //parent.translate(10, parent.height/4 + 40);

      //parent.strokeWeight(1);
      //parent.stroke(255,255,255, 192);
      //parent.line(0,0,larm_dist_conv.size(), 0);
      //parent.strokeWeight(2);
      //parent.stroke(0xff4DAF4A);


      //for (int j = 0; j < larm_dist_conv.size() - 1; j++){
        //float pt1 = (Float) larm_dist_conv.get(j);
        //float pt2 = (Float) larm_dist_conv.get(j+1);
        //parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      //}


    //parent.popMatrix();
    parent.popStyle();
  }

} // end class
