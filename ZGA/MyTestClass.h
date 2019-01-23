#pragma once
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