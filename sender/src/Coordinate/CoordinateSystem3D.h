/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 103 [complete_skel] (Sun Mar 27 22:37:05 EDT 2011)
 * @parent ac3becbea7546d5e90a262c32d944defccfbf21a
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

#define RADIUS X
#define PHI    Y
#define THETA  Z

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
