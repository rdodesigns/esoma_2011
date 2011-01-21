import processing.core.*;
import processing.xml.*;
import processing.opengl.*;

import java.applet.*;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.event.MouseEvent;
import java.awt.event.KeyEvent;
import java.awt.event.FocusEvent;
import java.awt.Image;
import java.io.*;
import java.net.*;
import java.text.*;
import java.util.*;
import java.util.zip.*;
import java.util.regex.*;

import java.util.StringTokenizer;
import org.zeromq.ZMQ;

public class phinect_listener extends PApplet {

  ZMQ.Context context;
  ZMQ.Socket subscriber;
  ArrayList larm_graph = new ArrayList();
  ArrayList rarm_graph = new ArrayList();
  ArrayList lleg_graph = new ArrayList();
  ArrayList rleg_graph = new ArrayList();
  PVector[] positions = new PVector[24];
  Skeleton skeleton = new Skeleton(this);

  static final int larm_color = 0xffE41A1C;
  static final int rarm_color = 0xff377EB8;
  static final int lleg_color = 0xff4DAF4A;
  static final int rleg_color = 0xff984EA3;

  public void setup() {

    size(640,480, OPENGL);
    hint(DISABLE_OPENGL_2X_SMOOTH);
    context = ZMQ.context(1);
    //  Socket to talk to server
    System.out.println("Listening for Kinect...");
    subscriber = context.socket(ZMQ.SUB);
    subscriber.connect("tcp://localhost:12345");
    //  Subscribe to zipcode, default is NYC, 10001
    String no_sub = "";
    subscriber.subscribe(no_sub.getBytes());

    frameRate(30);
    fill(255, 255, 255);

    for (int i = 0; i < 192; i++){
      larm_graph.add((float) 0);
      rarm_graph.add((float) 0);
      lleg_graph.add((float) 0);
      rleg_graph.add((float) 0);
    }

    for (int i = 0; i < 24; i++){
      positions[i] = new PVector(0,0,0);
    }
  }

  public void draw() {

    background(0);
    lights();
    camera(0f, 0f, 0f, -272.6f, -111.8f, 2972.2f, 0f, -1f, 1f);

    int i = 0;
    float pos_x, pos_y, pos_z;
    String update;

    while (true) {
      pushMatrix();

      update = new String(subscriber.recv(0)).trim();

      StringTokenizer sscanf = new StringTokenizer(update, " ");
      String t = sscanf.nextToken();
      pos_x = Float.valueOf(t);

      t = sscanf.nextToken();
      pos_y = Float.valueOf(t);

      t = sscanf.nextToken();
      pos_z = Float.valueOf(t);


      translate(pos_x, pos_y, pos_z);
      pushStyle();
      if (i == 5 || i == 6 || i ==8){
        fill(larm_color);
      } else if ( i == 11 || i == 12 || i == 14){
        fill(rarm_color);
      } else if ( i == 16 || i == 17 || i == 19) {
        fill(lleg_color);
      } else if ( i == 20 || i == 21 || i == 23) {
        fill(rleg_color);
      }
      box(50);
      popStyle();


      popMatrix();

      positions[i].set(pos_x,pos_y,pos_z);

      i++;
      if (!subscriber.hasReceiveMore()) break;
    }// end packet while

    larm_graph.remove(0);
    rarm_graph.remove(0);
    lleg_graph.remove(0);
    rleg_graph.remove(0);

    larm_graph.add(GetPercentDistension(5));
    rarm_graph.add(GetPercentDistension(11));
    lleg_graph.add(GetPercentDistension(16));
    rleg_graph.add(GetPercentDistension(20));

    // End 3D
    camera();
    javax.media.opengl.GL gl=((PGraphicsOpenGL)g).beginGL();
    gl.glClear(javax.media.opengl.GL.GL_DEPTH_BUFFER_BIT);
    gl.glDisable(javax.media.opengl.GL.GL_BLEND);
    ((PGraphicsOpenGL)g).endGL();

    // Begin 2D

    pushStyle();
    stroke(255,255,255);
    pushStyle();

    pushMatrix();

      translate(10, height/4 + 20);

      line(10, 0, 10, -height/4);

      strokeWeight(2);
      stroke(larm_color);

      for (int j = 0; j < larm_graph.size() - 1; j++){
        float pt1 = (Float) larm_graph.get(j);
        float pt2 = (Float) larm_graph.get(j+1);
        line(j, -(height/4)*pt1, j + 1, -(height/4)*pt2);
      }
    popMatrix();
    popStyle();

    pushStyle();
    pushMatrix();

      translate(width - rarm_graph.size() - 10, height/4 + 20);
      line(rarm_graph.size() - 10, 0, rarm_graph.size() - 10, -height/4);

      strokeWeight(2);
      stroke(rarm_color);

      for (int j = 0; j < rarm_graph.size() - 1; j++){
        float pt1 = (Float) rarm_graph.get(j);
        float pt2 = (Float) rarm_graph.get(j+1);
        line(j, -(height/4)*pt1, j + 1, -(height/4)*pt2);
      }
    popMatrix();
    popStyle();

    pushStyle();
    pushMatrix();

      translate( 10, height - 20);
      line(10, 0, 10, -height/4);

      strokeWeight(2);
      stroke(lleg_color);

      for (int j = 0; j < lleg_graph.size() - 1; j++){
        float pt1 = (Float) lleg_graph.get(j);
        float pt2 = (Float) lleg_graph.get(j+1);
        line(j, -(height/4)*pt1, j + 1, -(height/4)*pt2);
      }
    popMatrix();
    popStyle();

    pushStyle();
    pushMatrix();

      translate( width - rleg_graph.size() - 10, height - 20);
      line(rleg_graph.size() - 10, 0, rleg_graph.size() - 10, -height/4);

      strokeWeight(2);
      stroke(rleg_color);

      for (int j = 0; j < rleg_graph.size() - 1; j++){
        float pt1 = (Float) rleg_graph.get(j);
        float pt2 = (Float) rleg_graph.get(j+1);
        line(j, -(height/4)*pt1, j + 1, -(height/4)*pt2);
      }
    popMatrix();
    popStyle();
    popStyle();

  }

  public String timeStamp()
  {
    String year = String.valueOf(year());

    String  mon =  month() < 10 ? "0"+String.valueOf(month())
                                : String.valueOf(month());

    String  day =    day() < 10 ? "0"+String.valueOf(day())
                                : String.valueOf(day());

    String hour =   hour() < 10 ? "0"+String.valueOf(hour())
                                : String.valueOf(hour());

    String  min = minute() < 10 ? "0"+String.valueOf(minute())
                                : String.valueOf(minute());

    String  sec = second() < 10 ? "0"+String.valueOf(second())
                                : String.valueOf(second());

    return year+mon+day+hour+min+sec;

  }

  public void keyPressed() {
    //if (key == ' ') {
      //System.out.println("AHHAHAHAHAHA");
    //}
  }

  private float GetPercentDistension(int limb)
  {
    PVector origin = positions[limb];
    PVector second = positions[limb+1];
    PVector third  = positions[limb+3];

    float hyp_dist  =  PVector.dist(origin, third);
    float side_dist = PVector.dist(origin, second)
                    + PVector.dist(second, third);

    return hyp_dist/side_dist;

  }

  public static void main(String args[]) {
    PApplet.main(new String[] { "phinect_listener" });
  }

}

