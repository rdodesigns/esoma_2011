/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 72 [datacollector] (Mon Mar 21 02:49:10 EDT 2011)
 * @parent 8915da6c46e020833a3f13744b6e2daa8cceeaa9
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

  notify(); // Notify all observing data collectors.

}

XnVector3D Skeleton::getJoint(int joint_num)
{
  return joints[joint_num];
}

void Skeleton::addCollector(DataCollector *collector)
{
  collectors.push_back(collector);
}

void Skeleton::notify()
{
  for (int i = 0; i < collectors.size(); i++)
    collectors[i]->update();
}
