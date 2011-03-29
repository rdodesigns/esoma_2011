/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 106 [complete_skel] (Mon Mar 28 20:14:40 EDT 2011)
 * @parent 5af5a331fa4bb1e7b44b87ff7dbf570e3835be5a
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

// Also note that rotations and translations do commute (and hence to reset
// to the original data the resetTranslation and resetRotation can be done in
// any order).

#ifndef __ESOMA__COORDINATEDATA__
#define __ESOMA__COORDINATEDATA__



#include <XnOpenNI.h>
#include <XnCppWrapper.h>

#include <vector>
using std::vector;

#include "CoordinateSystem3D.h"

class CoordinateData3D
{

  public:
    CoordinateData3D() : coor_sys(data) {}
    ~CoordinateData3D(){}

    struct XnVector3D operator[](int index) {
      return data[index];
    }
    struct XnVector3D at(int index){data.at(index);}
    void addXnVector3D(XnVector3D vector);
    void removeFromBegin(){remove(0);}
    void removeFromEnd(){data.pop_back();}
    void remove(int index);
    void remove(int from, int to);
    void clear();
    int size() {return data.size();}

    // CoordinateSystem3D related calls
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


  private:
    vector<XnVector3D> data;
    CoordinateSystem3D coor_sys;

};

#endif // End header lock.
