/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 43 [draw] (Sun Feb 13 04:13:01 EST 2011)
 * @parent 9ba9cbadd4ae5d01d993271a392a13aeeab09f1c
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
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
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

