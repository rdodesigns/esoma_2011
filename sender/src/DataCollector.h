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


#ifndef __ESOMAS__DATACOLLECTOR__
#define __ESOMAS__DATACOLLECTOR__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <math.h>

#include "Skeleton.h"

class DataCollector
{
  public:
    DataCollector(Skeleton *skel);
    ~DataCollector(){}

    virtual void update() = 0;
  protected:
    Skeleton *skeleton;
    float getDistance(XnVector3D vec1, XnVector3D vec2);
  private:
};


#endif // End header lock
