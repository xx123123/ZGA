// ZGA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "pch.h"
#include <iostream>
#include <thread>
#include <mutex>
#include "Windows.h"
#include "iconsFrs.h"
#include <opencv2/opencv.hpp>
#include <time.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#define SIZE 1024
#define MILLI 1000
#define IMGSIZE 1920*1080
#define CV_IMWRITE_JPEG_QUALITY 95
#define random(x) (rand()%x)


using namespace std;

typedef int(*pGetStatus)();;
typedef int(*pGetDriverStatus)();
typedef int(*pGetCamStatus)(int camNo);
typedef int(*pGetCamType)(int camNo);
typedef int(*pStartPhotoTaking)(int camName, int expirePeriod);
typedef int(*pStopPhotoTaking)(int camName, iconsFace *pImage,
	iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
typedef int(*pStopPhotoTakingEx)(int camName, iconsFace *pImage,
	iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality, iconsFace *pCroppedImage);
typedef int(*pCompareFaces)(int camName, iconsFace *facialList[],
	float matchThreshold, int qualityThreshold,
	int livenessThreshold, int timeoutPeriod, int maxRetries,
	int *headCount, iconsFace *imgCaptured,
	float *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
typedef int(*pMatchFaces)(int camName, iconsFace *facialList[],
	int matchThreshold, int qualityThreshold, int enableLivenesCheck,
	int livenessThreshold, int timeoutPeriod, int maxRetries,
	int *headCount, iconsFace *imgCaptured,
	int *matchScoreList, int *numMatchAttempt, char *referenceID, int *timeForRecognise);
typedef int(*pSetIndicatorLight) (int camName, int lightStatus, char *referenceID);
typedef int(*pDetectFace)(int camName, int interleavingPeriod, iconsFace *pImage);
typedef int(*pCheckLiveness)(int camName, int livenessThreshold,
	int timeoutPeriod);
typedef int(*pCheckLivenessEx)(int camName, int livenessThreshold,
	int timeoutPeriod);
typedef int(*pVerifyFace)(iconsFace *pImage1, iconsFace *pImage2,
	float *matchScore);
typedef int(*pVerifyFaces)(iconsFace *pImage1, iconsFace *pImage2,
	int *matchScore);
typedef int(*pGenerateFaceImageAndTemplate) (iconsFace *pImage,
	int minEyeDist, int maxEyeDist, int orientation[],
	iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
	POINT *leftEyePos, POINT *rightEyePos,
	RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
typedef int(*pGenerateFaceImageAndTemplateEx) (iconsFace *pImage,
	int minEyeDist, int maxEyeDist, int orientation[],
	iconsFace *pFace, iconsFace *pTemplate, char *templateId, int *quality,
	POINT *leftEyePos, POINT *rightEyePos,
	RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
typedef int(*pCropFace) (iconsFace *pImage,
	int minEyeDist, int maxEyeDist, iconsFace *pFace,
	POINT *leftEyePos, POINT *rightEyePos,
	RECT *faceRect, RECT *headRect, RECT *cropRect, int *faceOrientation);
typedef int(*pGenerateFacialTemplate)(iconsFace *pImage,
	POINT *leftEyePos, POINT *rightEyePos,
	iconsFace *pFace, iconsFace *pTemplate, char *templateId);
typedef int(*pInitializeCamera)(int camName, char *urlStreaming);
typedef int(*pDeinitializeCamera)(int camName);
typedef int(*pInterruptCompareFaces)(int camName);
typedef int(*pInterruptMatchFaces)(int camName);
typedef int(*pInterruptDetectFace)(int camName);
typedef int(*pCheckQueryFaceQuality)(iconsFace *pImage,
	int minEyeDist, int maxEyeDist, int *quality);
typedef int(*pCheckQueryFaceQualityEx)(iconsFace *pImage,
	int minEyeDist, int maxEyeDist, int *quality);
typedef int(*pTakePhoto)(int camName, iconsFace *pFace,
	iconsFace *pTemplate, char *templateId, int *quality);
typedef int(*pTakePhotoEx)(int camName, iconsFace *pFace,
	iconsFace *pTemplate, char *templateId, int *quality);
typedef int(*pTakePhotoWithAntiSpoofing)(int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
	char *templateId, int *quality);
typedef int(*pTakePhotoWithAntiSpoofingEx)(int camName, int livenessThreshold,
	int timeoutPeriod, iconsFace *pFace, iconsFace *pTemplate,
	char *templateId, int *quality);
typedef int(*pGetDriverInfo)(char *driverInfo);
typedef int(*pSetLogLevel)(int logLevel, short logPerformance);
typedef int(*pSetLogPrefix)(char *logPrefix);
typedef int(*pSetLogPath)(char *logPath);


HMODULE hModule = NULL;

pGetStatus						mGetStatus = NULL;
pGetDriverStatus				mGetDriverStatus = NULL;
pGetCamStatus					mGetCamStatus = NULL;
pGetCamType						mGetCamType = NULL;
pStartPhotoTaking				mStartPhotoTaking = NULL;
pStopPhotoTaking				mStopPhotoTaking = NULL;
pStopPhotoTakingEx				mStopPhotoTakingEx = NULL;
pCompareFaces					mCompareFaces = NULL;
pMatchFaces						mMatchFaces = NULL;
pSetIndicatorLight				mSetIndicatorLight = NULL;
pDetectFace						mDetectFace = NULL;
pCheckLiveness					mCheckLiveness = NULL;
pCheckLivenessEx				mCheckLivenessEx = NULL;
pVerifyFace						mVerifyFace = NULL;
pVerifyFaces					mVerifyFaces = NULL;
pGenerateFaceImageAndTemplate	mGenerateFaceImageAndTemplate = NULL;
pGenerateFaceImageAndTemplateEx	mGenerateFaceImageAndTemplateEx = NULL;
pCropFace						mCropFace = NULL;
pGenerateFacialTemplate			mGenerateFacialTemplate = NULL;
pInitializeCamera				mInitializeCamera = NULL;
pDeinitializeCamera				mDeinitializeCamera = NULL;
pInterruptCompareFaces			mInterruptCompareFaces = NULL;
pInterruptMatchFaces			mInterruptMatchFaces = NULL;
pInterruptDetectFace			mInterruptDetectFace = NULL;
pCheckQueryFaceQuality			mCheckQueryFaceQuality = NULL;
pCheckQueryFaceQualityEx		mCheckQueryFaceQualityEx = NULL;
pTakePhoto						mTakePhoto = NULL;
pTakePhotoEx					mTakePhotoEx = NULL;
pTakePhotoWithAntiSpoofing		mTakePhotoWithAntiSpoofing = NULL;
pTakePhotoWithAntiSpoofingEx	mTakePhotoWithAntiSpoofingEx = NULL;
pGetDriverInfo					mGetDriverInfo = NULL;
pSetLogLevel					mSetLogLevel = NULL;
pSetLogPrefix					mSetLogPrefix = NULL;
pSetLogPath						mSetLogPath = NULL;


void LogCout(const char *message, BOOL flag)
{
	if (flag)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	cout << "****	" << setw(64) << left << setfill(' ') << message << "****" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}


bool Mat2Uc(char* imgPath, unsigned char** pImage, long &size)
{
	cv::Mat InputImage = cv::imread(imgPath);
	if (InputImage.empty() || pImage == NULL) return false;
	vector<uchar> buff;
	vector<int> param = vector<int>(2);
	param[0] = CV_IMWRITE_JPEG_QUALITY;
	param[1] = 95;
	cv::imencode(".jpg", InputImage, buff, param);
	size = (long)buff.size() * sizeof(unsigned char);
	unsigned char* pBGR = new unsigned char[size];
	if (pBGR == NULL) return false;
	if (!buff.empty())
	{
		memcpy(pBGR, buff.data(), buff.size() * sizeof(unsigned char));
	}
	*pImage = pBGR;
	return true;
}


iconsFace *GenIconsFace(int camName, int isTemplate)
{
	//isTemplate = 1为模板
	int tmp = 1;
	iconsFace *pFace = NULL;
	iconsFace *pTemplate = NULL;
	
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	
	char templateId[SIZE * 10] = { 0 };
	int *quality = &tmp;
	int ret = 0;
	int loop = 0;
	bool flag = false;
	char message[64] = { 0 };
	while (loop < 100)
	{
		ret = mTakePhoto(camName, pFace, pTemplate, templateId, quality);
		sprintf(message, "TakePhoto code : %d ! loop: %d ! quality: %d !", ret, loop, *quality);
		LogCout(message, true);
		if (ret == ICONS_NO_ERROR)
		{
			flag = true;
			if (isTemplate == 1)
			{
				return pTemplate;
			}
			else
			{
				return pFace;
			}
		}
		memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(templateId, 0, SIZE * 10);
		Sleep(1000);
		loop += 1;
	}
	if (!flag)
	{
		LogCout("TakePhoto failed!", false);
		return NULL;
	}
	return NULL;
}


void InitDevice(int camName)
{
	int ret = 0;
	char *dataChars = NULL;
	dataChars = (char*)malloc(sizeof(char) * SIZE);
	memset(dataChars, 0, sizeof(char) * SIZE);

	ret = mGetDriverInfo(dataChars);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "GetDriverInfo Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		sprintf(message, "GetDriverInfo Success! DriverInfo: %s.", dataChars);
		LogCout(message, true);
		memset(message, 0, sizeof(message));
	}
	memset(dataChars, 0, sizeof(char) * SIZE);
	ret = 0;

	ret = mInitializeCamera(camName, dataChars);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "InitializeCamera Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		sprintf(message, "InitializeCamera Success! Stream: %s.", dataChars);
		LogCout(message, true);
		memset(message, 0, sizeof(message));
	}
	memset(dataChars, 0, sizeof(char) * SIZE);
	ret = 0;

	ret = mGetCamStatus(camName);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "GetCamStatus Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("GetCamStatus Success!", true);
	}
	ret = 0;

	ret = mGetDriverStatus();
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "GetDriverStatus Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("GetDriverStatus Success!", true);
	}
	ret = 0;

	ret = mGetStatus();
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "GetStatus Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("GetStatus Success!", true);
	}
	ret = 0;
}


