#ifndef _TASK2_H
#define _TASK2_H

#include "stdafx.h"
using namespace std;

double D(vector<double>point1, vector<double>point2);
int findMinDistance(vector<double> point1, vector<double>point2, vector<vector<double>> Centroids);
double Direction(vector<double> point1, vector<double>point2); // calculate the direction of an offstroke ( using corner)

void FeatureExtract(vector<vector<double>> offstroke, vector<vector<double>> &feature1, vector<vector<double>> &feature2, vector<double> &feature3, vector<double> &feature4);
vector<vector<double>> Average(vector<vector<double>> offstroke, vector<int>flag);

void FeatureExtract(vector<vector<double>>);
bool Check(vector<int>, vector<int>); // kiem tra su thay doi cua  cac clusters
vector<int> Kmeans(vector<vector<double>> offstroke,int &);

#endif