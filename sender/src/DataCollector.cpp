/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 71 [datacollector] (Mon Mar 21 02:00:56 EDT 2011)
 * @parent f78bd7d036fabcf3e64bf15c5d9b1cc202fb081c
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

float DataCollector::getDistance(XnVector3D vec1, XnVector3D vec2)
{
  return sqrt(pow(vec1.X - vec2.X, 2) + pow(vec1.Y - vec2.Y, 2) + pow(vec1.Z - vec2.Z, 2));
}
