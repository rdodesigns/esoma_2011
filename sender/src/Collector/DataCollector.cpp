/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 105 [complete_skel] (Mon Mar 28 18:30:26 EDT 2011)
 * @parent ce6d1e9e39faea4077d384d3e2bd369c537e1330
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

#include <Collector/DataCollector.h>

DataCollector::DataCollector (Skeleton *skel) : skeleton(skel)
{
  skeleton->addCollector(this);
}

float DataCollector::getDistance(XnVector3D vec1, XnVector3D vec2)
{
  return sqrt(pow(vec1.X - vec2.X, 2) + pow(vec1.Y - vec2.Y, 2) + pow(vec1.Z - vec2.Z, 2));
}
