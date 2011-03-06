/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 63 [datacollector] (Sun Mar  6 10:30:11 PST 2011)
 * @parent 5292611a77495c3077f9bec5da87f969401ae8d6
 *
 * @section DESCRIPTION
 *
 * A template class for collecting data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
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
