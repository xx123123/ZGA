#pragma once

void LogCout(const char *message, bool flag);
bool Mat2Uc(char* imgPath, unsigned char** pImage, long &size);
iconsFace *GenIconsFace(int camName, int isTemplate);
void InitDevice(int camName);
void DeInitDevice(int camName);
void LoadDll();
