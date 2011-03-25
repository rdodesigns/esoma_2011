/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 84 [algorithms] (Fri Mar 25 04:46:37 EDT 2011)
 * @parent 0971f2c76d58c46dc05bd0d6d276a0d6fbdb194b
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

/*
 * From Cartesian to Spherical
 * r = x^2+y^2+z^2
 * theta = acos(z/r)
 * phi = atan2(y/x)
 *
 * From Spherical to Cartesian
 * x = rsin(theta)cos(phi)
 * y = rsin(theta)sin(phi)
 * z = rcos(theta)
 *
 * From Cylindrical (r, phi, z) to Spherical (rho, theta, phi)
 * rho = sqrt(r^r + z^2)
 * theta = atan2(rho/z) = acos(z/r)
 * phi = phi
 *
 * From Spherical to Cynlindrical
 * r = rho*sin(theta)
 * z = rho*cos(theta)
 * phi = phi
 *
 * From Cylindrical to Cartesian
 * x = rho*cos(phi)
 * y = rho*sin(phi)
 * z = z
 *
 * From Cartesian to Cylindrical
 * rho = sqrt(x^2 + y^2)
 *       0                    if x==0 && y==0
 * phi = arcsin(y/rho)        if x >= 0
 *       -arcsin(y/rho) + pi  if x < 0
 * z = z
 */

#ifndef __ESOMA__COORDINATESYSTEM__
#define __ESOMA__COORDINATESYSTEM__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include <vector>
using std::vector;

class CoordinateSystem3D
{
  public:
    CoordinateSystem3D(vector<XnVector3D>& data);
    ~CoordinateSystem3D();


    // Moving the coordinate system
    void translate(XnVector3D trans);
    void rotate(XnMatrix3X3 rot);

    // Resetting to original data
    void resetTranslation();
    void resetRotation();

    void convertToCoordinateSystem(int type);

  private:
    int type;
    XnVector3D origin;
    XnMatrix3X3 rotation;
    std::vector<XnVector3D>& data;

    // Easy case statements
    static const int CARTESIAN   = 0;
    static const int SPHERICAL   = 1;
    static const int CYLINDRICAL = 2;

    //
    // Convert to specific
    void convertCartesianToSpherical();
    void convertCartesianToCylindrical();
    void convertSphericalToCartesian();
    void convertCylindricalToCartesian();
    void convertSphericalToCylindrical();
    void convertCylindricalToSpherical();

};

#endif // end header lock
