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
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details. http://www.gnu.org/licenses/gpl.html
 */

//---------------------------------------------------------------------------
// Constants and Globals
//---------------------------------------------------------------------------
CircleGesture circle_gesture;

//---------------------------------------------------------------------------
// Setup
//---------------------------------------------------------------------------

void setup()
{
  size(400,400);
  frameRate(30); // 30 Hz
  smooth();      // Anti-aliasing

  ellipseMode(CENTER); // |------o------| instead of o-------------|
  rectMode(CENTER);    // |------o------| instead of o-------------|

  circle_gesture = new CircleGesture();
}


//---------------------------------------------------------------------------
// Drawing functions
//---------------------------------------------------------------------------


void draw()
{
  circle_gesture.calc();
  circle_gesture.draw();
}
