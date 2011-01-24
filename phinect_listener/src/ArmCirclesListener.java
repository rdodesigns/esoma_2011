/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 23 [master] (Mon Jan 24 03:22:12 EST 2011)
 * @parent b559be5a59f2cf47bd605326db26eccafd4b608f
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

import java.util.*;
import java.util.Observer;


public class ArmCirclesListener extends GestureListener
{

  ArmCirclesListener()
  {

  }

  public void update(Observable skeleton, Object o){
    System.out.println("Circling arms!");
  }


} // end class
