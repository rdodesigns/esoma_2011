/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 105 [complete_skel] (Mon Mar 28 18:30:26 EDT 2011)
 * @parent ce6d1e9e39faea4077d384d3e2bd369c537e1330
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

#include <Collector/ExtensionCollector.h>

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

#ifdef DEBUG
  std::cout << "ExtensionCollector for limb " << limb.name << " initiated.\n";
#endif
}


ExtensionCollector::~ExtensionCollector()
{
}


float ExtensionCollector::getExtension()
{
  float proximal_length = getDistance(skeleton->joints[limb.num], skeleton->joints[limb.num+1]);
  float distal_length = getDistance(skeleton->joints[limb.num+1], skeleton->joints[limb.num+2]);
  float direct_length = getDistance(skeleton->joints[limb.num], skeleton->joints[limb.num+2]);

  return (direct_length / (proximal_length + distal_length) );
}

void ExtensionCollector::update()
{
  float throw_away = getExtension();
}
