/**
 * @file
 * @author Ryan Orendorff <ryan@rdodesigns.com>
 * @version 21 [master] (Sat Jan 22 02:49:12 EST 2011)
 * @parent d2daf7d110ac3e419c415876621e52a01c4a76b0
 *
 * @section DESCRIPTION
 *
 * Callback functions for determining what to do during certain user tracking
 * events, such as finding a new user and calibrating that user's skeleton.
 *
 * This is licensed under GPLv3.
 *
 * MIT Media Lab
 * New Media Medicine Group
 * E14, 20 Ames Street
 * Cambridge, MA 02139 USA
 */

#include "Callback.h"

// XN_CALLBACK_TYPE is defined as nothing (it is for convention)

/*
 * Callback Syntax:
 * typedef void(* XnUserHandler)(XnNodeHandle hNode, XnUserID userGenerator,
 *                               void *pCookie)
 * param hNode: Handle to the userGenerator generator (a reference)
 * param userGenerator: The userGenerator related to the event (unsigned int32)
 * param pCookie: User cookie passed to all callback functions.
 */

// Defined in main.cpp
extern xn::UserGenerator user;

XnBool g_bNeedPose = FALSE;
XnChar g_strPose[20] = "";

/**
 * What to do when new user is found, ask if pose detection or calibration is
 * required next.
 */
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	printf("\rNew User %d\n", nId);
	// New userGenerator found
	if (g_bNeedPose)
	{
		user.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
	}
	else
	{
		user.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
}


/**
 * What to do when a userGenerator is lost (just prints out "Lost User %d", id
 */
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	printf("\rLost User %d\n", nId);
}


/**
 * What to do when a pose is detected (but not calibrated)
 */
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
{
	printf("Pose %s detected for User %d\n", strPose, nId);
	user.GetPoseDetectionCap().StopPoseDetection(nId);
	user.GetSkeletonCap().RequestCalibration(nId, TRUE);
}


/**
 * What to do when calibration starts (only prints "Calibration sarting for
 * userGenerator %d", id)
 */
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
{
	printf("Calibration started for User %d\n", nId);
}


/**
 * What to do when the pose calibration is done.
 * Starts tracking the skeleton if the calibration succeeded.
 * If calibration failed, then either look for pose (if pose was lost) or
 * restart the calibration process.
 */
void XN_CALLBACK_TYPE UserCalibration_CalibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie)
{
	if (bSuccess)
	{
		printf("Calibration complete, start tracking User %d\n", nId);
		user.GetSkeletonCap().StartTracking(nId);
	}
	else
	{
		printf("Calibration failed for User %d\n", nId);
		if (g_bNeedPose)
		{
			user.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
		}
		else
		{
			user.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}
}

void HandlerInit()
{

  XnCallbackHandle hUserCallbacks, hCalibrationCallbacks, hPoseCallbacks;

  /* RegisterUserCallbacks
   *
   * param NewUserCB: Function pointer to be called when new user is IDed.
   * param LostUserCB: Function pointer to be called when user lost
   * param pCookie: Cookie for the user, sent to the callback functions.
   * param phCallback: Handle for callbacks (allows unregistration)
   */
  user.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL,
                             hUserCallbacks);


  user.GetSkeletonCap().RegisterCalibrationCallbacks(
      UserCalibration_CalibrationStart,
      UserCalibration_CalibrationEnd,
      NULL,
      hCalibrationCallbacks);

}