void DeInitDevice(int camName)
{
	int ret = 0;
	ret = mDeinitializeCamera(camName);
	char message[64] = { 0 };

	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "DeinitializeCamera Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("DeinitializeCamera Success!", true);
	}
	ret = 0;
}


class MyTestClass
{
private:
	int camName = 0;
public:
	MyTestClass(int camName, char* logPrefix, int logLevel, short logPerformance, char *logPath);
	~MyTestClass();

public:
	void PECTest(int camName);
	void VECTest(int camName);
	void CNTTestNormal(int camName);
	void CNTTestMute(int camName);
	void CNTTestNoTake(int camName);
	void CNTTestTakeNoFace(int camName);
	void CNTTestImageNoFace(int camName);
	void CNTTestNoFace(int camName);
	void CNTTestNoInit(int camName);
	void CNTTestNoInitEx(int camName);
	void CNTTestNoDevice(int camName);
	void CNTTestNoDeviceEx(int camName);
	void CNTTestNoServer(int camName);
	void CNTTestNoServerEx(int camName);
	void CNTTestFaces(int camName);
	void CNTTestFacesEx(int camName);
	void CNTTestNoFaces(int camName);
	void CNTTestInDeLoop(int camName);
	void CNTTestStartStopLoop(int camName);
	void CNTTestProcedureLoop(int camName);
	void CNTTestServerWork(int camName);
	void CNTTestStartStopWork(int camName);
};


