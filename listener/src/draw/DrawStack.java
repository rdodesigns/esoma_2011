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

    draw_objects = new HashSet();

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
