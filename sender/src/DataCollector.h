/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 70 [datacollector] (Wed Mar  9 02:46:34 PST 2011)
 * @parent 3e9ce6ed429180aed9ae40095c4e3b6f94f5caec
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
#include "Skeleton.h"

class DataCollector
{
  public:
    DataCollector(Skeleton *skeleton) : skeleton(skeleton){}
    ~DataCollector(){}
  protected:
    Skeleton *skeleton;
  private:
};


#endif // End header lock
