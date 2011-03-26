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

//-----------------------------------------------------------------------------
// NOTE: ALL ROTATIONS ARE SUSCEPTIBLE TO GIMBEL LOCK!
//-----------------------------------------------------------------------------


#ifndef __ESOMA__COORDINATESYSTEM__
#define __ESOMA__COORDINATESYSTEM__

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include <vector>
using std::vector;

#include <math.h>

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

    void convertToCoordinateSystem(int to);

  private:
    int type;
    XnVector3D origin;
    XnMatrix3X3 rotation;
    std::vector<XnVector3D>& data;

    // Easy case statements
    static const int CARTESIAN   = 0;
    static const int SPHERICAL   = 1;
    static const int CYLINDRICAL = 2;

    // Convert to specific
    void convertSphericalToCartesian();
    void convertCylindricalToCartesian();
    void convertCartesianToCylindrical();
    void convertSphericalToCylindrical();
    void convertCylindricalToSpherical();
    void convertCartesianToSpherical();

};

#endif // end header lock
