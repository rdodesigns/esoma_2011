/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 80 [algorithms] (Thu Mar 24 19:54:00 EDT 2011)
 * @parent b02879b356753f6df526f65c1c1cb1790dc09722
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


// 0 = Cartesian
// 1 = Spherical/Polar
// 2 = Cylindrical


#ifndef __ESOMA__COORDINATEDATA__
#define __ESOMA__COORDINATEDATA__


#define CARTESIAN   0 // 3D
#define SPHERICAL   1 // 3D
#define POLAR       1 // 2D
#define CYLINDRICAL 2 // 3D

#include <vector>
#include <iostream>

using namespace std;

class CoordinateData;

class CoordinateData
{

  public:
    CoordinateData(int dimens) : dimens(dimens), coordinate_system(CARTESIAN, this) {}
    CoordinateData(int dimens, int type) : dimens(dimens), coordinate_system(type, this) {}
    ~CoordinateData(){}

    friend class CoordinateSystem;

    class CoordinateSystem
    {
      public:
        CoordinateSystem(int type, CoordinateData *coor_data);
        ~CoordinateSystem();
      protected:
      private:
        int type;
        double* origin;
        double* rotation;
        CoordinateData *coor_data;
    };


  protected:

  private:
    std::vector<double *> data;
    const int dimens;
    CoordinateSystem coordinate_system;

};

#endif // End header lock.
