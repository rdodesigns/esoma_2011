/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 21 [master] (Sat Jan 22 02:49:12 EST 2011)
 * @parent d2daf7d110ac3e419c415876621e52a01c4a76b0
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

public class phinect_listener extends PApplet {

  Skeleton skeleton;
  Socket  info_grab;

  public void setup() {
    size(640,480, OPENGL);
    frameRate(30);

    info_grab  = new Socket();
    skeleton = new Skeleton(this, info_grab, 1);
  }

  public void draw() {

    background(0);
    lights();
    camera(0f, 0f, 0f, -272.6f, -111.8f, 2972.2f, 0f, -1f, 1f);

    skeleton.drawSkeleton();


    // End 3D
    camera();
    javax.media.opengl.GL gl=((PGraphicsOpenGL)g).beginGL();
    gl.glClear(javax.media.opengl.GL.GL_DEPTH_BUFFER_BIT);
    gl.glDisable(javax.media.opengl.GL.GL_BLEND);
    ((PGraphicsOpenGL)g).endGL();

    // Begin 2D
    skeleton.draw2DData();
  }

  public static void main(String args[]) {
    PApplet.main(new String[] { "phinect_listener" });
  }

}

