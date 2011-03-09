/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 70 [datacollector] (Wed Mar  9 02:46:34 PST 2011)
 * @parent 3e9ce6ed429180aed9ae40095c4e3b6f94f5caec
 *
 * @section DESCRIPTION
 *
 * A template class for collecting extension data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */

#include "ExtensionCollector.h"

ExtensionCollector::ExtensionCollector(Skeleton *skeleton, int limb_num) : DataCollector(skeleton)
{
  limb.num = limb_num;
  if (limb.num == LARM)
    limb.name = "Left Arm";
  else if (limb.num == RARM)
    limb.name = "Right Arm";
  else if (limb.num == LLEG)
    limb.name = "Left Leg";
  else if (limb.num == RLEG)
    limb.name = "Right Leg";

  std::cout << "ExtensionCollector for limb " << limb.name << " initiated.\n";
}


ExtensionCollector::~ExtensionCollector()
{
}


// TODO: Add extension calculations (note skeleton.joints[15] is protected).
float ExtensionCollector::getExtension()
{
  //Xn
}
