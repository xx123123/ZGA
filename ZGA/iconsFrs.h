/*
 * ICONS FRS - Facial Recognition Device Interface Function Header
 *
 * Author: ICO
 * Date: 2015/05/19
 *
 * REMARK:
 *  Directive __DEFINE_FUNC_PTR should be defined in application invoking
 *  interfaces defined (e.g. Core program) 
 *
 *  Interface function header and function pointer to interface function
 *  are kept together to avoid inconsistency.
 */

#ifndef _ICONSFRS_h
#define _ICONSFRS_h

#ifdef __cplusplus
extern "C" {
#endif

#include "iconsConst.h"

//Camera ID
#define	ICONS_FRS_CAM_DEFAULT						0
#define ICONS_FRS_CAM_ARRIVE_SIGNON					1
#define ICONS_FRS_CAM_ARRIVE_CLEARANCE				2  //Liveness
#define ICONS_FRS_CAM_DEPART_SIGNON					3
#define ICONS_FRS_CAM_DEPART_CLEARANCE				4  //Liveness
#define ICONS_FRS_CAM_ARRIVAL_COUNTER				5
#define ICONS_FRS_CAM_AUTOMATIC_VEHICLE_CLEARANCE	6  //Liveness
#define ICONS_FRS_CAM_SELF_ENROLMENT_KIOSK			7  //Liveness
#define ICONS_FRS_CAM_ENROLMENT_WORKSTATION			8
#define ICONS_FRS_CAM_FACIAL_SIGNON					9
#define ICONS_FRS_CAM_EWARRANT_CARD_VERIFICATION	10
#define ICONS_FRS_CAM_SUPERVISOR_WORKSTATION		11
#define ICONS_FRS_CAM_MOBILE_NOTEBOOK				12

#define ICONS_FRS_CAM_RECTANGULAR	0
#define	ICONS_FRS_CAM_BALL		1

//Security level
#define ICONS_FRS_QUAL_LOW	0
#define ICONS_FRS_QUAL_MEDIUM	1
#define ICONS_FRS_QUAL_HIGH	2


#define ICONS_FRS_LIVENESS_LOW	0
#define ICONS_FRS_LIVENESS_MEDIUM	1
#define ICONS_FRS_LIVENESS_HIGH	2
#define	ICONS_FRS_FACE_NOT_DETECTED	-801
#define	ICONS_FRS_LIVENESS_FAIL		-802
#define	ICONS_FRS_FACE_MATCH_FAIL	-803


#define	ICONS_FRS_LIGHT_INACTIVE	0	// switch off the indicator light
						// (indicate the camera is inactive)
#define	ICONS_FRS_LIGHT_ACTIVE		1	// indicator flashing in yellow
						// (indicate the camera is doing facial matching)
#define ICONS_FRS_LIGHT_ERROR		2	// indicator keep in yellow (indicate the clearance is in error)
#define ICONS_FRS_LIGHT_SUCCESS		3	// indicator keep in green (indicate the clearance is successful)


struct _iconsFace {
	long size;
	short isTemplate;
	unsigned char *image;
};
typedef struct _iconsFace iconsFace;

/*
 * GetStatus - Get current status of the Facial Recognition Device
 *
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_OPERATION_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 *	ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GetStatus();
#else
typedef int (*pGetStatus)();
#endif

/*
 * GeDrivertStatus - Get current status of the Facial Engine and all related software drivers
 *
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_OPERATION_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 *	ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GetDriverStatus();
#else
typedef int (*pGetDriverStatus)();
#endif

/*
 * GetCamStatus - Get current status of the specified camera
 *
 * Parameter:
 *	camName - logical id of camera
 *
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_OPERATION_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 *	ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GetCamStatus(int camNo);
#else
typedef int (*pGetCamStatus)(int camNo);
#endif

/*
 * GetCamType - Get type (rectangular or ball) of the specified camera
 *
 * Parameter:
 *	camName - logical id of camera
 *
 * Return:
 *	ICONS_FRS_CAMERA_RECTANGULAR
 *	ICONS_FRS_CAMERA_BALL
 *	ICONS_OPERATION_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GetCamType(int camNo);
#else
typedef int (*pGetCamType)(int camNo);
#endif

/*
 * StartPhotoTaking - Trigger the camera to take photo for the passenger
 *                 	Camera continue to take photo until it is stopped by
 *			StopPhotoTaking or StopPhototakingEx method.
 *
 * Parameter:
 *	camName - logical id of camera
 *	expirePeriod - the expiry period (in millisecond).
 *			the best quality photo within the expiry period before
 *			StopPhotoTaking method is invoked will be returned
 *
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL StartPhotoTaking (int camName, int expirePeriod);
#else
typedef int (*pStartPhotoTaking)(int canName, int expirePeriod);
#endif



/*
 * StopPhotoTaking - Stop the camera photo taking which is triggered by
 *			StartPhotoTaking method.  The best image captured
 *			within the expired period will be returned.
 * Parameter:
 *	camName - logical id of the camera
 *	pImage - optional, passenger's passport image for eliminating unwanted
 *			face selection
 *	pFace - (Output) facial image of captured
 *	pTemplate - (Output) Facial template of the captured facial image
 *	templateId - (Output) Facial template ID
 *	quality - (Output) Query face quality.  Either one of the followings:
 *			ICONS_FRS_QUAL_LOW
 *			ICONS_FRS_QUAL_MEDIUM
 *			ICONS_FRS_QUAL_HIGH
 *	croppedImage - (Output) Cropped input photo will be return as well if the
 *			input photo is matched with the captured photo.
 *	
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_OPERATION_FAIL
 *	ICONS_FRS_FACE_NOT_DETECTED
 *	ICONS_FRS_LIVENESS_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 *      ICONS_FRS_FACE_MATCH_FAIL
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL StopPhotoTaking (int camName, iconsFace *pImage,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
#else
typedef int (*pStopPhotoTaking)(int camName, iconsFace *pImage,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
#endif

/*
 * StopPhotoTakingEx - Stop the camera photo taking which is triggered by
 *			StartPhotoTaking method.  The best image captured
 *			within the expired period will be returned.
 * Parameter:
 *	camName - logical id of the camera
 *	pImage - optional, passenger's passport image for eliminating unwanted
 *			face selection
 *	pFace - (Output) facial image of captured
 *	pTemplate - (Output) Facial template of the captured facial image
 *	templateId - (Output) Facial template ID
 *	quality - (Output) Query face quality score (0 - 1000)
 *	croppedImage - (Output) Cropped input photo will be return as well if the
 *			input photo is matched with the captured photo.
 *	
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_OPERATION_FAIL
 *	ICONS_FRS_FACE_NOT_DETECTED
 *	ICONS_FRS_LIVENESS_FAIL
 *	ICONS_DEV_ERROR
 *	ICONS_DEV_NOT_AVAILABLE
 *      ICONS_FRS_FACE_MATCH_FAIL
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL StopPhotoTakingEx (int camName, iconsFace *pImage,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
#else
typedef int (*pStopPhotoTakingEx)(int camName, iconsFace *pImage,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
#endif


/*
 * CompareFaces - Trigger the camera to take photo and the captured photo
 *		   should equal or higher than the input query photo quality
 *		   flag.  After the photo is taken, it will be compared with
 *		   input facial templates or photos.
 *		  When the checking finishes, the method will return,
 *		  Otherwise, it will be stopped either by timeout or
 *		   InterruptCompareFaces method is invoked
 *
 * Parameters:
 *	camName - logical camera ID
 *	facialList - null-terminated list of facial templates or photos to be
 *			compared with the live captured photo
 *	matchThreshold - Matching threshold
 *	qualityThreshold - Query photo quality threshold (ICONS_FRS_QUAL_LOW,
 *			ICONS_FRS_QUAL_MEDIUM or ICONS_FRS_QUAL_HIGH)
 *	livenessThreshold - Liveness threshold (ICONS_FRS_LIVENESS_LOW,
 *			ICONS_FRS_LIVENESS_MEDIUM or ICONS_FRS_LIVENESS_HIGH)
 *	timeoutPeriod - Timeout period in millisecond
 *	maxRetries - Maximum no. of retry for face comparison
 *			(-1 means unlimited)
 *	headCount - (Output) Head counted in the image
 *	imgCaptured - (Output) Facial image captured from camera
 *	matchScoreList - (Output) List of best match score (for each of the
 *			list of submitted facial data)
 *      numMatchAttempt - (Output) No. of matching attempts
 *	referenceId (input) - reference string for this trial match (e.g. cleaqrance ID or I/Card no.)
 *	timeForRecognise (Output) Offset time before recognising a face image
 *
 * Return:
 *	respCode - consolidated response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_USER_STOP
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_FRS_FACE_MATCH_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */

#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CompareFaces (int camName, iconsFace *facialList[],
		float matchThreshold, int qualityThreshold,
		int livenessThreshold, int timeoutPeriod, int maxRetries,
		int *headCount, iconsFace *imgCaptured,
		float *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
#else
typedef int (*pCompareFaces)(int camName, iconsFace *facialList[],
		float matchThreshold, int qualityThreshold,
		int livenessThreshold, int timeoutPeriod, int maxRetries,
		int *headCount, iconsFace *imgCaptured,
		float *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
#endif

/*
 * MatchFaces - Trigger the camera to take photo and the captured photo
 *		   should equal or higher than the input query photo quality
 *		   flag.  After the photo is taken, it will be compared with
 *		   input facial templates or photos.
 *		  When the checking finishes, the method will return,
 *		  Otherwise, it will be stopped either by timeout or
 *		   InterruptMatchFaces method is invoked
 *
 * Parameters:
 *	camName - logical camera ID
 *	facialList - null-terminated list of facial templates or photos to be
 *			compared with the live captured photo
 *	matchThreshold - Matching threshold (0 - 1000)
 *	qualityThreshold - Query photo quality threshold (0 - 1000)
 *	enableLivenessCheck - Enable liveness checking (1), otherwise, disabled (0)
 *	livenessThreshold - Liveness threshold (0 - 1000),
 *	timeoutPeriod - Timeout period in millisecond
 *	maxRetries - Maximum no. of retry for face comparison (-1 means unlimited)
 *	headCount - (Output) Head counted in the image
 *	imgCaptured - (Output) Facial image captured from camera
 *	matchScoreList - (Output) List of best match score (for each of the
 *			list of submitted facial data)
 *      numMatchAttempt - (Output) No. of matching attempts
 *	referenceId (input) - reference string for this trial match (e.g. cleaqrance ID or I/Card no.)
 *	timeForRecognise (Output) Offset time before recognising a face image
 *
 * Return:
 *	respCode - consolidated response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_USER_STOP
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_FRS_FACE_MATCH_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */

#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL MatchFaces (int camName, iconsFace *facialList[],
		int matchThreshold, int qualityThreshold, int enableLivenessCheck,
		int livenessThreshold, int timeoutPeriod, int maxRetries,
		int *headCount, iconsFace *imgCaptured,
		int *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
#else
typedef int (*pMatchFaces)(int camName, iconsFace *facialList[],
		int matchThreshold, int qualityThreshold, int enableLivenesCheck,
		int livenessThreshold, int timeoutPeriod, int maxRetries,
		int *headCount, iconsFace *imgCaptured,
		int *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
#endif



/*
 * SetIndicatorLight - Change the status of indicator light on the specified camera
 *
 * Parameters:
 *	camName (input) - logical camera name
 *	lightStatus (input) - required status to be applied:
 *		LIGHT_INACTIVE (0) - switch off the indicator light (indicate the camera is inactive)
 *		LIGHT_ACTIVE (1) - indicator flashing in yellow (indicate the camera is doing facial matching)
 *		LIGHT_ERROR (2) - indicator keep in yellow (indicate the clearance is in error)
 *		LIGHT_SUCCESS (3) - indicator keep in green (indicate the clearance is successful)
 *	referenceId (input) - reference string for this trial match (e.g. cleaqrance ID or I/Card no.)
 *
 * Return: result of status change on the indicator light
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL SetIndicatorLight (int camName, int lightStatus, char *referenceID);
#else
typedef int (*pSetIndicatorLight) (int camName, int lightStatus, char *referenceID);
#endif

/*
 * DetectFace - Check for existance of faces in the camera image and count
 *		for non-spoofing faces
 *
 * Parameters:
 *	camName - logical camera name
 *	interleavingPeriod - period (in milliseconds) between 2 checkings
 *	pImage - (Output) full image captured for the counted result
 *
 * Return:
 *	headCount - no. of non-spoofing faces counted in the image, or errors:
 *		ICONS_OPERATION_FAIL
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_USER_STOP
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL DetectFace (int camName, int interleavingPeriod, iconsFace *pImage);
#else
typedef int (*pDetectFace)(int camName, int interleavingPeriod, iconsFace *pImage);
#endif


/*
 * CheckLiveness - Make use of the anti-spoofing technology to check the face
 *			image is a live human or not
 *
 * Parameter:
 *	camName - logical camera ID
 *	livenessThreshold - Liveness threshold (ICONS_FRS_LIVENESS_LOW,
 *			ICONS_FRS_LIVENESS_MEDIUM or ICONS_FRS_LIVENESS_HIGH)
 *	timeoutPeriod - Timeout period in millisecond
 *
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_FAIL
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CheckLiveness (int camName, int livenessThreshold,
		int timeoutPeriod);
#else
typedef int (*pCheckLiveness)(int camName, int livenessThreshold,
		int timeoutPeriod);
#endif

/*
 * CheckLivenessEx - Make use of the anti-spoofing technology to check the face
 *			image is a live human or not
 *
 * Parameter:
 *	camName - logical camera ID
 *	livenessThreshold - Liveness threshold (0 - 1000)
 *	timeoutPeriod - Timeout period in millisecond
 *
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_FAIL
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CheckLivenessEx (int camName, int livenessThreshold,
		int timeoutPeriod);
#else
typedef int (*pCheckLivenessEx)(int camName, int livenessThreshold,
		int timeoutPeriod);
#endif


/*
 * VerifyFace - 1 to 1 faces comparison.  It will automatically convert
 *		the photo to template before comparison, if necessary
 *
 * Parameter:
 *	pImage1 - facial template or raw photo image 1
 *	pImage2 - facial Template or raw photo image 2
 *	matchScore - (Output) Matching score
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_MATCH_FAIL
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL VerifyFace (iconsFace *pImage1, iconsFace *pImage2,
				float *matchScore);
#else
typedef int (*pVerifyFace)(iconsFace *pImage1, iconsFace *pImage2,
				float *matchScore);
#endif

/*
 * VerifyFaces - 1 to 1 faces comparison and returns an integral matching score.
 *               It will automatically convert the photo to template before comparison,
 *               if necessary
 *
 * Parameter:
 *	pImage1 - facial template or raw photo image 1
 *	pImage2 - facial Template or raw photo image 2
 *	matchScore - (Output) Integral Matching score (0 - 1000)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_MATCH_FAIL
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL VerifyFaces (iconsFace *pImage1, iconsFace *pImage2,
				int *matchScore);
#else
typedef int (*pVerifyFaces)(iconsFace *pImage1, iconsFace *pImage2,
				int *matchScore);
#endif


/*
 * GenerateFaceImageAndTemplate - Detect the face from raw photo image and
 *				crop the face out in upright orientation and
 *				return facial image and face template.
 *				The cropping will retry with the orientation
 *				input sequence if the image cannot be cropped
 *
 * Parameter:
 *	pImage - raw photo image
 *	minEyeDist - minimum pixels between eyes
 *	maxEyeDist - maximum pixels between eyes
 *	orientation - Face orientation sequence
 *	pFace - (Output) Facial image cropped
 *	pTemplate - (Output) Facial template of the image cropped
 *	templateId - (Output) Facial template ID
 *	quality - (Output) Query face quality (ICONS_FRS_QUAL_LOW,
 *			ICONS_FRS_QUAL_MEDIUM or ICONS_FRS_QUAL_HIGH)
 *	leftEyePos - (Output) left eye coordinates
 *	rightEyePos - (Output) right eye coordindates
 *	faceRect - (Output) face rectangle
 *	headRect - (Output) head rectangle
 *	cropRect - (Output) cropped rectangle
 *	faceOrientation - (Output) face orientation
 *				(rotate clockwise by 0 - 0 deg; 1 - 90 deg; 2 - 180 deg; 3 - 270 deg)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GenerateFaceImageAndTemplate (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, int orientation[],
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#else
typedef int (*pGenerateFaceImageAndTemplate) (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, int orientation[],
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#endif

/*
 * GenerateFaceImageAndTemplateEx - Detect the face from raw photo image and
 *				crop the face out in upright orientation and
 *				return facial image and face template.
 *				The cropping will retry with the orientation
 *				input sequence if the image cannot be cropped
 *
 * Parameter:
 *	pImage - raw photo image
 *	minEyeDist - minimum pixels between eyes
 *	maxEyeDist - maximum pixels between eyes
 *	orientation - Face orientation sequence
 *	pFace - (Output) Facial image cropped
 *	pTemplate - (Output) Facial template of the image cropped
 *	templateId - (Output) Facial template ID
 *	quality - (Output) Query face quality score (0 - 1000)
 *	leftEyePos - (Output) left eye coordinates
 *	rightEyePos - (Output) right eye coordindates
 *	faceRect - (Output) face rectangle
 *	headRect - (Output) head rectangle
 *	cropRect - (Output) cropped rectangle
 *	faceOrientation - (Output) face orientation
 *				(rotate clockwise by 0 - 0 deg; 1 - 90 deg; 2 - 180 deg; 3 - 270 deg)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GenerateFaceImageAndTemplateEx (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, int orientation[],
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#else
typedef int (*pGenerateFaceImageAndTemplateEx) (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, int orientation[],
		iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#endif


/*
 * CropFace - Detect the face from raw photo image and crop the face out in
 *		upright orientation
 *
 * Parameters:
 *	pImage - raw photo image
 *	minEyeDist - minimum pixels between eyes
 *	maxEyeDist - maximum pixels between eyes
 *	pFace - (Output) facial image cropped
 *	leftEyePos - (Output) left eye coordinates
 *	rightEyePos - (Output) right eye coordinates
 *	faceRect - (Output) face rectangle
 *	headRect - (Output) head rectangle
 *	cropRect - (Output) cropped rectangle
 *	faceOrientation - (Output) face orientation
 *				(rotate clockwise by 0 - 0 deg; 1 - 90 deg; 2 - 180 deg; 3 - 270 deg)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CropFace (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, iconsFace *pFace,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#else
typedef int (*pCropFace) (iconsFace *pImage,
		int minEyeDist, int maxEyeDist, iconsFace *pFace,
		POINT *leftEyePos, POINT *rightEyePos,
		RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
#endif


/*
 * GenerateFacialTemplate - User select the eye coordinates and generate
 *				the facial template
 *
 * Parameters:
 *	pImage - raw photo image
 *	leftEyePos - left eye coordinates
 *	rightEyePos - right eye coordinates
 *	pFace - (Output) facial image cropped
 *	pTemplate - (Output) facial template of the image cropped
 *	templateId - (Output) facial template ID
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GenerateFacialTemplate (iconsFace *pImage,
		POINT *leftEyePos, POINT *rightEyePos,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId);
#else
typedef int (*pGenerateFacialTemplate)(iconsFace *pImage,
		POINT *leftEyePos, POINT *rightEyePos,
		iconsFace *pFace, iconsFace *pTemplate, char *templateId);
#endif



/*
 * InitializeCamera - Initialize the camera (for speed up start up time for
 *			photo taking or face comparing functions)
 *
 * Parameters:
 *	camName - logical camera name
 *	urlStreaming - (Output) URL for streaming
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL InitializeCamera (int camName, char *urlStreaming);
#else
typedef int (*pInitializeCamera)(int camName, char *urlStreaming);
#endif


/*
 * DeinitializeCamera - release the resources allocated by initializeCamera
 *
 * Parameter:
 *	camName - logical camera name
 *
 * Return:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL DeinitializeCamera (int camName);
#else
typedef int (*pDeinitializeCamera)(int camName);
#endif


/* InterruptCompareFaces - stop the CompareFaces method
 *
 * Parameter:
 *	camName - logical camera name
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL InterruptCompareFaces (int camName);
#else
typedef int (*pInterruptCompareFaces)(int camName);
#endif

/* InterruptMatchFaces - stop the MatchFaces method
 *
 * Parameter:
 *	camName - logical camera name
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL InterruptMatchFaces (int camName);
#else
typedef int (*pInterruptMatchFaces)(int camName);
#endif


/* InterruptDetectFace - stop the DetectFace method
 *
 * Parameter:
 *	camName - logical camera name
 *
 * Return:
 *		ICONS_NO_ERROR
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL InterruptDetectFace (int camName);
#else
typedef int (*pInterruptDetectFace)(int camName);
#endif


/*
 * CheckQueryFaceQuality - Face quality check before identification /
 *				verification frontal face score, pixel
 *				between eyes and so on
 *
 * Parameters:
 *	pImage - raw photo image
 *	minEyeDist - minimum pixels between eyes
 *	maxEyeDist - maximum pixels between eyes
 *	quality - (Output) Query face quality (ICONS_FRS_QUAL_LOW,
 *			ICONS_FRS_QUAL_MEDIUM or ICONS_FRS_QUAL_HIGH)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CheckQueryFaceQuality (iconsFace *pImage,
		int minEyeDist, int maxEyeDist,  int *quality);
#else
typedef int (*pCheckQueryFaceQuality)(iconsFace *pImage,
		int minEyeDist, int maxEyeDist,  int *quality);
#endif

/*
 * CheckQueryFaceQualityEx - Face quality check before identification /
 *				verification frontal face score, pixel
 *				between eyes and so on
 *
 * Parameters:
 *	pImage - raw photo image
 *	minEyeDist - minimum pixels between eyes
 *	maxEyeDist - maximum pixels between eyes
 *	quality - (Output) Query face quality score (0 - 1000)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL CheckQueryFaceQualityEx (iconsFace *pImage,
		int minEyeDist, int maxEyeDist,  int *quality);
#else
typedef int (*pCheckQueryFaceQualityEx)(iconsFace *pImage,
		int minEyeDist, int maxEyeDist,  int *quality);
#endif


/*
 * TakePhoto - This trigger the camera to take one photo
 *
 * Parameter:
 *	camName - logical camera name
 *	pFace - (Output) facial image cropped
 *	pTemplate - (Output) facial template of the image cropped
 *	templateId - (Output) facial template ID
 *	quality - (Output) Query face quality (ICONS_FRS_QUAL_LOW,
 *			ICONS_FRS_QUAL_MEDIUM or ICONS_FRS_QUAL_HIGH)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL TakePhoto (int camName, iconsFace *pFace,
			iconsFace *pTemplate, char *templateId, int *quality);
#else
typedef int (*pTakePhoto)(int camName, iconsFace *pFace,
			iconsFace *pTemplate, char *templateId, int *quality);
#endif

/*
 * TakePhotoEx - This trigger the camera to take one photo
 *
 * Parameter:
 *	camName - logical camera name
 *	pFace - (Output) facial image cropped
 *	pTemplate - (Output) facial template of the image cropped
 *	templateId - (Output) facial template ID
 *	quality - (Output) Query face quality score (0 - 1000)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL TakePhotoEx (int camName, iconsFace *pFace,
			iconsFace *pTemplate, char *templateId, int *quality);
#else
typedef int (*pTakePhotoEx)(int camName, iconsFace *pFace,
			iconsFace *pTemplate, char *templateId, int *quality);
#endif


/*
 * TakePhotoWithAntiSpoofing - This trigger the camera to take photo
 *				continuously until timeout.
 *			       The best photo will be returned.
 *			       Anti-spoofing check will be performed.
 *			       If anti-spoofing check is not passed,
 *				an error will be returned
 *
 * Parameter:
 *	camName - logical camera name
 *	livenessThreshold - Liveness threshold (ICONS_FRS_LIVENESS_LOW,
 *			ICONS_FRS_LIVENESS_MEDIUM or ICONS_FRS_LIVENESS_HIGH)
 *	timeoutPeriod - Timeout period in millisecond
 *	pFace - (Output) facial image cropped
 *	pTemplate - (Output) facial template of the image cropped
 *	templateId - (Output) facial template ID
 *	quality - (Output) Query face quality (ICONS_FRS_QUAL_LOW,
 *			ICONS_FRS_QUAL_MEDIUM or ICONS_FRS_QUAL_HIGH)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL TakePhotoWithAntiSpoofing (int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
		char *templateId, int *quality);
#else
typedef int (*pTakePhotoWithAntiSpoofing)(int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
		char *templateId, int *quality);
#endif

/*
 * TakePhotoWithAntiSpoofingEx - This trigger the camera to take photo
 *				continuously until timeout.
 *			       The best photo will be returned.
 *			       Anti-spoofing check will be performed.
 *			       If anti-spoofing check is not passed,
 *				an error will be returned
 *
 * Parameter:
 *	camName - logical camera name
 *	livenessThreshold - Liveness threshold (0 - 1000)
 *	timeoutPeriod - Timeout period in millisecond
 *	pFace - (Output) facial image cropped
 *	pTemplate - (Output) facial template of the image cropped
 *	templateId - (Output) facial template ID
 *	quality - (Output) Query face quality score (0 - 1000)
 *
 * Return:
 *	respCode - response code:
 *		ICONS_NO_ERROR
 *		ICONS_FRS_FACE_NOT_DETECTED
 *		ICONS_FRS_LIVENESS_FAIL
 *		ICONS_OPERATION_TIMEOUT
 *		ICONS_OPERATION_FAIL
 *		ICONS_DEV_ERROR
 *		ICONS_DEV_NOT_AVAILABLE
 *		ICONS_DEV_NOT_CONNECTED
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL TakePhotoWithAntiSpoofingEx (int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
		char *templateId, int *quality);
#else
typedef int (*pTakePhotoWithAntiSpoofingEx)(int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
		char *templateId, int *quality);
#endif

/*
 * GetDriverInfo - Get the driver identity information
 *
 * Parameter:
 *  driverInfo - buffer for storing driver identity information including
 *      Vendor name, Device model & Device driver version.
 *      The returned buffer should contains the concatenation of 3 strings,
 *      delimited and terminated by null character, arrange in the order:
 *      <Vendor name><null><Device model><null><Driver version><null>
 *	Total length of data returned should not be longer than 240 characters
 *      (including null characters)
 *
 * Return: always zero
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL GetDriverInfo(char *driverInfo);
#else
typedef int (*pGetDriverInfo)(char *driverInfo);
#endif

/*
 * SetLogLevel - Set the log level
 *
 * Parameter:
 *  logLevel - ICONS_LOG_ERROR, ICONS_LOG_WARNING, ICONS_LOG_INTERFACE,
 *            ICONS_LOG_INFORMATION, ICONS_LOG_TRACE, ICONS_LOG_MASKED_DATA,
 *            ICONS_LOG_DEBUG
 *  logPerformance - ICONS_TRUE = create performance log;
 *                   ICONS_FALSE = no performance log.
 *
 * Return: always zero
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL SetLogLevel(int logLevel, short logPerformance);
#else
typedef int (*pSetLogLevel)(int logLevel, short logPerformance);
#endif


/*
 * SetLogPrefix - Define a string prefix to be printed at the beginning of each
 *               logged line (help to identify logged message of the same tx).
 *
 * Parameter:
 *  logPrefix - the prefix string to be printed.  Empty string assumed, if null.
 *              (Override the previously set prefix)
 *
 * Return: always zero
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL SetLogPrefix(char *logPrefix);
#else
typedef int (*pSetLogPrefix)(char *logPrefix);
#endif


/*
 * SetLogPath - Define the path for the storing log file(s)
 *
 * Parameter:
 *  logPath - the full or relative path for storing the log file(s)
 *
 * Return:
 *	ICONS_NO_ERROR
 *	ICONS_FILE_OPENING_FAIL
 *	ICONS_FILE_WRITE_ERROR
 */
#ifndef __DEFINE_FUNC_PTR
int _EXPORT_CALL SetLogPath(char *logPath);
#else
typedef int (*pSetLogPath)(char *logPath);
#endif

#ifdef __cplusplus
}
#endif

#endif
