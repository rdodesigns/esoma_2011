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

//-----------------------------------------------------------------------------
// NOTE: ALL ROTATIONS ARE SUSCEPTIBLE TO GIMBEL LOCK!
//-----------------------------------------------------------------------------

// Also note that rotations and translations do commute (and hence to reset
// to the original data the resetTranslation and resetRotation can be done in
// any order).

#ifndef __ESOMA__COORDINATEDATA__
#define __ESOMA__COORDINATEDATA__


// Coordinate systems. Currently only have two and three dimensions planned.

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

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include <vector>
using std::vector;


class CoordinateData3D
{

  public:
    CoordinateData3D() : coor_sys(data) {}
    ~CoordinateData3D(){}

    struct XnVector3D operator[](int index) {
      return data[index];
    }
    void addXnVector3D(XnVector3D vector);
    void removeFromBegin(){remove(0);}
    void removeFromEnd(){data.pop_back();}
    void remove(int index);
    void remove(int from, int to);
    void clear();

    // OpenNI related calls
    // NOTE: These only work in Cartesian coordinates (they make less sense in
    // other coordinate systems).
    void translate(XnVector3D trans){coor_sys.translate(trans);}
    void rotate(XnMatrix3X3 rot){coor_sys.rotate(rot);}

    // Get back to original data.
    void resetTranslation(){coor_sys.resetTranslation();}
    void resetRotation(){coor_sys.resetRotation();}
    void reset(){coor_sys.resetTranslation();
                 coor_sys.resetRotation();}

    // Convert to various coordinate systems
    void convertToCartesian(){coor_sys.convertToCoordinateSystem(0);}
    void convertToSpherical(){coor_sys.convertToCoordinateSystem(1);}
    void convertToCylindrical(){coor_sys.convertToCoordinateSystem(2);}

    class CoordinateSystem
    {
      public:
        CoordinateSystem(vector<XnVector3D>& data);
        ~CoordinateSystem();


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

  private:
    vector<XnVector3D> data;
    CoordinateSystem coor_sys;

};

#endif // End header lock.
