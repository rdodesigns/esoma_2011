/**
 * @file
 * @author Ryan Orendorff <ryan.com>
 * @version 14 [master] (Fri Jan 21 18:21:30 EST 2011)
 * @parent 96b936cedc48a0de9663a6cbe02b49fa6b1b54ac
 *
 * Skeleton functions
 *
 */


#ifndef __PHINECT__SKELETON__
#define __PHINECT__SKELETON__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#define XN_SKEL_LEFT_ARM  XN_SKEL_LEFT_SHOULDER
#define XN_SKEL_RIGHT_ARM XN_SKEL_RIGHT_SHOULDER
#define XN_SKEL_LEFT_LEG  XN_SKEL_LEFT_HIP
#define XN_SKEL_RIGHT_LEG XN_SKEL_RIGHT_HIP

XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part);
XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part);
float GetPercentDistension(XnUserID player, XnSkeletonJoint limb);


#endif // End header lock
