// ZGA.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "pch.h"

using namespace std;

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
