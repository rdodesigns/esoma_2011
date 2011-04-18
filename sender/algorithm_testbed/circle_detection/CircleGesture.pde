/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 114 [master] (Mon Apr 18 02:24:21 EDT 2011)
 * @parent 546c7549931ab4843a75414f45e2ace818824442
 *
 * @section DESCRIPTION
 *
 * Test to see if the user draws a circle with the cursor (on purpose).
 *
 * Copyright (C) 2011 Ryan Orendorff
 *
 * Licensed under GPLv3
 */

class CircleGesture{
//---------------------------------------------------------------------------
// Constants and Globals
//---------------------------------------------------------------------------


// Note on colors (A = alpha)                        AARRGGBB
private static final int cursor_color            = 0xFFFFFFFF; // White
private static final int circle_drawn_color      = 0xFF00FF00; // Green
private static final int circle_not_drawn_color  = 0xFFFF0000; // Red

// Mouse tracking characteristics
private static final int number_mouse_spline_pts = 50;   // time (#/30 Hz)
private static final float fraction_circle       = 12/8; // 360*%

// Mouse tracking position
private ArrayList mouse_spline; // A deque would be more efficient.
private PVector   averageMouse; // Average mouse position.
private PVector   sumMouse;     // Sum of all mouse spline positions.

// Direction constants
private static final int CLOCKWISE        = 1;
private static final int COUNTERCLOCKWISE = -1;

// Booleans used to change draw sequence.
private boolean circle_drawn;
private boolean was_calc_done;


//---------------------------------------------------------------------------
// Setup
//---------------------------------------------------------------------------


CircleGesture() // We take no inputs to the object because it makes no sense.
{
  // Instantiate mouse_spline object and add default values.
  mouse_spline = new ArrayList(number_mouse_spline_pts);
  for(int i = 0; i < number_mouse_spline_pts; i++)
    mouse_spline.add(new PVector(0,0));

  averageMouse = new PVector(0,0);
  sumMouse     = new PVector(0,0);

  was_calc_done = false;
}


//---------------------------------------------------------------------------
// Drawing functions
//---------------------------------------------------------------------------


/**
 * Draw onto the canvas.
 *
 * Ideally should contain only draw commands, calculations done elsewhere.
 */
void draw()
{
  if (!was_calc_done){
    println("CircleGesture: Calculation function must be run before draw"
            + " function.");
    return;
  }

  pushStyle(); // push style information (fill, stroke, etc) onto style stack.
  background(0); // clear screen with black background.

  // Set the fill of an object and the color of its outline.
  fill(cursor_color);
  drawMousePoints();

  if (circle_drawn)
    fill(circle_drawn_color);
  else
    fill(circle_not_drawn_color);
  noStroke();

  rect(averageMouse.x, averageMouse.y, 6,6);
  popStyle(); // Pop off stored style from style stack.

  was_calc_done = false;
}


/**
 * Draw the last n mouse points
 */
private void drawMousePoints()
{
  // Go through points, draw circles and connect them with lines.
  for(int i = 0; i < mouse_spline.size()-1; i++){
    pushStyle();
    // Unfortunately the Processing environment does not support generics yet.
    PVector vec  = (PVector) mouse_spline.get(i);
    PVector nvec = (PVector) mouse_spline.get(i+1);

    ellipse(vec.x, vec.y, 4,4);

    stroke(128); // gray
    line(vec.x, vec.y, nvec.x, nvec.y);
    popStyle();
  }

  // Take care of the latest added value.
  ellipse(mouseX, mouseY, 4,4);
  stroke(128);
  line(pmouseX, pmouseY, mouseX, mouseY);
}


//---------------------------------------------------------------------------
// Calculation functions
//---------------------------------------------------------------------------

/**
 * Performs all the calculations for gesture control.
 *
 * Should be run before {$link #draw()}
 */
public void calc()
{
  addNewMousePoint();
  drawMousePoints();
  circle_drawn = wasCircleDrawn();

  was_calc_done = true;
}

/**
 * Adds a new mouse point to mouse spline and removes oldest point.
 *
 * Separate function so we never forget to remove the last point and add new.
 */
private void addNewMousePoint()
{
  // If we have not moved, don't add the point again.
  if (!(mouseX == pmouseX && mouseY == pmouseY)){
    calculateAveragePoint();
    mouse_spline.remove(0);                        // Remove beginning point
    mouse_spline.add(new PVector(mouseX, mouseY)); // add point to end
  }
}


/**
 * Calculates the average point from the mouse spline data.
 */
private void calculateAveragePoint()
{
  PVector end = (PVector) mouse_spline.get(0);

  // Uses a running sum
  sumMouse.x = sumMouse.x - end.x + mouseX;
  sumMouse.y = sumMouse.y - end.y + mouseY;

  averageMouse.x = sumMouse.x / number_mouse_spline_pts;
  averageMouse.y = sumMouse.y / number_mouse_spline_pts;
}


/**
 * Has a circle been drawn over the last n points?
 */
private boolean wasCircleDrawn()
{
  /* Might want to think about a few things
   * - The origin of the circle is not constant.
   * - The loop may not be closed.
   * - The loop will most definitely not be a perfect circle shape.
   * - One can accidentally produced closed loops when moving (usually in very
   *   thin slices).
   *
   * It is possible to use the spline data to find an average x, y value and
   * then use this to define the center of a potential circle. Then one only
   * has to look for if the theta value that is increasing in the same
   * direction. This runs through the array once each frame, hence runs in
   * O(n).
   *
   * There might be a O(1) solution but I am not sure how long it would take to
   * find and how difficult it would be.
   */

  float angle;
  float sum_angle = 0;
  int direction = (angleDirection(translateToAvg((PVector) mouse_spline.get(0)),
                                  translateToAvg((PVector) mouse_spline.get(1)))
                   == CLOCKWISE) ? CLOCKWISE : COUNTERCLOCKWISE;

  // Forget newest point. Too lazy.
  for(int i = 1; i < mouse_spline.size() - 1; i++){
    PVector vec1 = (PVector) mouse_spline.get(i);
    PVector vec2 = (PVector) mouse_spline.get(i+1);

    angle = deltaAngle(vec1,vec2);
    if ( sign(angle) != direction)
      return false; // We started going in the opposite direction.

    sum_angle += angle;
    // We check for loops that are done more than once (so intentionally).
    if (Math.abs(sum_angle) > (2.0*Math.PI)*fraction_circle) return true;
  }

  // If we have been going in the same direction but not far enough.
  return false;
}


/**
 * Calculate the angle between two vectors.
 *
 * See {@link #angleDirection(PVector, PVector)} for direction calculation.
 */
private float deltaAngle(PVector vec1, PVector vec2)
{
  /*   x+ ->
   * ^ +---------------+
   * | |       o       | In this function the positions of the vectors are
   * y |      / \      | taken relative to the average point. This allows for
   * + |     /   \     | one to use vector math to find the angle between the
   *   | vec1     \    | vectors, along with a sign of the angle (+ for
   *   |       |  vec2 | clockwise). This alleviates the problem of the
   *   |       |       | discontinuities in the atan2 function.
   *   |      angle    |
   *   +---------------+
   */
  PVector vec1_from_avg = translateToAvg(vec1);
  PVector vec2_from_avg = translateToAvg(vec2);

  int direction = angleDirection(vec1_from_avg, vec2_from_avg);

  return PVector.angleBetween(vec1_from_avg, vec2_from_avg) * direction;
}


/**
 * Determine the sign of a float.
 *
 * @return 1 if positive, -1 if negative, 0 if erroneous or f=0.
 */
private int sign(float f)
{
  if (f > 0)
    return 1;
  else if (f < 0)
    return -1;
  else
    return 0; // This only occurs while values = NaN or f=0
}


/**
 * Determine the direction of the angle between two vectors.
 *
 * This is the cross product. Since both vectors have 0 z components the only
 * part of the determinate that survives is k, which provides the handedness of
 * the vector pair.
 *
 * @return 1 if clockwise, -1 if counterclockwise, 0 if erroneous or angle=0.
 */
private int angleDirection(PVector vec1, PVector vec2)
{
  return sign((vec1.x*vec2.y) - (vec1.y*vec2.x));
}


/**
 * Translate a vector to the average point.
 */
private PVector translateToAvg(PVector v)
{
  return PVector.sub(v, averageMouse);
}


} // END CLASS
