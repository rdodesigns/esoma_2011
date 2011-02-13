/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 38 [analysis] (Sat Feb 12 20:44:05 EST 2011)
 * @parent d212d6477193323b0efe69c45e874c10fe85d10d
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
 * E14, 20 Ames Street
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
