/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 32 [master] (Fri Feb  4 23:07:29 EST 2011)
 * @parent 7e2b7f0eec705d6755a8679bda9052873660306e
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
