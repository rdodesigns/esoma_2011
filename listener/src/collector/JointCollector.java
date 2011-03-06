/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 62 [datacollector] (Sun Mar  6 10:50:08 EST 2011)
 * @parent 2071cf1994accd684ce75b738fe1eb75002eed62
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
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 *
 */
import java.util.Observable;

import java.util.ArrayList;

public class JointCollector extends DataCollector
{
  private ArrayList[] joints;

  public void update(Observable skeleton, Object o)
  {
    System.out.println("Listening to extension");
  }

} // end class
