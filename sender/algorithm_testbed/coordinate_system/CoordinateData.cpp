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


#include "CoordinateData.h"

CoordinateData::CoordinateSystem::CoordinateSystem(int type, CoordinateData *coor_data) : type(type), coor_data(coor_data)
{
  cout << coor_data->dimens << endl;
  origin = new double[3];
  rotation = new double[3*3];
}

CoordinateData::CoordinateSystem::~CoordinateSystem()
{
}

