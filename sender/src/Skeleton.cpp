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
 *
 */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "Skeleton.h"
#include "ExtensionCollector.h"
#include <iostream>


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------

Skeleton::Skeleton( xn::UserGenerator user) : user(user)
{
  ExtensionCollector *ext_col = new ExtensionCollector(this, LARM);
  ext_col->printSomething();
  delete ext_col;
}

Skeleton::~Skeleton(){}

XnVector3D Skeleton::GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part)
{
  XnSkeletonJointPosition pos;

  user.GetSkeletonCap().GetSkeletonJointPosition(player, body_part,
                                                 pos);
  //return pos.position;
}

XnMatrix3X3 Skeleton::GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part)
{
  XnSkeletonJointOrientation ori;

  user.GetSkeletonCap().GetSkeletonJointOrientation(player, body_part,
                                                 ori);
  return ori.orientation;

}

void Skeleton::updateSkeleton()
{
  int j = 0;
  for (int i = 1; i <= 24 ; i++) {
    if (   i == 4
        || i == 5
        || i == 8
        || i == 10
        || i == 11
        || i == 14
        || i == 16
        || i == 19
        || i == 23) continue; // These give odd results in z axis.
    XnVector3D pos = GetBodyPartPosition(1, (XnSkeletonJoint) i);

    joints[j++] = pos;
  }
}

XnVector3D Skeleton::getJoint(int joint_num)
{
  return joints[joint_num];
}
