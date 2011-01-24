/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 26 [master] (Mon Jan 24 11:08:36 EST 2011)
 * @parent f786ee0d314d9f7fefb3fadb274f97a7b54208a2
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
