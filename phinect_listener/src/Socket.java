/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 20 [master] (Sat Jan 22 00:13:27 EST 2011)
 * @parent f9b2244c1712921defcac5c8f6c910f1e1f28cae
 *
 * Skeleton class
 *
 */


import processing.core.PApplet;
import org.zeromq.ZMQ;

public class Socket {
  PApplet parent;

  ZMQ.Context context;
  ZMQ.Socket subscriber;

  Socket(PApplet parent) {
    this.parent = parent;

    context = ZMQ.context(1);
    subscriber = context.socket(ZMQ.SUB);

    // Subscription information
    subscriber.connect("tcp://localhost:12345");
  }

  public void subscribeToUser(int user)
  {
    String user_name = Integer.toString(user);
    subscriber.subscribe(user_name.getBytes());
  }

  public String getMessage()
  {
    return new String(subscriber.recv(0)).trim();
  }

  public boolean moreToMessage()
  {
    return subscriber.hasReceiveMore();
  }

}
