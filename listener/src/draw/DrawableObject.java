/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 43 [draw] (Sun Feb 13 04:13:01 EST 2011)
 * @parent 9ba9cbadd4ae5d01d993271a392a13aeeab09f1c
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
    canvas = drawer;
  }

  static public void addCamera(PeasyCam cam)
  {
    camera = cam;
  }

  public abstract void draw();


}
