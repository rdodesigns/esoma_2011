/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 3 (master)
 *
 * Main phinect_sender
 *
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

#include "Callback.h"
#include "Skeleton.h"




//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------
#define SAMPLE_XML_PATH "SamplesConfig.xml"


//---------------------------------------------------------------------------
// Macros
//---------------------------------------------------------------------------

// Taken from sample file. I really like this one.
#define CHECK_RC(rc, what)											\
	if (rc != XN_STATUS_OK)											\
	{																\
		printf("%s failed: %s\n", what, xnGetStatusString(rc));		\
		return rc;													\
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



  HandlerInit();

	user.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

  if (save) {
    xn::Recorder recorder;
    nRetVal = recorder.Create(context);

    nRetVal = recorder.SetDestination(XN_RECORD_MEDIUM_FILE, argv[2]);
    nRetVal = recorder.AddNodeToRecording(depth, XN_CODEC_16Z_EMB_TABLES);
  }

  nRetVal = context.StartGeneratingAll();

  int marker = 0;

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


    for (int i = 1; i <= 24 ; i++) {
      XnVector3D pos = GetBodyPartPosition(1, (XnSkeletonJoint) i);

      zmq::message_t message(6*4);
      snprintf((char *) message.data(), 6*4,
        "%05.1f %05.1f %05.1f ", pos.X, pos.Y, pos.Z);
      //printf("[%d] %05.1f, %05.1f, %05.1f\n", i, pos.X, pos.Y, pos.Z);
      publisher.send(message, (i == 24) ? 0 : ZMQ_SNDMORE);
    }


  }

context.Shutdown();

return 0;
} // end main