//构造函数
MyTestClass::MyTestClass(int camName, char* logPrefix, int logLevel, short logPerformance, char *logPath)
{

	LogCout("Class Init!", true);
	this->camName = camName;
	int ret = 0;
	ret = mSetLogLevel(logLevel, logPerformance);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "Set logLevel Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("Set logLevel Success!", true);
	}

	ret = mSetLogPrefix(logPrefix);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "Set logPrefix Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("Set logPrefix Success!", true);
	}

	ret = mSetLogPath(logPath);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "Set LogPath Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
		exit(0);
	}
	else
	{
		LogCout("Set LogPath Success!", true);
	}
	
}


//析构函数
MyTestClass::~MyTestClass()
{

}


//人道测试成员函数
void MyTestClass::PECTest(int camName)
{
	InitDevice(camName);
	int ret = 0;
	//exit(0);
	int orientation[] = { 1 };
	iconsFace *pFace = NULL;
	iconsFace *pTemplate = NULL;
	char templateId[64] = { 0 };
	int *quality = NULL;
	POINT *leftEyePos = NULL;
	POINT *rightEyePos = NULL;
	RECT *faceRect = NULL;
	RECT *headRect = NULL;
	RECT *cropRect = NULL;
	int *faceOrientation = NULL;
	ret = mGenerateFaceImageAndTemplateEx(GenIconsFace(camName, 0), 10, 20, orientation,
		pFace, pTemplate, templateId, quality, leftEyePos, rightEyePos,
		faceRect, headRect, cropRect, faceOrientation);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "GenerateFaceImageAndTemplateEx Failed! Error code: " << ret << " !" << endl;
		exit(0);
	}
	else
	{
		cout << "GenerateFaceImageAndTemplateEx Success!" << endl;
	}
	ret = 0;
	pFace = NULL;
	pTemplate = NULL;
	quality = NULL;
	leftEyePos = NULL;
	rightEyePos = NULL;
	faceRect = NULL;
	headRect = NULL;
	cropRect = NULL;
	faceOrientation = NULL;

	iconsFace* facialList[] = { GenIconsFace(camName, 0) };
	int matchThreshold = 80;
	int qualityThreshold = 80;
	int enableLivenessCheck = 0;
	int livenessThreshold = 0;
	int timeoutPeriod = 30;
	int maxRetries = 10;
	int *headCount = NULL;
	iconsFace *imgCaptured = NULL;
	int *matchScoreList = NULL;
	int *numMatchAttempt = NULL;
	char *referenceID = NULL;
	int *timeForRecognise = NULL;
	ret = mMatchFaces(camName, facialList, matchThreshold, qualityThreshold, enableLivenessCheck, livenessThreshold, timeoutPeriod, maxRetries,
		headCount, imgCaptured, matchScoreList, numMatchAttempt, referenceID, timeForRecognise);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "MatchFaces Failed! Error code: " << ret << " !" << endl;
		exit(0);
	}
	else
	{
		cout << "MatchFaces Success!" << endl;
	}
	ret = 0;
	headCount = NULL;
	imgCaptured = NULL;
	matchScoreList = NULL;
	numMatchAttempt = NULL;
	referenceID = NULL;
	timeForRecognise = NULL;

	DeInitDevice(camName);
}


