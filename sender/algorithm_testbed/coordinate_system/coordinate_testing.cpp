/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 83 [algorithms] (Fri Mar 25 04:38:29 EDT 2011)
 * @parent 3f60445abc32c3abf427594723d8076e7f2bac50
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
#define SIZE 3

#define PRINTOUT \
  for (int i = 0; i < SIZE; i++){\
    results = data[i];\
    cout << results.X << ", " << results.Y << ", " << results.Z << endl;\
  }\
  cout << endl;


using namespace std;

int main()
{
  CoordinateData3D data;
  XnVector3D results;

  // Load in data points
  data.addXnVector3D((XnVector3D) {0,1,2});
  data.addXnVector3D((XnVector3D) {3,4,5});
  data.addXnVector3D((XnVector3D) {6,7,8});
  PRINTOUT


  data.translate((XnVector3D) {1,1,1});
  PRINTOUT

  data.translate((XnVector3D) {3,0,7});
  PRINTOUT

  //data.resetTranslation();
  //PRINTOUT


  data.rotate((XnMatrix3X3) {ZR, ZR, 0, -ZR, ZR, 0, 0, 0, 1});
  PRINTOUT

  data.rotate((XnMatrix3X3) {ZR, ZR, 0, -ZR, ZR, 0, 0, 0, 1});
  PRINTOUT


  data.resetRotation();
  data.resetTranslation();
  PRINTOUT

  return 0;
}
