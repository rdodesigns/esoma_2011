/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 85 [algorithms] (Fri Mar 25 23:27:00 EDT 2011)
 * @parent 4f1367c34178bc802352e74b0e76a15e405ec896
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


