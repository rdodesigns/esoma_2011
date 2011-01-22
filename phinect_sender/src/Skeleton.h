/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 21 [master] (Sat Jan 22 02:49:12 EST 2011)
 * @parent d2daf7d110ac3e419c415876621e52a01c4a76b0
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
 */


#ifndef __PHINECT__SKELETON__
#define __PHINECT__SKELETON__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

XnMatrix3X3 GetBodyPartOrientation(XnUserID player, XnSkeletonJoint body_part);
XnVector3D GetBodyPartPosition(XnUserID player, XnSkeletonJoint body_part);

#endif // End header lock
