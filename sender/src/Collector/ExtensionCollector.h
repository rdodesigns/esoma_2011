/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 104 [build_system] (Mon Mar 28 03:32:22 EDT 2011)
 * @parent c0f3df27ccf168ef3344cf194d287b22ce2ab018
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
    void update();
  private:
    struct limb_s limb;
};


#endif // End header lock
