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


