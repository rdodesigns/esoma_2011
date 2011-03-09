/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 70 [datacollector] (Wed Mar  9 02:46:35 PST 2011)
 * @parent 3e9ce6ed429180aed9ae40095c4e3b6f94f5caec
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

// Define the numbers for the body joints.
#define LARM 3
#define RARM 6
#define LLEG 9
#define RLEG 12

class Skeleton
{
  public:
    Skeleton( xn::UserGenerator user);
    ~Skeleton();
    XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part);
    XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part);

    void updateSkeleton();
    XnVector3D getJoint(int joint_num);

  protected:
    XnVector3D joints[15];

  private:
    xn::UserGenerator user;
    ExtensionCollector *ext_col;

};


#endif // End header lock
