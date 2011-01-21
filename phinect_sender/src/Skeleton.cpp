/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 5 [master] (Fri Jan 21 02:35:11 EST 2011)
 *
 * Skeleton functions
 *
 */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "Skeleton.h"
#include <math.h>


//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define PI 3.14159265

extern xn::UserGenerator user;

float GetDistanceBetweenVectors(XnVector3D vec1, XnVector3D vec2)
{

  return sqrt(  pow(vec1.X - vec2.X, 2)
              + pow(vec1.Y - vec2.Y, 2)
              + pow(vec1.Z - vec2.Z, 2));
}

float GetRotationAngleInDegrees(XnVector3D input, XnVector3D rotate)
{
  return acos(input.X*rotate.X + input.Y*rotate.Y + input.Z*rotate.Z)
         * 180.0 / PI;
}

float GetRotationAngleInRadians(XnVector3D input, XnVector3D rotate)
{
  return acos(input.X*rotate.X + input.Y*rotate.Y + input.Z*rotate.Z);
}


XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part)
{
  XnSkeletonJointPosition pos;

  user.GetSkeletonCap().GetSkeletonJointPosition(player, body_part,
                                                 pos);

  //printf("[%d] (%.0f, %.0f, %.0f) \n",
      //player,
      //pos.position.X, pos.position.Y, pos.position.Z);

  return pos.position;

}

XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part)
{

  XnSkeletonJointOrientation ori;

  user.GetSkeletonCap().GetSkeletonJointOrientation(player, body_part,
                                                 ori);

  //printf("[%d] (%f, %f, %f)\n",
      //player,
      //GetRotationAngleInDegrees((XnVector3D){1,0,0}, (XnVector3D)
                                             //{
                                              //ori.orientation.elements[0],
                                              //ori.orientation.elements[1],
                                              //ori.orientation.elements[2]}),
      //GetRotationAngleInDegrees((XnVector3D){0,1,0}, (XnVector3D)
                                             //{
                                              //ori.orientation.elements[3],
                                              //ori.orientation.elements[4],
                                              //ori.orientation.elements[5]}),
      //GetRotationAngleInDegrees((XnVector3D){0,0,1}, (XnVector3D)
                                             //{
                                              //ori.orientation.elements[6],
                                              //ori.orientation.elements[7],
                                              //ori.orientation.elements[8]})
                                                                          //);

  //printf("[%d] (%+f, %+f, %+f, %+f, %+f, %+f, %+f, %+f, %+f) [%f] \n",
      //player,
      //ori.orientation.elements[0],
      //ori.orientation.elements[1],
      //ori.orientation.elements[2],
      //ori.orientation.elements[3],
      //ori.orientation.elements[4],
      //ori.orientation.elements[5],
      //ori.orientation.elements[6],
      //ori.orientation.elements[7],
      //ori.orientation.elements[8],
      //ori.fConfidence);

  return ori.orientation;
}

float GetPercentDistension(XnUserID player, XnSkeletonJoint limb)
{
  XnVector3D origin = GetBodyPartPosition(player, (XnSkeletonJoint) limb);
  XnVector3D second = GetBodyPartPosition(player, (XnSkeletonJoint) (limb+1));
  XnVector3D third  = GetBodyPartPosition(player, (XnSkeletonJoint) (limb+3));

  float hyp_dist  = GetDistanceBetweenVectors(origin, third);
  float side_dist = GetDistanceBetweenVectors(origin, second)
                  + GetDistanceBetweenVectors(second, third);

  return hyp_dist/side_dist;

}
