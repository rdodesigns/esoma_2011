/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 71 [datacollector] (Mon Mar 21 02:00:57 EDT 2011)
 * @parent f78bd7d036fabcf3e64bf15c5d9b1cc202fb081c
 *
 * @section DESCRIPTION
 *
 * The functions for acquiring useful data out of the Kinect using the OpenNI
 * framework. These mostly act as bridges to preexisting methods that provide
 * additional information in less convenient structs.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 */


#ifndef __ESOMAS__SKELETON__
#define __ESOMAS__SKELETON__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include "ExtensionCollector.h"

// Define the numbers for the body joints.
#define LARM 3
#define RARM 6
#define LLEG 9
#define RLEG 12

class ExtensionCollector;

class Skeleton
{
  public:
    Skeleton(xn::UserGenerator user);
    ~Skeleton();
    XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part);
    XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part);

    void updateSkeleton();
    XnVector3D getJoint(int joint_num);

    XnVector3D joints[15];
  protected:

  private:
    xn::UserGenerator user;
    ExtensionCollector *ext_col;

};


#endif // End header lock
