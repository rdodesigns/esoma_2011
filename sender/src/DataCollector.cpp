/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 72 [datacollector] (Mon Mar 21 02:49:10 EDT 2011)
 * @parent 8915da6c46e020833a3f13744b6e2daa8cceeaa9
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
