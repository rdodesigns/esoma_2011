/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 63 [datacollector] (Sun Mar  6 10:30:11 PST 2011)
 * @parent 5292611a77495c3077f9bec5da87f969401ae8d6
 *
 * @section DESCRIPTION
 *
 * A template class for collecting extension data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
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
}


ExtensionCollector::~ExtensionCollector()
{
}

void ExtensionCollector::printSomething()
{
  std::cout << "ExtensionCollector for limb " << limb.name << " initiated.\n";
}
