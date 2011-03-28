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


#ifndef __ESOMAS__DATACOLLECTOR__
#define __ESOMAS__DATACOLLECTOR__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <math.h>

#include <Skeleton.h>

class Skeleton;

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
