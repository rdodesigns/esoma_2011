/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 41 [cleanup] (Sun Feb 13 00:10:46 EST 2011)
 * @parent 8c6c36a1702a453a8237d2068e86ebfda6a11196
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

      larm_dist_smooth.addAll(Filters.smoothing(larm_dist, smpl));
      larm_dist_der.addAll(Filters.derivative(larm_dist, smpl));
      Filters.peakDetection(larm_dist_smooth, 0.1f, peaks, null);
      Filters.peakDetection(larm_dist_der, 0.1f, peaks_der_max, peaks_der_min);
    }


    cam.beginHUD();
    draw();
    cam.endHUD();
  }


  protected void draw()
  {
    parent.pushStyle();

    parent.pushStyle();
    parent.pushMatrix();
      parent.fill(255,255,255);
      //parent.text(Float.toString(calculateSpeed()) + " sec/rep", 190, 10);
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

      //parent.text(Float.toString(calculateLengthTime()) + " sec (length of bend)", 120, 30);
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
    parent.popStyle();
  }

} // end class
