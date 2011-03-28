/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 104 [build_system] (Mon Mar 28 03:32:22 EDT 2011)
 * @parent c0f3df27ccf168ef3344cf194d287b22ce2ab018
 *
 * @section DESCRIPTION
 *
 * A template class for collecting data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */

#include "DataCollector.h"

DataCollector::DataCollector (Skeleton *skel) : skeleton(skel)
{
  skeleton->addCollector(this);
}

float DataCollector::getDistance(XnVector3D vec1, XnVector3D vec2)
{
  return sqrt(pow(vec1.X - vec2.X, 2) + pow(vec1.Y - vec2.Y, 2) + pow(vec1.Z - vec2.Z, 2));
}
