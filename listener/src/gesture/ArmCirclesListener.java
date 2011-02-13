/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 44 [master] (Sun Feb 13 04:17:21 EST 2011)
 * @parent 426daa04f78e6e09361d6fccffd6e0c548cf4f24
 *
 * @section DESCRIPTION
 *
 * Listen for the Arm Cirlces movement, which looks at the parameters of arm
 * extension, arm direction and how close the arms are to the torse to
 * determine the speed of the activity and the maximum extension.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 *
 */
import java.util.Observer;
import java.util.Observable;

public class ArmCirclesListener extends GestureListener
{

  ArmCirclesListener()
  {

  }

  public void update(Observable skeleton, Object o){
    System.out.println("Circling arms!");
  }


} // end class
