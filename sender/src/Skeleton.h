/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 63 [datacollector] (Sun Mar  6 10:30:11 PST 2011)
 * @parent 5292611a77495c3077f9bec5da87f969401ae8d6
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
 * E14, 20 Ames Street
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
  private:
    xn::UserGenerator user;
    XnVector3D joints[15];

};


#endif // End header lock
