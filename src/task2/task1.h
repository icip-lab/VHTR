#ifndef _TASK1_H
#define _TASK1_H

#include "stdafx.h"
using namespace std;

int Exp(int size);
vector<string> readNameFile(string filename);
vector<vector<double>> readfile(const char *filename, vector<vector<double>>&offstroke);
void SetWindowSize(size_t width, size_t height);
void sleepcp(int milliseconds);

#endif