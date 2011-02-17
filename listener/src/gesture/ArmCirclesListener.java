/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 55 [windows] (Wed Feb 16 23:04:02 EST 2011)
 * @parent 6e327a7504538998cdeac4b26cbff67fde609109
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
