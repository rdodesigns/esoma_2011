/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 105 [complete_skel] (Mon Mar 28 18:30:26 EDT 2011)
 * @parent ce6d1e9e39faea4077d384d3e2bd369c537e1330
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


#ifndef __ESOMAS__SKELETON__
#define __ESOMAS__SKELETON__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <vector>

#include <Collector/DataCollector.h>
#include <Coordinate/CoordinateData3D.h>

// Define the numbers for the body joints.
#define LARM 3
#define RARM 6
#define LLEG 9
#define RLEG 12

class DataCollector;

class Skeleton
{
  public:
    Skeleton(xn::UserGenerator user);
    ~Skeleton();
    XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part);
    XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part);

    void updateSkeleton();
    XnVector3D getJoint(int joint_num);

    void addCollector(DataCollector *collector);
    void notify();
    CoordinateData3D joints;
  protected:

  private:
    xn::UserGenerator user;
    std::vector <DataCollector * > collectors;

};


#endif // End header lock
