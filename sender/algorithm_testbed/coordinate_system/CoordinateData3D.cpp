/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 83 [algorithms] (Fri Mar 25 04:38:29 EDT 2011)
 * @parent 3f60445abc32c3abf427594723d8076e7f2bac50
 *
 * @section DESCRIPTION
 *
 * Holding coordinate data and allowing it to be easily translated to other
 * coordinate systems.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 * Resources and brainstorming assistance provided through a collaboration with
 * the MIT Media Lab and Tufts University. Contact information is provided
 * below.
 *
 * Contact
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 *
 */


#include "CoordinateData3D.h"

//*****************************************************************************
// Coordinate Data
//*****************************************************************************

void CoordinateData3D::addXnVector3D(XnVector3D vector)
{
  data.push_back(vector);
}
void CoordinateData3D::remove(int index)
{
  if (index >= data.size()) return; // This needs to be improved.

  data.erase(data.begin()+index);
}

void CoordinateData3D::remove(int from, int to)
{
  if (to < from) return;
  if (to >= data.size()) return; // This needs to be improved.

  data.erase(data.begin()+from, data.begin()+to);
}

void CoordinateData3D::clear()
{
  data.clear();
}


//*****************************************************************************
// Coordinate System
//*****************************************************************************

CoordinateData3D::CoordinateSystem::CoordinateSystem(vector<XnVector3D> &data) : data(data)
{
  type     = CARTESIAN;
  origin   = (XnVector3D) {0,0,0};
  rotation = (XnMatrix3X3) {1,0,0,0,1,0,0,0,1}; // I
}

CoordinateData3D::CoordinateSystem::~CoordinateSystem()
{
}

void CoordinateData3D::CoordinateSystem::translate(XnVector3D trans)
{
  origin.X += trans.X; // This makes the vector always relative to the
  origin.Y += trans.Y; // absolute coordinates.
  origin.Z += trans.Z;

  vector<XnVector3D>::iterator it;
  for (it = data.begin(); it < data.end(); it++) {
    it->X -= trans.X;
    it->Y -= trans.Y;
    it->Z -= trans.Z;
  }

}

void CoordinateData3D::CoordinateSystem::resetTranslation()
{
  translate((XnVector3D) {-origin.X, -origin.Y, -origin.Z});
}

void CoordinateData3D::CoordinateSystem::rotate(XnMatrix3X3 rot)
{

  XnMatrix3X3 old = rotation;
  /*
   * Rotations do NOT commute, and hence it is necessary to perform the inverse
   * operations in the opposite order of the operations to get to a particular
   * rotation. This can be thought of rotation A, followed by B, followed by
   * C. The result is
   *
   *  A*B*C*C^T*B^T*A^T
   *  = A*B*I*B^T*A^T
   *  = A*I*I*A^T
   *  = I*I*I = I
   *
   */

  rotation.elements[0] = rot.elements[0]*old.elements[0]
                       + rot.elements[3]*old.elements[3]
                       + rot.elements[6]*old.elements[6];
  rotation.elements[1] = rot.elements[0]*old.elements[1]
                       + rot.elements[3]*old.elements[4]
                       + rot.elements[6]*old.elements[7];
  rotation.elements[2] = rot.elements[0]*old.elements[2]
                       + rot.elements[3]*old.elements[5]
                       + rot.elements[6]*old.elements[8];
  rotation.elements[3] = rot.elements[1]*old.elements[0]
                       + rot.elements[4]*old.elements[3]
                       + rot.elements[7]*old.elements[6];
  rotation.elements[4] = rot.elements[1]*old.elements[1]
                       + rot.elements[4]*old.elements[4]
                       + rot.elements[7]*old.elements[7];
  rotation.elements[5] = rot.elements[1]*old.elements[2]
                       + rot.elements[4]*old.elements[5]
                       + rot.elements[7]*old.elements[8];
  rotation.elements[6] = rot.elements[2]*old.elements[0]
                       + rot.elements[5]*old.elements[3]
                       + rot.elements[8]*old.elements[6];
  rotation.elements[7] = rot.elements[2]*old.elements[1]
                       + rot.elements[5]*old.elements[4]
                       + rot.elements[8]*old.elements[7];
  rotation.elements[8] = rot.elements[2]*old.elements[2]
                       + rot.elements[5]*old.elements[5]
                       + rot.elements[8]*old.elements[8];

  vector<XnVector3D>::iterator it;
  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D v = *it;
    it->X = v.X*rot.elements[0]+v.Y*rot.elements[1]+v.Z*rot.elements[2];
    it->Y = v.X*rot.elements[3]+v.Y*rot.elements[4]+v.Z*rot.elements[5];
    it->Z = v.X*rot.elements[6]+v.Y*rot.elements[7]+v.Z*rot.elements[8];
  }
}

void CoordinateData3D::CoordinateSystem::resetRotation()
{
  rotate(rotation);

  rotation = (XnMatrix3X3) {1,0,0,0,1,0,0,0,1};
}
