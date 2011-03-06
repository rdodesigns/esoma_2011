/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 63 [datacollector] (Sun Mar  6 10:30:11 PST 2011)
 * @parent 5292611a77495c3077f9bec5da87f969401ae8d6
 *
 * @section DESCRIPTION
 *
 * A template class for collecting extension data.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
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

    float GetExtension();
    float GetYayas();
    void printSomething();
  private:
    struct limb_s limb;
    //vector<int> limbs_over_time; // Can an initial size be set?
};


#endif // End header lock