//车道测试成员函数
void MyTestClass::VECTest(int camName)
{
	int ret = 0;
}


//柜台测试成员函数，正常流程
void MyTestClass::CNTTestNormal(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	
	char message[64] = { 0 };

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	//抓拍比对
	ret = mStartPhotoTaking(camName, 1000);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	
	ret = mStopPhotoTakingEx(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTakingEx Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTakingEx Success!", true);
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT Normal Success!!!", true);
}


//柜台测试成员函数，多次比对未通过，
void MyTestClass::CNTTestMute(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"222.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	for (int i = 0; i < random(10); i++)
	{
		ret = mStartPhotoTaking(camName, 100);
		if (ret != ICONS_NO_ERROR)
		{
			cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
			//exit(0);
		}
		else
		{
			cout << "StartPhotoTaking Success!" << endl;
		}
		ret = 0;

		ret = mStopPhotoTaking(camName, pImage, 
			pFace, pTemplate, templateId, quality, pCroppedImage);
		if (ret != ICONS_NO_ERROR)
		{
			cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
			//exit(0);
		}
		else
		{
			cout << "StopPhotoTakingEx Success!" << endl;
		}
		ret = 0;
	}

	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	//抓拍比对
	ret = mStartPhotoTaking(camName, 1000);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;


	ret = mStopPhotoTakingEx(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);
	
	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT Mute Success!!!" << endl;
}


//柜台测试成员函数，未抓拍，直接比对
void MyTestClass::CNTTestNoTake(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT NoTake Success!!!" << endl;
}


//柜台测试成员函数，抓拍无人脸
void MyTestClass::CNTTestTakeNoFace(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	Sleep(random(20) * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT TakeNoFace Success!!!" << endl;
}


//柜台测试成员函数，图片无人脸
void MyTestClass::CNTTestImageNoFace(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"333.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	Sleep(random(20) * MILLI);
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT ImageNoFace Success!!!" << endl;
}


//柜台测试成员函数，无人脸
void MyTestClass::CNTTestNoFace(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"333.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	Sleep(random(20) * MILLI);
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT NoFace Success!!!" << endl;
}


//柜台测试成员函数，未初始化
void MyTestClass::CNTTestNoInit(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	mDeinitializeCamera(camName);
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	Sleep(random(20) * MILLI);

	InitDevice(camName);
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT NoInit Success!!!" << endl;
}


//柜台测试成员函数，抓拍后释放设备
void MyTestClass::CNTTestNoInitEx(int camName)
{
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	srand(int(time(0)));
	Sleep(random(20) * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}
	ret = 0;

	Sleep(random(20) * MILLI);

	InitDevice(camName);
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StartPhotoTaking Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StartPhotoTaking Success!" << endl;
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		cout << "StopPhotoTakingEx Failed! Error code: " << ret << " !" << endl;
		//exit(0);
	}
	else
	{
		cout << "StopPhotoTakingEx Success!" << endl;
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	cout << "Test CNT NoInitEx Success!!!" << endl;
}


//柜台测试成员函数，未连接设备抓拍
void MyTestClass::CNTTestNoDevice(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	LogCout("Please disconnect device!", true);
	Sleep(10 * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	//比对
	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;
	memset(pImage, 0, sizeof(iconsFace) + 10);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	free(pImage->image);


	LogCout("Please connect device!", true);
	Sleep(10 * MILLI);

	//抓拍
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	//比对
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;
	
	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT NoDevice Success!!!", true);
}


//柜台测试成员函数，抓拍后断开设备
void MyTestClass::CNTTestNoDeviceEx(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	LogCout("Please disconnect device!", true);
	Sleep(10 * MILLI);

	//比对
	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;
	memset(pImage, 0, sizeof(iconsFace) + 10);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	free(pImage->image);


	LogCout("Please connect device!", true);
	Sleep(10 * MILLI);

	//抓拍
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	//比对
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT NoDeviceEx Success!!!", true);
}


//柜台测试成员函数，无服务
void MyTestClass::CNTTestNoServer(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	system("TASKKILL /F /IM server.exe");
	Sleep(5 * MILLI);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTaking Success!", true);
	}
	ret = 0;
	memset(pImage, 0, sizeof(iconsFace) + 10);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	free(pImage->image);

	WinExec("C:\\ICONS\\devices\\frs1\\server\\server.exe", SW_SHOWMAXIMIZED);
	Sleep(5 * MILLI);
	InitDevice(camName);
	//抓拍
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;
	//比对
	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT NoServer Success!!!", true);
}


//柜台测试成员函数，抓拍后断开服务
void MyTestClass::CNTTestNoServerEx(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	system("TASKKILL /F /IM server.exe");
	Sleep(3 * MILLI);

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTaking Success!", true);
	}
	ret = 0;
	memset(pImage, 0, sizeof(iconsFace) + 10);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	Sleep(3 * MILLI);

	WinExec("C:\\ICONS\\devices\\frs1\\server\\server.exe", SW_SHOWMAXIMIZED);
	Sleep(5 * MILLI);
	InitDevice(camName);
	//抓拍
	ret = mStartPhotoTaking(camName, 100);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	//比对
	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT NoServer Success!!!", true);
}


//柜台测试成员函数，抓拍多张人脸图片，被比对人脸图像最大
void MyTestClass::CNTTestFaces(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTaking Success!", true);
	}
	ret = 0;

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT Faces Success!!!", true);
}


