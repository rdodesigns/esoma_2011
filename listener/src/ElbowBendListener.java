/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 32 [master] (Fri Feb  4 23:07:28 EST 2011)
 * @parent 7e2b7f0eec705d6755a8679bda9052873660306e
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

  public void update(Observable skeleton, Object o){
    System.out.println("Bending Elbows!");
  }

} // end class
