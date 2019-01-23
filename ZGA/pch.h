// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件





#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "iconsFrs.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include "MyTestClass.h"
#include "common.h"


#define SIZE 1024
#define MILLI 1000
#define IMGSIZE 1920*1080
#define CV_IMWRITE_JPEG_QUALITY 95
#define random(x) (rand()%x)

HMODULE const hModule = LoadLibraryA("frs.dll");;

#pragma   once 

pGetStatus	const						mGetStatus = pGetStatus(GetProcAddress(hModule, "GetStatus"));
pGetDriverStatus	const				mGetDriverStatus = pGetDriverStatus(GetProcAddress(hModule, "GetDriverStatus"));
pGetCamStatus	const					mGetCamStatus = pGetCamStatus(GetProcAddress(hModule, "GetCamStatus"));
pGetCamType	const						mGetCamType = pGetCamType(GetProcAddress(hModule, "GetCamType"));
pStartPhotoTaking	const				mStartPhotoTaking = pStartPhotoTaking(GetProcAddress(hModule, "StartPhotoTaking"));
pStopPhotoTaking	const				mStopPhotoTaking = pStopPhotoTaking(GetProcAddress(hModule, "StopPhotoTaking"));
pStopPhotoTakingEx	const				mStopPhotoTakingEx = pStopPhotoTakingEx(GetProcAddress(hModule, "StopPhotoTakingEx"));
pCompareFaces	const					mCompareFaces = pCompareFaces(GetProcAddress(hModule, "CompareFaces"));
pMatchFaces	const						mMatchFaces = pMatchFaces(GetProcAddress(hModule, "MatchFaces"));
pSetIndicatorLight	const				mSetIndicatorLight = pSetIndicatorLight(GetProcAddress(hModule, "SetIndicatorLight"));;
pDetectFace	const						mDetectFace = pDetectFace(GetProcAddress(hModule, "DetectFace"));;
pCheckLiveness	const					mCheckLiveness = pCheckLiveness(GetProcAddress(hModule, "CheckLiveness"));;
pCheckLivenessEx	const				mCheckLivenessEx = pCheckLivenessEx(GetProcAddress(hModule, "CheckLivenessEx"));;
pVerifyFace		const					mVerifyFace = pVerifyFace(GetProcAddress(hModule, "VerifyFace"));;
pVerifyFaces	const					mVerifyFaces = pVerifyFaces(GetProcAddress(hModule, "VerifyFaces"));;
pGenerateFaceImageAndTemplate	const	mGenerateFaceImageAndTemplate = pGenerateFaceImageAndTemplate(GetProcAddress(hModule, "GenerateFaceImageAndTemplate"));;
pGenerateFaceImageAndTemplateEx	const	mGenerateFaceImageAndTemplateEx = pGenerateFaceImageAndTemplateEx(GetProcAddress(hModule, "GenerateFaceImageAndTemplateEx"));;
pCropFace	const						mCropFace = pCropFace(GetProcAddress(hModule, "CropFace"));;
pGenerateFacialTemplate	const			mGenerateFacialTemplate = pGenerateFacialTemplate(GetProcAddress(hModule, "GenerateFacialTemplate"));;
pInitializeCamera	const				mInitializeCamera = pInitializeCamera(GetProcAddress(hModule, "InitializeCamera"));;
pDeinitializeCamera	const				mDeinitializeCamera = pDeinitializeCamera(GetProcAddress(hModule, "DeinitializeCamera"));;
pInterruptCompareFaces	const			mInterruptCompareFaces = pInterruptCompareFaces(GetProcAddress(hModule, "InterruptCompareFaces"));;
pInterruptMatchFaces	const			mInterruptMatchFaces = pInterruptMatchFaces(GetProcAddress(hModule, "InterruptMatchFaces"));;
pInterruptDetectFace	const			mInterruptDetectFace = pInterruptDetectFace(GetProcAddress(hModule, "InterruptDetectFace"));;
pCheckQueryFaceQuality	const			mCheckQueryFaceQuality = pCheckQueryFaceQuality(GetProcAddress(hModule, "CheckQueryFaceQuality"));;
pCheckQueryFaceQualityEx	const		mCheckQueryFaceQualityEx = pCheckQueryFaceQualityEx(GetProcAddress(hModule, "CheckQueryFaceQualityEx"));;
pTakePhoto	const						mTakePhoto = pTakePhoto(GetProcAddress(hModule, "TakePhoto"));;
pTakePhotoEx	const					mTakePhotoEx = pTakePhotoEx(GetProcAddress(hModule, "TakePhotoEx"));;
pTakePhotoWithAntiSpoofing	const		mTakePhotoWithAntiSpoofing = pTakePhotoWithAntiSpoofing(GetProcAddress(hModule, "TakePhotoWithAntiSpoofing"));;
pTakePhotoWithAntiSpoofingEx	const	mTakePhotoWithAntiSpoofingEx = pTakePhotoWithAntiSpoofingEx(GetProcAddress(hModule, "TakePhotoWithAntiSpoofingEx"));;
pGetDriverInfo	const					mGetDriverInfo = pGetDriverInfo(GetProcAddress(hModule, "GetDriverInfo"));;
pSetLogLevel	const					mSetLogLevel = pSetLogLevel(GetProcAddress(hModule, "SetLogLevel"));;
pSetLogPrefix	const					mSetLogPrefix = pSetLogPrefix(GetProcAddress(hModule, "SetLogPrefix"));;
pSetLogPath	const						mSetLogPath = pSetLogPath(GetProcAddress(hModule, "SetLogPath"));;

#endif //PCH_H
