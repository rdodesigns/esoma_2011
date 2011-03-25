/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 81 [algorithms] (Fri Mar 25 00:47:24 EDT 2011)
 * @parent f54be4bc5895feecc1b55d179657a84d5e762343
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


#ifndef __ESOMA__COORDINATEDATA__
#define __ESOMA__COORDINATEDATA__


// Coordinate systems. Currently only have two and three dimensions planned.
#define CARTESIAN   0
#define SPHERICAL   1
#define CYLINDRICAL 2

#include <vector>

using std::vector;

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

class CoordinateData3D
{

  public:
    CoordinateData3D() : coordinate_system(CARTESIAN, data) {}
    CoordinateData3D(int type) : coordinate_system(type, data) {}
    ~CoordinateData3D(){}

    void addXnVector3D(XnVector3D vector);
    void removeFromBegin(){remove(0);}
    void removeFromEnd(){data.pop_back();}
    void remove(int index);
    void remove(int from, int to);
    void clear();


    // OpenNI specific calls
    void translate(XnVector3D trans){coordinate_system.translate(trans);}
    void rotate(XnMatrix3X3 rot){coordinate_system.rotate(rot);}

    void resetTranslation(){coordinate_system.resetTranslation();}
    void resetRotation(){coordinate_system.resetRotation();}

    struct XnVector3D operator[](int index) {
      return data[index];
    }

    class CoordinateSystem
    {
      public:
        CoordinateSystem(int type, vector<XnVector3D>& data);
        ~CoordinateSystem();

        void translate(XnVector3D trans);
        void rotate(XnMatrix3X3 rot);

        void resetTranslation();
        void resetRotation();

      private:
        int type;
        XnVector3D origin;
        XnMatrix3X3 rotation;

        std::vector<XnVector3D>& data;
    };

  private:
    vector<XnVector3D> data;
    CoordinateSystem coordinate_system;

};

#endif // End header lock.
