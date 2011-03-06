/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 62 [datacollector] (Sun Mar  6 10:50:08 EST 2011)
 * @parent 2071cf1994accd684ce75b738fe1eb75002eed62
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
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 *
 */

import processing.core.PVector;

import java.util.Observable;
import java.util.StringTokenizer;


public class Skeleton extends Observable {

  private PVector[] joints;
  private PVector[] joints_p;

  private Socket socket;
  private DrawStack draw_stack;
  private int user;

  int smpl_offset;

  int wait;

  Skeleton(Socket socket, DrawStack draw_stack, int user)
  {
    this.user       = user;
    this.socket     = socket;
    this.draw_stack = draw_stack;

    socket.subscribeToUser(this.user);

    smpl_offset = 0;
    wait = 0;

    joints   = new PVector[15];
    joints_p = new PVector[15];

    for (int i = 0; i < 15; i++){
      joints[i] = new PVector(0,0,0);
      joints_p[i] = new PVector(0,0,0);
    }

  }

  public void updateSkeleton()
  {
    wait = wait + 1 % 10;
    if (wait == 0){
      for (int i = 0; i < 15; i++){
        joints_p[i].x = joints[i].x;
        joints_p[i].y = joints[i].y;
        joints_p[i].z = joints[i].z;
      }
    }

    do {
      this.processUpdateMessage(socket.getMessage());
    } while (socket.moreToMessage());


    // Send gestures an update
    setChanged();
    notifyObservers();

    draw_stack.add(new DrawSkeleton(joints));
  }

  // TODO: Move this to DataCollector
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

  public PVector[] getSkeleton()
  {
    return joints;
  }

  public <E extends GestureListener> void AttachGestureListener(E gesture)
  {
    smpl_offset = (smpl_offset + GestureListener.smpl/4 + GestureListener.smpl/8) % GestureListener.pts_t; // Gives 30 equally spaced calculation
    gesture.setSampleOffset(smpl_offset); // opportunities.
    gesture.addDrawStack(draw_stack);
    this.addObserver((GestureListener) gesture);
  }

  // We do this in order to add only DataCollectors, ensuring safe type.
  public <E extends DataCollector> void AttachDataCollector(E data)
  {
    this.addObserver((DataCollector) data);
  }

} // end class
