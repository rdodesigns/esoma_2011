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


#ifndef __ESOMAS__DATACOLLECTOR__
#define __ESOMAS__DATACOLLECTOR__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <math.h>

//#include "Skeleton.h"

class Skeleton;


class DataCollector
{
  public:
    DataCollector(Skeleton *skeleton) : skeleton(skeleton){}
    ~DataCollector(){}

    virtual void collectData() = 0;
  protected:
    Skeleton *skeleton;
    float getDistance(XnVector3D vec1, XnVector3D vec2);
  private:
};


#endif // End header lock
