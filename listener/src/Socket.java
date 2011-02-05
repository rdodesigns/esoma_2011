/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 32 [master] (Fri Feb  4 23:07:28 EST 2011)
 * @parent 7e2b7f0eec705d6755a8679bda9052873660306e
 *
 * @section DESCRIPTION
 *
 * An interface to the ZeroMQ (0MQ) library that hides some of the background
 * of listening to the Kinect.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 *
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
