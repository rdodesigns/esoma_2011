/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 19 [cleanup] (Sat Jan 22 00:09:41 EST 2011)
 * @parent eb7eb6da42f2dee113645525b3328ba7af3cd96d
 *
 * Phinect Listener
 * A proce
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

    info_grab  = new Socket(this);
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

