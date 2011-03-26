/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 86 [algorithms] (Fri Mar 25 23:46:08 EDT 2011)
 * @parent 52ae570d2b80b4c37fb904713a87f19ae6b388f1
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
  if (index >= data.size()) return;

  data.erase(data.begin()+index);
}

void CoordinateData3D::remove(int from, int to)
{
  // TODO: Figure out why data.erase(from, to) does not work
  for(int i = from; i <= to; i++)
      remove(from);
}

void CoordinateData3D::clear()
{
  data.clear();
}

