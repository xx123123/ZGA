#include "pch.h"

using namespace std;
//���캯��
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


//��������
MyTestClass::~MyTestClass()
{

}


//�˵����Գ�Ա����
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


//�������Գ�Ա����
void MyTestClass::VECTest(int camName)
{
	int ret = 0;
}


//��̨���Գ�Ա��������������
void MyTestClass::CNTTestNormal(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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

	//ץ�ıȶ�
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


//��̨���Գ�Ա��������αȶ�δͨ����
void MyTestClass::CNTTestMute(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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

	//ץ�ıȶ�
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


//��̨���Գ�Ա������δץ�ģ�ֱ�ӱȶ�
void MyTestClass::CNTTestNoTake(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ץ��������
void MyTestClass::CNTTestTakeNoFace(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ͼƬ������
void MyTestClass::CNTTestImageNoFace(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������������
void MyTestClass::CNTTestNoFace(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������δ��ʼ��
void MyTestClass::CNTTestNoInit(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ץ�ĺ��ͷ��豸
void MyTestClass::CNTTestNoInitEx(int camName)
{
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������δ�����豸ץ��
void MyTestClass::CNTTestNoDevice(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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

	//�ȶ�
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

	//ץ��
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

	//�ȶ�
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


//��̨���Գ�Ա������ץ�ĺ�Ͽ��豸
void MyTestClass::CNTTestNoDeviceEx(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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

	//�ȶ�
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

	//ץ��
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

	//�ȶ�
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


//��̨���Գ�Ա�������޷���
void MyTestClass::CNTTestNoServer(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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
	//ץ��
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
	//�ȶ�
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


//��̨���Գ�Ա������ץ�ĺ�Ͽ�����
void MyTestClass::CNTTestNoServerEx(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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
	//ץ��
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
	//�ȶ�
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


//��̨���Գ�Ա������ץ�Ķ�������ͼƬ�����ȶ�����ͼ�����
void MyTestClass::CNTTestFaces(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ץ�Ķ�������ͼƬ�����ȶ�����ͼ�������
void MyTestClass::CNTTestFacesEx(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ץ�Ķ�������ͼƬ�����ȶ��˲�������
void MyTestClass::CNTTestNoFaces(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ѭ����ȡ���ͷ��豸
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


//��̨���Գ�Ա������ѭ��ץ�ġ��ȶ�
void MyTestClass::CNTTestStartStopLoop(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա������ѭ������
void MyTestClass::CNTTestProcedureLoop(int camName)
{
	//��ʼ���豸

	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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


//��̨���Գ�Ա�������������з���
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


//��̨���Գ�Ա���������̳�������
void MyTestClass::CNTTestStartStopWork(int camName)
{
	//��ʼ���豸
	InitDevice(camName);
	int ret = 0;

	//��ʼ��ͼƬ��ͼƬ���ݡ�ģ�塢ģ��ID���ü�ͼƬ������������ռ�
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