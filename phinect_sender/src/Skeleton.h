/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 5 [master] (Fri Jan 21 02:35:11 EST 2011)
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
