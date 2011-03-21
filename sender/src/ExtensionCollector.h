/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 71 [datacollector] (Mon Mar 21 02:00:56 EDT 2011)
 * @parent f78bd7d036fabcf3e64bf15c5d9b1cc202fb081c
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

class ExtensionCollector : protected DataCollector
{
  public:
    ExtensionCollector(Skeleton *skeleton, int limb_num);
    ~ExtensionCollector();

    float getExtension();
    void collectData();
  private:
    struct limb_s limb;
    //vector<int> limbs_over_time; // Can an initial size be set?
};


#endif // End header lock
