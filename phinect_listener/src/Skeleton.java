/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 23 [master] (Mon Jan 24 03:22:12 EST 2011)
 * @parent b559be5a59f2cf47bd605326db26eccafd4b608f
 *
 * @section DESCRIPTION
 *
 * A class for describing the skeleton as a series of PVectors. Calculates
 * and keeps track of data derived from the skeletal points.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
 */

import processing.core.*;

import java.util.*;

import java.util.Observable;


public class Skeleton extends Observable {
  private final int larm_color = 0xffE41A1C; ///< Red
  private final int rarm_color = 0xff377EB8; ///< Blue
  private final int lleg_color = 0xff4DAF4A; ///< Green
  private final int rleg_color = 0xff984EA3; ///< Purple

  private PApplet parent;
  private PVector[] joints;

  private Socket socket;
  private int user;

  Skeleton(PApplet parent, Socket socket, int user)
  {
    this.parent = parent;
    this.user   = user;
    this.socket = socket;

    socket.subscribeToUser(this.user);

    joints  = new PVector[15];

    for (int i = 0; i < 15; i++){
      joints[i] = new PVector(0,0,0);
    }

  }

  public void updateSkeleton()
  {
    do {
      this.processUpdateMessage(socket.getMessage());
    } while (socket.moreToMessage());


    // Send gestures an update
    setChanged();
    notifyObservers();
  }

  private void processUpdateMessage(String update)
  {
    StringTokenizer sscanf = new StringTokenizer(update, " ");

    String t = sscanf.nextToken(); // Skip user
    t = sscanf.nextToken();
    int limb = Integer.valueOf(t);

    t = sscanf.nextToken();
    joints[limb].x = Float.valueOf(t);

    t = sscanf.nextToken();
    joints[limb].y = Float.valueOf(t);

    t = sscanf.nextToken();
    joints[limb].z = Float.valueOf(t);
  }

  public void drawSkeleton()
  {
    this.updateSkeleton();

    parent.fill(255,255,255);

    //for (PVector vec: joints) {
    for (int i = 0; i < joints.length; i++){
      parent.pushMatrix();
      parent.translate(joints[i].x,joints[i].y,joints[i].z);

      if (i == 1)
        parent.ambientLight(255,255,255);

      if ( i >=3 && i <=5)
        parent.fill(larm_color);
      else if ( i >=6 && i <=8)
        parent.fill(rarm_color);
      else if ( i >=9 && i <=11)
        parent.fill(lleg_color);
      else if ( i >=12 && i <=14)
        parent.fill(rleg_color);

      parent.box(50);
      parent.popMatrix();
    }
  }

  public <E extends GestureListener> void AttachGestureListener(E gesture)
  {
    this.addObserver((GestureListener) gesture);
  }

} // end class
