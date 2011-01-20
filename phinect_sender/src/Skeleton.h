/******************************************************************************
 *                                                                            *
 * Phinect: Obtain userGenerator physiological raw data from Kinect.          *
 *   Skeleton: Setup User Tracker Skeleton functions                          *
 *                                                                            *
 * Under the GPLv3.                                                           *
 *                                                                            *
 * Uses OpenNI and NITE framework.                                            *
 *                                                                            *
 * MIT Media Lab: Personal Robots and New Media Medicine                      *
 *                                                                            *
 *****************************************************************************/

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
