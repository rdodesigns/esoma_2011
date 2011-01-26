/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 30 [analysis] (Wed Jan 26 03:09:00 EST 2011)
 * @parent bc56c6681eca8fc3bd91849fdd94c26d54688c7f
 *
 * @section DESCRIPTION
 *
 * A Processing based visualization for the data obtained from the MS Kinect.
 * Interfaces with a C++ program (phinect_sender) to obtain skeletal points
 * of a player, and then shows this player's body on screen along with some
 * calculated physiological parameters. Performs gesture recognition to give
 * a score of a patients progress in a particular excerise as a method of
 * creating better patient compliance with physical therapy treatments
 * between doctors visits.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 */

import processing.core.*;
import processing.xml.*;
import processing.opengl.*;

import peasy.*;

public class phinect_listener extends PApplet {

  Skeleton skeleton;
  Socket  info_grab;

  PeasyCam cam;

  public void setup() {
    size(640,480, OPENGL);
    frameRate(30);
    frame.setResizable(true);

    // Set Camera
    cam = new PeasyCam(this, -424.8 ,86.8, 1504.1, 1500 );
    cam.setMinimumDistance(0);
    cam.setMaximumDistance(4000);
    cam.rotateX(-2.9755113);
    cam.rotateY(-0.026724178);
    cam.rotateZ(-0.04521484);

    // Skeleton Tracking
    info_grab  = new Socket();
    skeleton = new Skeleton(this, info_grab, 1);

    skeleton.AttachGestureListener(new ElbowBendListener(this, cam));
  }

  public void draw() {

    background(0);

    skeleton.drawSkeleton();

    PVector offset = skeleton.getNormalOffset();
    //PVector offset = new PVector(3,4);
    // 2D
    cam.beginHUD();
    pushMatrix();
    pushStyle();
    stroke(255,255,255);
    noFill();
    translate(width/4, super.height/2  );
    offset.mult(30);
    offset.limit(30);
    strokeWeight(2);
    line(0,0,offset.x, offset.y);
    strokeWeight(1);
    ellipse(0,0, 100, 100);
    popStyle();
    popMatrix();
    cam.endHUD();
  }

  public static void main(String args[]) {
    PApplet.main(new String[] { "phinect_listener" });
  }

}

