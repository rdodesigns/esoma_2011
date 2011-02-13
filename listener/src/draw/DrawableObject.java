/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 47 [master] (Sun Feb 13 04:27:43 EST 2011)
 * @parent 83bc70362b251766ab104a1feeb6f67df4f0826e
 *
 * @section DESCRIPTION
 *
 * A public abstract class for unifying how draws are done.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */

import processing.core.PApplet;

import peasy.*;

public abstract class DrawableObject
{

  static PApplet canvas;
  static PeasyCam camera;

  static public void addDrawPointer(PApplet drawer)
  {
    if (canvas == null) canvas = drawer;
  }

  static public void addCamera(PeasyCam cam)
  {
    if (camera == null) camera = cam;
  }

  public abstract void draw();


}