//柜台测试成员函数，抓拍多张人脸图片，被比对人脸图像不是最大
void MyTestClass::CNTTestFacesEx(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTaking Success!", true);
	}
	ret = 0;

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT FacesEx Success!!!", true);
}


//柜台测试成员函数，抓拍多张人脸图片，被比对人不在其中
void MyTestClass::CNTTestNoFaces(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	Mat2Uc((char*)"111.jpg", &pImage->image, size);
	pImage->isTemplate = 0;
	pImage->size = size;

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	ret = mStartPhotoTaking(camName, 100);
	char message[64] = { 0 };
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StartPhotoTaking Success!", true);
	}
	ret = 0;

	ret = mStopPhotoTaking(camName, pImage,
		pFace, pTemplate, templateId, quality, pCroppedImage);
	if (ret != ICONS_NO_ERROR)
	{
		sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
		LogCout(message, false);
		memset(message, 0, sizeof(message));
	}
	else
	{
		LogCout("StopPhotoTaking Success!", true);
	}
	ret = 0;

	DeInitDevice(camName);

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);
	LogCout("Test CNT NoFaces Success!!!", true);
}


//柜台测试成员函数，循环获取、释放设备
void MyTestClass::CNTTestInDeLoop(int camName)
{
	int loop = 0;
	loop = GetPrivateProfileInt("CASES", "loop", 0, "./Config.ini");
	for (int i = 0; i < loop; i++)
	{
		InitDevice(camName);
		LogCout("Sleep!", true);
		Sleep(random(10) * MILLI);
		DeInitDevice(camName);
	}
	LogCout("Test CNT InDeLoop Success!!!", true);
}


//柜台测试成员函数，循环抓拍、比对
void MyTestClass::CNTTestStartStopLoop(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;
	

	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char message[64] = { 0 };

	int loop = 0;
	loop = GetPrivateProfileInt("CASES", "loop", 0, "./Config.ini");
	for (int i = 0; i < loop; i++)
	{
		Mat2Uc((char*)"111.jpg", &pImage->image, size);
		pImage->isTemplate = 0;
		pImage->size = size;

		ret = mStartPhotoTaking(camName, 100);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StartPhotoTaking Success!", true);
		}

		Sleep(random(10) * MILLI);

		ret = mStopPhotoTaking(camName, pImage,
			pFace, pTemplate, templateId, quality, pCroppedImage);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StopPhotoTaking Success!", true);
		}
		ret = 0;
		memset(pImage, 0, sizeof(iconsFace) + 10);
		memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		free(pImage->image);
	}
	
	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);

	DeInitDevice(camName);
	LogCout("Test CNT StartStopLoop Success!!!", true);
}


