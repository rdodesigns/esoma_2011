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

import processing.core.*;

import peasy.PeasyCam;

import java.util.HashSet;
import java.util.Set;
import java.util.Iterator;

public class DrawStack
{

  protected PApplet draw;
  protected PeasyCam camera;

  private Set<DrawableObject> draw_objects;

  DrawStack(PApplet parent, PeasyCam cam){
    draw = parent;
    camera = cam;

    draw_objects = new HashSet<DrawableObject>();

    DrawableObject.addDrawPointer(draw);
    DrawableObject.addCamera(camera);
  }

  public <E extends DrawableObject> boolean add(E drawable_object)
  {
    return draw_objects.add(drawable_object);
  }

  public <E extends DrawableObject> boolean remove(E drawable_object)
  {
    return draw_objects.remove(drawable_object);
  }

  public void drawAll()
  {
    Iterator<DrawableObject> it = draw_objects.iterator();
    while (it.hasNext()) {
      DrawableObject element = it.next();
      element.draw();
    }

    draw_objects.clear();
  }

}
