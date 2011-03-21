/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 75 [master] (Mon Mar 21 05:47:43 EDT 2011)
 * @parent 132af61bc80c4968ff5a120e9c8746bb42381213
 *
 * @section DESCRIPTION
 *
 * Opens up either the Kinect device or plays back a recording. User tracking
 * is performed on this recording, which is then to the TCP port 12345 using
 * ZeroMQ (OMQ). This continues until the user presses a key.
 *
 * This is licensed under GPLv3.
 *
 * This work was conceptualized and created by Ryan Orendorff, Jan 2011.
 * Resources and brainstorming assistance provided through a collaboration with
 * the MIT Media Lab and Tufts University. Contact information is provided
 * below.
 *
 * Ryan Orendorff
 *  email: esoma@rdodesigns.com
 *    www: http://www.rdodesigns.com
 * github: https://github.com/rdodesigns
 *
 * Dr. John Moore
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 75 Amherst Street, Cambridge MA
 * Cambridge, MA 02139 USA
 *
 * Professor Fiorenzo Omenetto
 * Tufts University
 * Department of Biomedical Engineering
 * 4 Colby Street
 * Medford, MA 02155 USA
 */

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnOpenNI.h>
#include <XnLog.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>

#include <zmq.hpp>
#include <string.h>
#include <stdio.h>

#include <Callback.h>
#include <Skeleton.h>
#include <Collector/ExtensionCollector.h>

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define SAMPLE_XML_PATH "SamplesConfig.xml"

//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------

// Taken from sample file. I really like this one.
#define CHECK_RC(rc, what)                                  \
	if (rc != XN_STATUS_OK)                                   \
	{                                                         \
		printf("%s failed: %s\n", what, xnGetStatusString(rc)); \
		return rc;                                              \
	}

//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
using namespace xn;

Context context;
DepthGenerator depth;
UserGenerator user;


//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

int main(int argc, const char *argv[])
{

  // 0MQ stuff
  zmq::context_t zmq_context (1);
  zmq::socket_t publisher (zmq_context, ZMQ_PUB);
  publisher.bind("tcp://*:12345");

  XnStatus nRetVal = XN_STATUS_OK;

  XnBool save = false;

  if (argc > 2)
  {
    // Save to file, currently does not support rerecording (open and save).
    if ((strcmp(argv[1], "save") == 0)) save = true;

    EnumerationErrors errors;
    nRetVal = context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
    if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
    {
      XnChar strError[1024];
      errors.ToString(strError, 1024);
      printf("%s\n", strError);
      return (nRetVal);
    }
    else if (nRetVal != XN_STATUS_OK)
    {
      printf("Open failed: %s\n", xnGetStatusString(nRetVal));
      return (nRetVal);
    }
  }
  else if (argc > 1) {
    nRetVal = context.Init();
    CHECK_RC(nRetVal, "Init");
    nRetVal = context.OpenFileRecording(argv[1]);
    if (nRetVal != XN_STATUS_OK)
    {
      printf("Can't open recording %s: %s\n", argv[1], xnGetStatusString(nRetVal));
      return 1;
    }
  }
  else
  {
    EnumerationErrors errors;
    nRetVal = context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
    if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
    {
      XnChar strError[1024];
      errors.ToString(strError, 1024);
      printf("%s\n", strError);
      return (nRetVal);
    }
    else if (nRetVal != XN_STATUS_OK)
    {
      printf("Open failed: %s\n", xnGetStatusString(nRetVal));
      return (nRetVal);
    }
  }


	nRetVal = context.FindExistingNode(XN_NODE_TYPE_DEPTH, depth);
	CHECK_RC(nRetVal, "Find depth generator");

  nRetVal = context.FindExistingNode(XN_NODE_TYPE_USER, user);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = user.Create(context);
		CHECK_RC(nRetVal, "Find user generator");
	}

  // Sets up the callback functions for user tracking. See Callback.cpp
  HandlerInit();

	user.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

  // Are we recording? If so, do so to argv[2]
  if (save) {
    xn::Recorder recorder;
    nRetVal = recorder.Create(context);

    nRetVal = recorder.SetDestination(XN_RECORD_MEDIUM_FILE, argv[2]);
    nRetVal = recorder.AddNodeToRecording(depth, XN_CODEC_16Z_EMB_TABLES);
  }

  nRetVal = context.StartGeneratingAll();

  // Marker for the Sending... notification.
  int marker = 0;
  Skeleton skeleton((xn::UserGenerator) user);
  ExtensionCollector ext_col(&skeleton, LARM);

  while(!xnOSWasKeyboardHit()) {
    nRetVal = context.WaitAndUpdateAll();
    CHECK_RC(nRetVal, "WaitAndUpdateAll");

    if(!user.GetSkeletonCap().IsTracking(1)) continue;

    marker = ++marker % 60;

    if (marker < 20)
      printf("\rSending.  ");
    else if (marker < 40)
      printf("\rSending.. ");
    else
      printf("\rSending...");

#ifdef _WIN32
    int (*sprintf_sp)( char *buffer, size_t buff_size, const char *format, ... ) = &sprintf_s;
#else
    int (*sprintf_sp)( char *buffer, size_t buff_size, const char *format, ... ) = &snprintf;
#endif

    skeleton.updateSkeleton();
    // Use j to number the joints (currently from 0 to 14)
    for (int i = 0; i < 15 ; i++) {
      XnVector3D pos = skeleton.getJoint(i);

      zmq::message_t message(6*5);

      sprintf_sp((char *) message.data(), 6*5,
        "%d %d %05.1f %05.1f %05.1f ", 1, i, pos.X, pos.Y, pos.Z);
      publisher.send(message, (i == 14) ? 0 : ZMQ_SNDMORE);
    }

  }

context.Shutdown();

return 0;
} // end main

