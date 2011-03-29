/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 106 [complete_skel] (Mon Mar 28 20:14:40 EDT 2011)
 * @parent 5af5a331fa4bb1e7b44b87ff7dbf570e3835be5a
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
  // The extensions are only based on the three limb points.
  float proximal_length = getDistance(data[BASE], data[PROXIMAL]);
  float distal_length = getDistance(data[PROXIMAL], data[DISTAL]);
  float direct_length = getDistance(data[BASE], data[DISTAL]);

  return (direct_length / (proximal_length + distal_length) );
}

void ExtensionCollector::update(CoordinateData3D& in_joints)
{
  data.clear();

  for (int i = limb.num; i < limb.num + 3; i++)
    data.addXnVector3D(in_joints.at(i));
  float throw_away = getExtension();
}
