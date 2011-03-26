/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 87 [algorithms] (Fri Mar 25 23:49:25 EDT 2011)
 * @parent cdaa38519a5ff8511490acf367281c50ad8b49f3
 *
 * @section DESCRIPTION
 *
 * Holding coordinate data and allowing it to be easily translated to other
 * coordinate systems.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 *
 * Contact
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 */
#include "CoordinateSystem3D.h"

CoordinateSystem3D::CoordinateSystem3D(vector<XnVector3D> &data) : data(data)
{
  type     = CARTESIAN;
  origin   = (XnVector3D) {0,0,0};
  rotation = (XnMatrix3X3) {1,0,0,0,1,0,0,0,1}; // I
}

CoordinateSystem3D::~CoordinateSystem3D()
{
}

void CoordinateSystem3D::translate(XnVector3D trans)
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

void CoordinateSystem3D::resetTranslation()
{
  translate((XnVector3D) {-origin.X, -origin.Y, -origin.Z});
}

void CoordinateSystem3D::rotate(XnMatrix3X3 rot)
{

  XnMatrix3X3 old = rotation;
  /*
   * Rotations do NOT commute, and hence it is necessary to perform the inverse
   * operations in the opposite order of the operations to get to a particular
   * rotation. This can be thought of rotation A, followed by B, followed by
   * C. The result is
   *
   *  A*B*C*...*C^T*B^T*A^T
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

void CoordinateSystem3D::resetRotation()
{
  // The rotation is already the product of the transposed rotations.
  rotate(rotation);

  // Reset to identity matrix.
  rotation = (XnMatrix3X3) {1,0,0,0,1,0,0,0,1}; // I
}

//-----------------------------------------------------------------------------
// Converting functions
//-----------------------------------------------------------------------------

void CoordinateSystem3D::convertToCoordinateSystem(int to)
{
  switch (to)
  {
    case CARTESIAN:
      switch (type)
      {
        case CARTESIAN:
          return; // Same as initial type
          break;
        case SPHERICAL:
          convertSphericalToCartesian();
          break;
        case CYLINDRICAL:
          convertCylindricalToCartesian();
          break;
      }

      break;


    case SPHERICAL:
      switch (type)
      {
        case CARTESIAN:
          convertCartesianToSpherical();
          break;
        case SPHERICAL:
          return; // Same as initial type
          break;
        case CYLINDRICAL:
          convertCylindricalToSpherical();
          break;
      }

      break;


    case CYLINDRICAL:
      switch (type)
      {
        case CARTESIAN:
          convertCartesianToCylindrical();
          break;
        case SPHERICAL:
          convertSphericalToCylindrical();
          break;
        case CYLINDRICAL:
          return; // Same as initial type
          break;
      }
      break;


    default: // Gave an invalid type to function.
      throw 2;
      break;
  }
}


// NOTE:
// X = x, r
// Y = y, phi
// Z = z, theta

/* From Spherical to Cartesian   *
 * x = r*sin(theta)*cos(phi)     *
 * y = r*sin(theta)*sin(phi)     *
 * z = r*cos(theta)              */
void CoordinateSystem3D::convertSphericalToCartesian()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = old.X*sin(old.Z)*cos(old.Y);
    it->Y = old.X*sin(old.Z)*sin(old.Y);
    it->Z = old.X*cos(old.Z);
  }

  type = CARTESIAN;
}

/* From Cylindrical to Cartesian *
 * x = r * cos(phi)              *
 * y = r * sin(phi)              *
 * z = z                         */
void CoordinateSystem3D::convertCylindricalToCartesian()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = old.X*cos(old.Y);
    it->Y = old.X*sin(old.Y);
    //it->Z = old.Z;
  }

  type = CARTESIAN;
}

/* From Cartesian to Cylindrical                *
 *   r = sqrt(x^2 + y^2)                        *
 *      | 0                    if x==0 && y==0  *
 * phi =| arcsin(y/r)          if x >= 0        *
 *      | -arcsin(y/r) + pi    if x < 0         *
 *   z = z                                      */
void CoordinateSystem3D::convertCartesianToCylindrical()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = sqrt(pow(old.X,2) + pow(old.Y,2));

    if (old.X == 0 && old.Y == 0) {
      it->Y = 0;
    }
    else if (old.X >=0){
      it->Y = asin(old.Y/it->X);
    }
    else if (old.X < 0){
      it->Y = -asin(old.Y/it->X) + 3.14159265;
    }

    //it->Z = old.Z;
  }

  type = CYLINDRICAL;
}

/* From Spherical to Cynlindrical *
 * r = rho * sin(theta)           *
 * phi = phi                      *
 * z = rho * cos(theta)           */
void CoordinateSystem3D::convertSphericalToCylindrical()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = old.X*sin(old.Z);
    //it->Y = old.Y;
    it->Z = old.X*cos(old.Z);
  }

  type = CYLINDRICAL;
}

/* From Cylindrical (r, phi, z) to Spherical (rho, phi, theta)  *
 * rho   = sqrt(r^2 + z^2)                                      *
 * phi   = phi                                                  *
 * theta = atan2(r/z) = acos(z/rho)                             */
void CoordinateSystem3D::convertCylindricalToSpherical()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = sqrt(pow(old.X,2) + pow(old.Z,2));
    //it->Y = old.Y;
    it->Z = acos(old.Z/it->X);
  }

  type = SPHERICAL;
}

/* From Cartesian to Spherical *
 * r = sqrt(x^2+y^2+z^2)       *
 * phi = atan2(y/x)            *
 * theta = acos(z/r)           */
void CoordinateSystem3D::convertCartesianToSpherical()
{
  vector<XnVector3D>::iterator it;

  for (it = data.begin(); it < data.end(); it++) {
    XnVector3D old = *it;
    it->X = sqrt(pow(old.X,2) + pow(old.Y,2) + pow(old.Z,2) );
    double new_y = atan2(old.Y,old.X);
    it->Y = ( (new_y < 0) ) ? new_y + 2*3.14159265 : new_y;
    it->Z = acos(old.Z/it->X);
  }


  type = SPHERICAL;
}
