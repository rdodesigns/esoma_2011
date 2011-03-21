/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 71 [datacollector] (Mon Mar 21 02:00:56 EDT 2011)
 * @parent f78bd7d036fabcf3e64bf15c5d9b1cc202fb081c
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


float ExtensionCollector::getExtension()
{
  float proximal_length = getDistance(skeleton->joints[limb.num], skeleton->joints[limb.num+1]);
  float distal_length = getDistance(skeleton->joints[limb.num+1], skeleton->joints[limb.num+2]);
  float total_length = getDistance(skeleton->joints[limb.num], skeleton->joints[limb.num+2]);

  return ((proximal_length + distal_length) / total_length);
}

void ExtensionCollector::collectData()
{

}
