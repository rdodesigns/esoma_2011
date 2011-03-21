/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * A public abstract class for unifying how draws are done.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 *
 * Contact Information
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
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