//柜台测试成员函数，循环流程
void MyTestClass::CNTTestProcedureLoop(int camName)
{
	//初始化设备
	
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;


	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char message[64] = { 0 };

	int loop = 0;
	loop = GetPrivateProfileInt("CASES", "loop", 0, "./Config.ini");
	for (int i = 0; i < loop; i++)
	{
		Mat2Uc((char*)"111.jpg", &pImage->image, size);
		pImage->isTemplate = 0;
		pImage->size = size;

		InitDevice(camName);

		ret = mStartPhotoTaking(camName, 100);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StartPhotoTaking Success!", true);
		}

		Sleep(random(10) * MILLI);

		ret = mStopPhotoTaking(camName, pImage,
			pFace, pTemplate, templateId, quality, pCroppedImage);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StopPhotoTaking Success!", true);
		}
		ret = 0;
		memset(pImage, 0, sizeof(iconsFace) + 10);
		memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		free(pImage->image);

		DeInitDevice(camName);
	}

	free(pImage);
	free(pFace);
	free(pTemplate);
	free(pCroppedImage);

	
	LogCout("Test CNT StartStopLoop Success!!!", true);
}


//柜台测试成员函数，持续运行服务
void MyTestClass::CNTTestServerWork(int camName)
{
	srand(int(time(0)));
	int hours = GetPrivateProfileInt("CASES", "hours", 0, "./Config.ini");
	time_t startTime, localTime;
	startTime = time(&startTime);
	int tmp = (int)startTime;
	do {
		Sleep(random(10) * MILLI);
		localTime = time(&localTime);
		if (localTime - tmp > 60)
		{
			InitDevice(camName);
			tmp += 60;
		}

	} while (localTime - startTime < hours * 60 * 60);
	DeInitDevice(camName);
}


//柜台测试成员函数，流程持续工作
void MyTestClass::CNTTestStartStopWork(int camName)
{
	//初始化设备
	InitDevice(camName);
	int ret = 0;

	//初始化图片、图片数据、模板、模板ID、裁剪图片变量，并分配空间
	iconsFace *pImage = NULL;
	pImage = (iconsFace*)malloc(sizeof(iconsFace) + 10);
	memset(pImage, 0, sizeof(iconsFace) + 10);
	long size = 0;


	iconsFace *pFace = NULL;
	pFace = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	iconsFace *pTemplate = NULL;
	pTemplate = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char templateId[SIZE * 10] = { 0 };
	int tmp = 1;
	int *quality = &tmp;
	iconsFace *pCroppedImage = NULL;
	pCroppedImage = (iconsFace*)malloc(sizeof(iconsFace) + 10 + IMGSIZE);
	memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);

	char message[64] = { 0 };

	srand(int(time(0)));
	int hours = GetPrivateProfileInt("CASES", "hours", 0, "./Config.ini");
	time_t startTime, localTime;
	startTime = time(&startTime);
	tmp = (int)startTime;
	do {
		Mat2Uc((char*)"111.jpg", &pImage->image, size);
		pImage->isTemplate = 0;
		pImage->size = size;

		ret = mStartPhotoTaking(camName, 100);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StartPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StartPhotoTaking Success!", true);
		}

		Sleep(random(10) * MILLI);

		ret = mStopPhotoTaking(camName, pImage,
			pFace, pTemplate, templateId, quality, pCroppedImage);
		if (ret != ICONS_NO_ERROR)
		{
			sprintf(message, "StopPhotoTaking Failed! Error code: %d !", ret);
			LogCout(message, false);
			memset(message, 0, sizeof(message));
		}
		else
		{
			LogCout("StopPhotoTaking Success!", true);
		}
		ret = 0;
		memset(pImage, 0, sizeof(iconsFace) + 10);
		memset(pFace, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pTemplate, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		memset(pCroppedImage, 0, sizeof(iconsFace) + 10 + IMGSIZE);
		free(pImage->image);

		Sleep(random(60) * MILLI);

		localTime = time(&localTime);
	} while (localTime - startTime < hours * 60 * 60);
	DeInitDevice(camName);
}


