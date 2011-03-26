/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 86 [algorithms] (Fri Mar 25 23:46:08 EDT 2011)
 * @parent 52ae570d2b80b4c37fb904713a87f19ae6b388f1
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
  for (int i = 0; i < data.size(); i++){\
    results = data[i];\
    cout << results.X << ", " << results.Y << ", " << results.Z << endl;\
  }\
  cout << endl


using namespace std;

int main()
{
  CoordinateData3D data;
  XnVector3D results;

  // Load in data points tests
  cout << "Adding three data points\n";
  data.addXnVector3D((XnVector3D) {0,1,2});
  data.addXnVector3D((XnVector3D) {3,4,5});
  data.addXnVector3D((XnVector3D) {6,7,8});
  PRINTOUT;

  cout << "Removing first element\n";
  data.removeFromBegin();
  PRINTOUT;

  cout << "Remove last element\n";
  data.removeFromEnd();
  PRINTOUT;

  cout << "Adding two data points\n";
  data.addXnVector3D((XnVector3D) {9,10,11});
  data.addXnVector3D((XnVector3D) {12,13,14});
  PRINTOUT;

  cout << "Removing second data point\n";
  data.remove(1);
  PRINTOUT;

  cout << "Adding two data points\n";
  data.addXnVector3D((XnVector3D) {15,16,17});
  data.addXnVector3D((XnVector3D) {18,19,20});
  PRINTOUT;

  cout << "Removing second and third data point\n";
  data.remove(1,2);
  PRINTOUT;

  cout << "Removing from outside data.size()\n";
  data.remove(12);
  PRINTOUT;

  cout << "Clearing the results\n";
  data.clear();
  PRINTOUT;

  cout << "Adding three data points\n";
  data.addXnVector3D((XnVector3D) {0,1,2});
  data.addXnVector3D((XnVector3D) {3,4,5});
  data.addXnVector3D((XnVector3D) {6,7,8});
  PRINTOUT;


  // Translation and Rotation Tests
  cout << "Translating by (1,1,1)\n";
  data.translate((XnVector3D) {1,1,1});
  PRINTOUT;

  cout << "Translating by (3,0,7)\n";
  data.translate((XnVector3D) {3,0,7});
  PRINTOUT;

  cout << "Rotate around Z-axis 45 degrees\n";
  data.rotate((XnMatrix3X3) {ZR, ZR, 0,
                            -ZR, ZR, 0,
                              0,  0, 1});
  PRINTOUT;

  cout << "Rotate around Y-axis 60 degrees again\n";
  data.rotate((XnMatrix3X3) {ZR, ZR, 0,
                            -ZR, ZR, 0,
                              0,  0, 1});
  PRINTOUT;


  // Converting to Coordinate System Tests
  cout << "Convert Cartesian to Spherical\n";
  data.convertToSpherical();
  PRINTOUT;

  cout << "Convert Spherical to Cylindrical\n";
  data.convertToCylindrical();
  PRINTOUT;

  cout << "Convert Cylindrical to Cartesian\n";
  data.convertToCartesian();
  PRINTOUT;

  cout << "Convert Cartesian to Cylindrical\n";
  data.convertToCylindrical();
  PRINTOUT;

  cout << "Convert Cylindrical to Spherical\n";
  data.convertToSpherical();
  PRINTOUT;

  cout << "Convert Spherical to Cartesian\n";
  data.convertToCartesian();
  PRINTOUT;


  // Reset to original data
  cout << "Resetting rotation and translations\n";
  data.resetRotation();
  data.resetTranslation();
  PRINTOUT;

  return 0;
}
