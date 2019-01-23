#include "pch.h"

using namespace std;


void LogCout(const char *message, bool flag)
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

//通过照相功能返回iconsFace指针
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


//导入DLL，引入API函数
void LoadDll()
{
	//hModule = LoadLibraryA("frs.dll");
	if (hModule == NULL)
	{
		LogCout("Load dll Failed!", false);
		exit(0);
	}
	else
	{
		LogCout("Load dll Success!", true);
	}

	if ((mGetStatus != NULL) &&
		(mGetCamStatus != NULL) &&
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
