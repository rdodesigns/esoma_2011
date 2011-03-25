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

CoordinateData3D::CoordinateSystem::CoordinateSystem(int type, vector<XnVector3D> &data) : type(type), data(data)
{
  origin   = (XnVector3D) {0,0,0};
  rotation = (XnMatrix3X3) {0,0,0,0,0,0,0,0,0};
}

CoordinateData3D::CoordinateSystem::~CoordinateSystem()
{
}

void CoordinateData3D::CoordinateSystem::translate(XnVector3D trans)
{
  origin.X += trans.X; // This makes the vector always relative to the
  origin.Y += trans.Y; // abolsute coordinates.
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

}
