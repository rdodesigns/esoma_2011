/**
 * @file
 * @author Ryan Orendorff <ryan.com>
 * @version 14 [master] (Fri Jan 21 18:21:30 EST 2011)
 * @parent 96b936cedc48a0de9663a6cbe02b49fa6b1b54ac
 *
 * Skeleton functions
 *
 *
 */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "Skeleton.h"


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

extern xn::UserGenerator user;

XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part)
{
  XnSkeletonJointPosition pos;

  user.GetSkeletonCap().GetSkeletonJointPosition(player, body_part,
                                                 pos);

  return pos.position;

}

XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part)
{

  XnSkeletonJointOrientation ori;

  user.GetSkeletonCap().GetSkeletonJointOrientation(player, body_part,
                                                 ori);

  return ori.orientation;

}
