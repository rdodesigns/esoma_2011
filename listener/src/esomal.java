/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * A Processing based visualization for the data obtained from the MS Kinect.
 * Interfaces with a C++ program (esomas) to obtain skeletal points of a
 * player, and then shows this player's body on screen along with some
 * calculated physiological parameters. Performs gesture recognition to give a
 * score of a patients progress in a particular excerise as a method of
 * creating better patient compliance with physical therapy treatments between
 * doctors visits.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 * Resources and brainstorming assistance provided through a collaboration with
 * the MIT Media Lab and Tufts University. Contact information is provided
 * below.
 *
 * Ryan Orendorff
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 *
 * Dr. John Moore
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 * Professor Fiorenzo Omenetto
 * Tufts University
 * Department of Biomedical Engineering
 * 4 Colby Street
 * Medford, MA 02155 USA
 */

import processing.core.*;
import processing.xml.*;
import processing.opengl.*;

import peasy.*;

public class esomal extends PApplet {

  Skeleton skeleton;
  DrawStack draw_stack;
  Socket  socket;

  PeasyCam cam;

  public void setup() {
    size(1024,768, OPENGL);
    frameRate(30);
    frame.setResizable(true);

    // Set Camera
    cam = new PeasyCam(this, -424.8 ,86.8, 1504.1, 1500 );
    draw_stack = new DrawStack(this, cam);
    cam.setMinimumDistance(0);
    cam.setMaximumDistance(4000);
    cam.rotateX(-2.9755113);
    cam.rotateY(-0.026724178);
    cam.rotateZ(-0.04521484);

    // Skeleton Tracking
    socket  = new Socket();
    skeleton = new Skeleton(socket, draw_stack, 1);

    skeleton.AttachGestureListener(new ElbowBendListener());
  }

  public void draw() {

    background(0);

    skeleton.updateSkeleton();

    draw_stack.drawAll();
  }

  public static void main(String args[]) {
    PApplet.main(new String[] { "esomal" });
  }

}

