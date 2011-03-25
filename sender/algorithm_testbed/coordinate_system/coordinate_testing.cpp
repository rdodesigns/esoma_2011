/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 81 [algorithms] (Fri Mar 25 00:47:25 EDT 2011)
 * @parent f54be4bc5895feecc1b55d179657a84d5e762343
 *
 * @section DESCRIPTION
 *
 * Test of coordinate system translations.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 * Resources and brainstorming assistance provided through a collaboration with
 * the MIT Media Lab and Tufts University. Contact information is provided
 * below.
 *
 * Ryan Orendorff
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 *
 * Dr. John Moore
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 * Professor Fiorenzo Omenetto
 * Tufts University
 * Department of Biomedical Engineering
 * 4 Colby Street
 * Medford, MA 02155 USA
 */

#include "CoordinateData3D.h"
#include <iostream>

#define ZR .707106781187
using namespace std;

int main()
{
  CoordinateData3D data(CARTESIAN);

  data.addXnVector3D((XnVector3D) {1,1,1});
  data.translate((XnVector3D) {1,1,1});
  data.resetTranslation();
  data.rotate((XnMatrix3X3) {ZR, ZR, 0, -ZR, ZR, 0, 0, 0, 1});

  XnVector3D results = data[0];
  cout << "Data is " << results.X << ", " << results.Y << ", " << results.Z << endl;
  return 0;
}
