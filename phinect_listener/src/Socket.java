/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 19 [cleanup] (Sat Jan 22 00:09:41 EST 2011)
 * @parent eb7eb6da42f2dee113645525b3328ba7af3cd96d
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
