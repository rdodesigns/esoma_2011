/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 24 [master] (Mon Jan 24 03:39:23 EST 2011)
 * @parent 8de86979965f9413b8fff1b2676764c0254b7b29
 *
 * @section DESCRIPTION
 *
 * Listen for the Elbow Bend movement, which looks at the parameters of arm
 * extension, arm direction and how close the arms are to the torse to
 * determine the speed of the activity and the maximum extension.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 */
import java.util.Observer;
import java.util.Observable;

public class ElbowBendListener extends GestureListener
{

  ElbowBendListener()
  {

  }

  public void update(Observable thing, Object o){
    System.out.println("Bending Elbows!");
  }

} // end class
