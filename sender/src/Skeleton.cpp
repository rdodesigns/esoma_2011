/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * The functions for acquiring useful data out of the Kinect using the OpenNI
 * framework. These mostly act as bridges to preexisting methods that provide
 * additional information in less convenient structs.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 *
 * Contact Information
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
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
