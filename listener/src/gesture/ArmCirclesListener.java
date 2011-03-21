/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * Listen for the Arm Cirlces movement, which looks at the parameters of arm
 * extension, arm direction and how close the arms are to the torse to
 * determine the speed of the activity and the maximum extension.
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
