#ifndef _TASK2_H
#define _TASK2_H

#include "stdafx.h"
using namespace std;

double D(vector<int>point1, vector<double>point2);
double D(vector<double>point1, vector<double>point2);
int findMinDistance(vector<int> point1, vector<int>point2, vector<vector<double>> Centroids);
double Direction(vector<double> point1, vector<double>point2); // calculate the direction of an offstroke ( using corner)
void FeatureExtract(vector<vector<int>> offstroke, vector<vector<int>> &feature1, vector<vector<int>> &feature2, vector<double> &feature3, vector<double> &feature4);
vector<double> Average(vector<vector<int>> Store);

void FeatureExtract(vector<vector<int>>);

vector<vector<int>> Kmeans(vector<vector<int>> offstroke);

#endif