//导入DLL，引入API函数
void LoadDll()
{
	hModule = LoadLibraryA("frs.dll");
	if (hModule == NULL)
	{
		LogCout("Load dll Failed!", false);
		exit(0);
	}
	else
	{
		LogCout("Load dll Success!", true);
	}

	mGetStatus						= pGetStatus(GetProcAddress(hModule, "GetStatus"));
	mGetDriverStatus				= pGetDriverStatus(GetProcAddress(hModule, "GetDriverStatus"));
	mGetCamStatus					= pGetCamStatus(GetProcAddress(hModule, "GetCamStatus"));
	mGetCamType						= pGetCamType(GetProcAddress(hModule, "GetCamType"));
	mStartPhotoTaking				= pStartPhotoTaking(GetProcAddress(hModule, "StartPhotoTaking"));
	mStopPhotoTaking				= pStopPhotoTaking(GetProcAddress(hModule, "StopPhotoTaking"));
	mStopPhotoTakingEx				= pStopPhotoTakingEx(GetProcAddress(hModule, "StopPhotoTakingEx"));
	mCompareFaces					= pCompareFaces(GetProcAddress(hModule, "CompareFaces"));
	mMatchFaces						= pMatchFaces(GetProcAddress(hModule, "MatchFaces"));
	mSetIndicatorLight				= pSetIndicatorLight(GetProcAddress(hModule, "SetIndicatorLight"));
	mDetectFace						= pDetectFace(GetProcAddress(hModule, "DetectFace"));
	mCheckLiveness					= pCheckLiveness(GetProcAddress(hModule, "CheckLiveness"));
	mCheckLivenessEx				= pCheckLivenessEx(GetProcAddress(hModule, "CheckLivenessEx"));
	mVerifyFace						= pVerifyFace(GetProcAddress(hModule, "VerifyFace"));
	mVerifyFaces					= pVerifyFaces(GetProcAddress(hModule, "VerifyFaces"));
	mGenerateFaceImageAndTemplate	= pGenerateFaceImageAndTemplate(GetProcAddress(hModule, "GenerateFaceImageAndTemplate"));
	mGenerateFaceImageAndTemplateEx = pGenerateFaceImageAndTemplateEx(GetProcAddress(hModule, "GenerateFaceImageAndTemplateEx"));
	mCropFace						= pCropFace(GetProcAddress(hModule, "CropFace"));
	mGenerateFacialTemplate			= pGenerateFacialTemplate(GetProcAddress(hModule, "GenerateFacialTemplate"));
	mInitializeCamera				= pInitializeCamera(GetProcAddress(hModule, "InitializeCamera"));
	mDeinitializeCamera				= pDeinitializeCamera(GetProcAddress(hModule, "DeinitializeCamera"));
	mInterruptCompareFaces			= pInterruptCompareFaces(GetProcAddress(hModule, "InterruptCompareFaces"));
	mInterruptMatchFaces			= pInterruptMatchFaces(GetProcAddress(hModule, "InterruptMatchFaces"));
	mInterruptDetectFace			= pInterruptDetectFace(GetProcAddress(hModule, "InterruptDetectFace"));
	mCheckQueryFaceQuality			= pCheckQueryFaceQuality(GetProcAddress(hModule, "CheckQueryFaceQuality"));
	mCheckQueryFaceQualityEx		= pCheckQueryFaceQualityEx(GetProcAddress(hModule, "CheckQueryFaceQualityEx"));
	mTakePhoto						= pTakePhoto(GetProcAddress(hModule, "TakePhoto"));
	mTakePhotoEx					= pTakePhotoEx(GetProcAddress(hModule, "TakePhotoEx"));
	mTakePhotoWithAntiSpoofing		= pTakePhotoWithAntiSpoofing(GetProcAddress(hModule, "TakePhotoWithAntiSpoofing"));
	mTakePhotoWithAntiSpoofingEx	= pTakePhotoWithAntiSpoofingEx(GetProcAddress(hModule, "TakePhotoWithAntiSpoofingEx"));
	mGetDriverInfo					= pGetDriverInfo(GetProcAddress(hModule, "GetDriverInfo"));
	mSetLogLevel					= pSetLogLevel(GetProcAddress(hModule, "SetLogLevel"));
	mSetLogPrefix					= pSetLogPrefix(GetProcAddress(hModule, "SetLogPrefix"));
	mSetLogPath						= pSetLogPath(GetProcAddress(hModule, "SetLogPath"));

	if ((mGetCamStatus != NULL) &&
		(mGetDriverStatus != NULL) &&
		(mGetCamType != NULL) &&
		(mStartPhotoTaking != NULL) &&
		(mStopPhotoTaking != NULL) &&
		(mStopPhotoTakingEx != NULL) &&
		(mCompareFaces != NULL) &&
		(mMatchFaces != NULL) &&
		(mSetIndicatorLight != NULL) &&
		(mDetectFace != NULL) &&
		(mCheckLiveness != NULL) &&
		(mCheckLivenessEx != NULL) &&
		(mVerifyFace != NULL) &&
		(mVerifyFaces != NULL) &&
		(mGenerateFaceImageAndTemplate != NULL) &&
		(mGenerateFaceImageAndTemplateEx != NULL) &&
		(mCropFace != NULL) &&
		(mGenerateFacialTemplate != NULL) &&
		(mInitializeCamera != NULL) &&
		(mDeinitializeCamera != NULL) &&
		(mInterruptCompareFaces != NULL) &&
		(mInterruptMatchFaces != NULL) &&
		(mInterruptDetectFace != NULL) &&
		(mCheckQueryFaceQuality != NULL) &&
		(mCheckQueryFaceQualityEx != NULL) &&
		(mTakePhoto != NULL) &&
		(mTakePhotoEx != NULL) &&
		(mTakePhotoWithAntiSpoofing != NULL) &&
		(mTakePhotoWithAntiSpoofingEx != NULL) &&
		(mGetDriverInfo != NULL) &&
		(mSetLogLevel != NULL) &&
		(mSetLogPrefix != NULL) &&
		(mSetLogPath != NULL))
	{
		LogCout("GetProcAddress Success!", true);
	}
	else
	{
		LogCout("GetProcAddress Failed!", false);
		exit(0);
	}
}


