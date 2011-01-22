/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 19 [cleanup] (Sat Jan 22 00:09:41 EST 2011)
 * @parent eb7eb6da42f2dee113645525b3328ba7af3cd96d
 *
 * @section DESCRIPTION
 *
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

import processing.core.*;

import java.util.*;

public class Skeleton {
  private PApplet parent;
  private final int larm_color = 0xffE41A1C; ///< Red
  private final int rarm_color = 0xff377EB8; ///< Blue
  private final int lleg_color = 0xff4DAF4A; ///< Green
  private final int rleg_color = 0xff984EA3; ///< Purple
  private final int graph_size = 192;

  private ArrayList larm_graph;
  private ArrayList rarm_graph;
  private ArrayList lleg_graph;
  private ArrayList rleg_graph;
  private PVector[] joints;

  private Socket socket;
  private int user;

  Skeleton(PApplet parent, Socket socket, int user)
  {
    this.parent = parent;
    this.user   = user;
    this.socket = socket;

    socket.subscribeToUser(this.user);

    larm_graph = new ArrayList();
    rarm_graph = new ArrayList();
    lleg_graph = new ArrayList();
    rleg_graph = new ArrayList();
    joints  = new PVector[15];

    for (int i = 0; i < graph_size; i++){
      larm_graph.add((float) 0);
      rarm_graph.add((float) 0);
      lleg_graph.add((float) 0);
      rleg_graph.add((float) 0);
    }

    for (int i = 0; i < 15; i++){
      joints[i] = new PVector(0,0,0);
    }

  }

  public void updateSkeleton()
  {
    do {
      this.processUpdateMessage(socket.getMessage());
    } while (socket.moreToMessage());
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


    larm_graph.remove(0);
    rarm_graph.remove(0);
    lleg_graph.remove(0);
    rleg_graph.remove(0);

    larm_graph.add(GetPercentDistension(3));
    rarm_graph.add(GetPercentDistension(6));
    lleg_graph.add(GetPercentDistension(9));
    rleg_graph.add(GetPercentDistension(12));


  }

  public void draw2DData()
  {
    parent.pushStyle();
    parent.stroke(255,255,255);
    parent.pushStyle();

    parent.pushMatrix();

      parent.translate(10, parent.height/4 + 20);

      parent.line(10, 0, 10, -parent.height/4);

      parent.strokeWeight(2);
      parent.stroke(larm_color);

      for (int j = 0; j < larm_graph.size() - 1; j++){
        float pt1 = (Float) larm_graph.get(j);
        float pt2 = (Float) larm_graph.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }
    parent.popMatrix();
    parent.popStyle();

    parent.pushStyle();
    parent.pushMatrix();

      parent.translate(parent.width - rarm_graph.size() - 10, parent.height/4 + 20);
      parent.line(rarm_graph.size() - 10, 0, rarm_graph.size() - 10, -parent.height/4);

      parent.strokeWeight(2);
      parent.stroke(rarm_color);

      for (int j = 0; j < rarm_graph.size() - 1; j++){
        float pt1 = (Float) rarm_graph.get(j);
        float pt2 = (Float) rarm_graph.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }
    parent.popMatrix();
    parent.popStyle();

    parent.pushStyle();
    parent.pushMatrix();

      parent.translate( 10, parent.height - 20);
      parent.line(10, 0, 10, -parent.height/4);

      parent.strokeWeight(2);
      parent.stroke(lleg_color);

      for (int j = 0; j < lleg_graph.size() - 1; j++){
        float pt1 = (Float) lleg_graph.get(j);
        float pt2 = (Float) lleg_graph.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }
    parent.popMatrix();
    parent.popStyle();

    parent.pushStyle();
    parent.pushMatrix();

      parent.translate( parent.width - rleg_graph.size() - 10, parent.height - 20);
      parent.line(rleg_graph.size() - 10, 0, rleg_graph.size() - 10, -parent.height/4);

      parent.strokeWeight(2);
      parent.stroke(rleg_color);

      for (int j = 0; j < rleg_graph.size() - 1; j++){
        float pt1 = (Float) rleg_graph.get(j);
        float pt2 = (Float) rleg_graph.get(j+1);
        parent.line(j, -(parent.height/4)*pt1, j + 1, -(parent.height/4)*pt2);
      }
    parent.popMatrix();
    parent.popStyle();
    parent.popStyle();
  }


  private float GetPercentDistension(int limb)
  {
    PVector origin = joints[limb];
    PVector second = joints[limb+1];
    PVector third  = joints[limb+2];

    float hyp_dist  =  PVector.dist(origin, third);
    float side_dist = PVector.dist(origin, second)
                    + PVector.dist(second, third);

    return hyp_dist/side_dist;

  }

}
