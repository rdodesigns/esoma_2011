/**
 * @file
 * @author Ryan Orendorff <ryan.com>
 * @version 12 [master] (Fri Jan 21 14:40:40 EST 2011)
 * @message Another githook test?
 * @parent a164e8961fc8a6fe0d6f4384a47ebc30dcad3991
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