int main()
{
	LogCout("start server!", true);
	if (_access(".//server//server.exe", 0) != -1)
	{
		WinExec("C:\\ICONS\\devices\\frs1\\server\\server.exe", SW_SHOWMAXIMIZED);
	}
	else
	{
		cout << "server.exe not exits!" << endl;
		exit(0);
	}
	Sleep(5 * MILLI);

	unsigned char *image = NULL;
	image = (unsigned char*)malloc(IMGSIZE + 10);
	memset(image, 0, IMGSIZE + 10);
	long size = 1;
	Mat2Uc((char*)"111.jpg", &image, size);
	LoadDll();
	
	int camName = 0; //2：PEC、5：CNT、6：VEC、11：supervisor、8：emrollment
	
	camName = GetPrivateProfileInt("DEVICE", "camName", 0, "./Config.ini");
	
	LPSTR strPro = NULL;
	strPro = (LPSTR)malloc(64);
	memset(strPro, 0, 64);
	LPSTR strPath = NULL;
	strPath = (LPSTR)malloc(64);
	memset(strPath, 0, 64);
	LPSTR testCases = NULL;
	testCases = (LPSTR)malloc(1024);
	memset(testCases, 0, 1024);
	GetPrivateProfileString("DEVICE", "strPro", "No data", strPro, 64, "./Config.ini");
	GetPrivateProfileString("DEVICE", "strPath", "No data", strPath, 64, "./Config.ini");
	GetPrivateProfileString("CASES", "cases", "No data", testCases, 1024, "./Config.ini");

	MyTestClass my_test(camName, strPro, ICONS_LOG_INFORMATION, ICONS_TRUE, strPath);

	//cout << "testCases--->" << testCases << endl;
	const char *delim = ",";
	char *caseExcute;
	caseExcute = strtok(testCases, delim);
	int countExcute = 0;
	countExcute = countExcute = GetPrivateProfileInt("CASES", "count", 0, "./Config.ini");
	while (caseExcute)
	{
		if (strcmp(caseExcute, "CNTTestNormal") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNormal(camName);
			}
			
		}
		if (strcmp(caseExcute, "CNTTestMute") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestMute(camName);
			}

		}
		if (strcmp(caseExcute, "CNTTestNoTake") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoTake(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestTakeNoFace") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestTakeNoFace(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestImageNoFace") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestImageNoFace(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoFace") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoFace(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoInit") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoInit(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoInitEx") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoInitEx(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoDevice") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoDevice(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoDeviceEx") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoDeviceEx(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoServer") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoServer(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoServerEx") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoServerEx(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestFaces") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestFaces(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestFacesEx") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestFaces(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestNoFaces") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestNoFaces(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestInDeLoop") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestInDeLoop(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestStartStopLoop") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestStartStopLoop(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestProcedureLoop") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestProcedureLoop(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestServerWork") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestServerWork(camName);
			}
		}
		if (strcmp(caseExcute, "CNTTestStartStopWork") == 0)
		{
			for (int i = 0; i < countExcute; i++)
			{
				my_test.CNTTestStartStopWork(camName);
			}
		}
		
		caseExcute = strtok(NULL, delim);
	}
	
	
	free(strPro);
	free(strPath);
	free(testCases);
	system("TASKKILL /F /IM server.exe");
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
