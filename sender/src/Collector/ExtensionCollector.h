/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 106 [complete_skel] (Mon Mar 28 20:14:40 EDT 2011)
 * @parent 5af5a331fa4bb1e7b44b87ff7dbf570e3835be5a
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
    void update(CoordinateData3D& in_joints);
  private:
    struct limb_s limb;
    static const int BASE     = 0;
    static const int PROXIMAL = 1;
    static const int DISTAL   = 2;
};


#endif // End header lock
