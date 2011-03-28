/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 105 [complete_skel] (Mon Mar 28 18:30:26 EDT 2011)
 * @parent ce6d1e9e39faea4077d384d3e2bd369c537e1330
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

#include <Collector/DataCollector.h>

#include <iostream>

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
