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
