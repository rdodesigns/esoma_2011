/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 29 [analysis] (Tue Jan 25 04:13:30 EST 2011)
 * @parent 68581a5bdd351abcee32595aa5d54b97bb43ac06
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
  ArrayList<Float> larm_dist_der;
  ArrayList<Float> rarm_dist;

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
    rarm_dist = new ArrayList<Float>(pts_t);

    for (int i = 0; i < pts_t; i++){
      larm_dist.add(0.0f);
      rarm_dist.add(0.0f);
      larm_dist_smooth.add(0.0f);
      larm_dist_der.add(0.0f);
    }

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


  protected void draw()
  {
    parent.pushStyle();

    parent.pushMatrix();

      parent.translate(10, parent.height/4 + 20);

      parent.strokeWeight(2);
      parent.stroke(0xffE41A1C);


      for (int j = 0; j < larm_dist_smooth.size() - 1; j++){
        float pt1 = (Float) larm_dist_smooth.get(j);
        float pt2 = (Float) larm_dist_smooth.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }


    parent.popMatrix();

    parent.pushMatrix();

      parent.translate(10, parent.height/4 + 20);

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


    parent.popMatrix();
    parent.popStyle();
  }

} // end class
