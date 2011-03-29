/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 106 [complete_skel] (Mon Mar 28 20:14:40 EDT 2011)
 * @parent 5af5a331fa4bb1e7b44b87ff7dbf570e3835be5a
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

#include <Skeleton.h>
#include <Coordinate/CoordinateData3D.h>

class Skeleton;

class DataCollector
{
  public:
    DataCollector(Skeleton *skel);
    ~DataCollector(){}

    virtual void update(CoordinateData3D& in_joints) = 0;
  protected:
    float getDistance(XnVector3D vec1, XnVector3D vec2);
    CoordinateData3D data;
  private:
    Skeleton *skeleton;
};


#endif // End header lock
