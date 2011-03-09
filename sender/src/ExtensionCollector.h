/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 70 [datacollector] (Wed Mar  9 02:46:34 PST 2011)
 * @parent 3e9ce6ed429180aed9ae40095c4e3b6f94f5caec
 *
 * @section DESCRIPTION
 *
 * A template class for collecting extension data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */


#ifndef __ESOMAS__EXTENSIONCOLLECTOR__
#define __ESOMAS__EXTENSIONCOLLECTOR__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
//#include <vector.h>
#include <iostream>

#include "Skeleton.h"
#include "DataCollector.h"


struct limb_s {
  int num;
  std::string name;
};

class ExtensionCollector : DataCollector
{
  public:
    ExtensionCollector(Skeleton *skeleton, int limb_num);
    ~ExtensionCollector();

    float getExtension();
  private:
    struct limb_s limb;
    //vector<int> limbs_over_time; // Can an initial size be set?
};


#endif // End header lock
