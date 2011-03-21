/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:42 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * An interface to the ZeroMQ (0MQ) library that hides some of the background
 * of listening to the Kinect.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 *
 * Contact Information
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 */

import org.zeromq.ZMQ;

public class Socket {
  ZMQ.Context context;
  ZMQ.Socket subscriber;

  Socket() {

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
