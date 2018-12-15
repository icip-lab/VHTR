#include "task2.h"
#include "cmath"
using namespace std;

// vector<int> point1 : a pair of coordernate x,y of point1

//phia duoi em goi ham D (tinh khoang cach giua 2 diem ) theo nhieu kieu du lieu nen em tao toi 3 ham D 

double D(vector<double>point1, vector<double>point2) {
	double x = (point1.front() - point2.front())*(point1.front() - point2.front());
	double y = (point1.back() - point2.back())*(point1.back() - point2.back());
	return sqrt((double)(x + y));
}
// ham Direction la cai feature thu 4 , tim huong cua cai offstroke dang xet
double Direction(vector<double> point1, vector<double>point2) // calculate the direction of an offstroke ( using corner)
{
	double degree_cos; // tinh goc cua offstroke
	// xet quan he giua 2 cai Oy , neu Oy1 < Oy2 thi goc phai nho hon 90 do, nguoc lai >= 90
	if (point1.back() < point2.back())
	{

		double d = D(point1, point2);
		double pytago = sqrt((double)d*d - (double)(point2.back() - point1.back())*(point2.back() - point1.back()));
		degree_cos = acos((double)pytago / d);
	}
	else
	{

		double d = D(point1, point2);
		double pytago = sqrt((double)d*d - (double)(point1.back() - point2.back())*(point1.back() - point2.back()));
		degree_cos = acos((double)pytago / d);
		degree_cos = degree_cos + 90;
	}
	return degree_cos*3.1415 / 180; // chuyen tu do sang radian
}

// point1 & point2 are two pairs of coordernate of an offstroke( first coor & last coor)
// ham nay dung de tim noi chua cua cai offstroke dang xet trong 5 bo Centroid ( chua trong vector<vector> Centroids)
// em da danh so thu tu cho 5 set va ham nay se tra ve vi tri Centroid chua cai offstroke dang xet 
int findMinDistance(vector<double> point1,vector<double>point2,vector<vector<double>> Centroids)
{
	vector<double>temp;
	// gan trung binh cua nhom dau tien
	temp = Centroids[0];
	// 2 vector nay luu tru toa do cua 2 diem cua offstroke
	vector<double>temp1, temp2;

	// temp1 la diem dau(khi nhac but len) cua offstroke
	temp1.push_back(temp[0]);
	temp1.push_back(temp[1]);
	// do lech giua point1 va temp1
	double d1 = D(point1, temp1);
	// temp2 la diem cuoi(khi dat but xuong) cua offstroke
	temp2.push_back(temp[2]);
	temp2.push_back(temp[3]);
	// do lech giua point2 va temp2
	double d2 = D(point2, temp2);
	// do lech cua huong
	double error_dir = Direction(point1, point2) - temp[5];
	// tinh tong do lech cua offstroke dang xet so voi trung binh cua nhom dau tien
	double min = d1*d1 + d2*d2 + (D(temp1, temp2) - temp[4])*(D(temp1, temp2) - temp[4])+ error_dir*error_dir;
	int pos = 0;
	temp.clear();
	temp1.clear();
	temp2.clear();
	// tinh tong do lech cua offstroke dang xet voi cac nhom tiep theo
	for (int i = 1; i < 5; i++) {
		temp = Centroids[i];
		temp1.push_back(temp[0]);
		temp1.push_back(temp[1]);
		d1 = D(point1, temp1);
		temp2.push_back(temp[2]);
		temp2.push_back(temp[3]);
		d2 = D(point2, temp2);
		error_dir = (double)Direction(point1, point2) - temp[5];
		double distance = d1*d1 + d2*d2 + (D(temp1, temp2) - temp[4])*(D(temp1, temp2) - temp[4]) + error_dir*error_dir;
		//neu ra do lech nho hon thi cap nhat lai min va pos
		if (min > distance) {
			min = distance;
			
			pos = i;
		}
		temp.clear();
		temp1.clear();
		temp2.clear();
	}
	
	return pos;
}


//ham FeatureExtract: vector<vector> offstroke chua thong tin toa do cua cac offstroke ,
// o day em luu vao vector<vector> offstroke theo kieu cu 2 phan tu ke tiep nhau la toa do dau( khi nhac but len) va toa
//  do cuoi( khi dat but xuong) cua 1 offstroke
// muc dich cua ham FeatureExtract la dua vao vector<vector>offstroke em se tao ra duoc 4 cai dac trung nhu o phia duoi
void FeatureExtract(vector<vector<double>> offstroke, vector<vector<double>> &feature1, vector<vector<double>> &feature2, vector<double> &feature3, vector<double> &feature4)
{
	vector<double> temp;

	for (int i = 0; i < offstroke.size(); i=i+2)
	{
		// save begining coorderenate
		temp.push_back(offstroke[i].front());
		temp.push_back(offstroke[i].back());
		feature1.push_back(temp);
		// save second coordernate of an offstroke
		temp.push_back(offstroke[i + 1].front());
		temp.push_back(offstroke[i + 1].back());
		feature2.push_back(temp);
		// save length of an offstroke
		double can = sqrt((double)pow(offstroke[i].front() - offstroke[i + 1].front(), 2) + (double)pow(offstroke[i].back() - offstroke[i + 1].back(), 2));
		feature3.push_back(can);
		double corner = Direction(offstroke[i], offstroke[i + 1]);
		// dac trung thu 4 ( huong )
		feature4.push_back(corner);
	}

}

// calculate average of centroid
// ham nay tinh trung binh cua mot bo du lieu ( 1 cai Centroid)
// mac du minh chi co 4 dac trung nhung do dac trung 1 va 2 luu tru 1 cap Ox Oy 
// nen khi tinh trun binh em lai tinh den 6 gia tri, vi em tinh trung binh cua Ox rieng va trung binh cua Oy rieng luon
// ca 2 dac trung 1 va 2 em deu lam nhu vay

vector<vector<double>> Average(vector<vector<double>> offstroke, vector<int>flag)
{
	vector<vector<double>> result;// luu vector trung binh cua tung nhom 
	// dem so luong phan tu cua tung nhom
	int *Count = new int[5];
	//d: khoang cach giua 2 diem cua offstroke
	//dir: huong cua offstroke
	double d, dir;
	//vector co 6 phan tu bang khong de khoi tao gia tri ban dau
	vector<double>temp;
		for (int j = 0; j < 6; j++) {
			temp.push_back(0);
		}
	//khoi tao gia tri ban dau bang khong cho result va Count
	for (int i = 0; i < 5; i++) {
		result.push_back(temp);
		Count[i] = 0;
	}
	temp.clear();
	//tinh tong tung dac trung theo tung nhom cua no
	for (int i = 0; i<flag.size(); i=i+2) {
		Count[flag[i]] = Count[flag[i]] + 1;
		result[flag[i]][0] = result[flag[i]][0] + offstroke[i].front();
		result[flag[i]][1] = result[flag[i]][1] + offstroke[i].back();
		result[flag[i]][2] = result[flag[i]][2] + offstroke[i+1].front();
		result[flag[i]][3] = result[flag[i]][3] + offstroke[i+1].back();
		d = sqrt((double)pow(offstroke[i].front() - offstroke[i+1].front(), 2) + (double)pow(offstroke[i].back() - offstroke[i+1].back(), 2));
		result[flag[i]][4] = result[flag[i]][4]+ d;
		dir = Direction(offstroke[i], offstroke[i + 1]);
		result[flag[i]][5] = result[flag[i]][5] + dir;

	}
	//tinh trung binh tung dac trung theo tung nhom cua no
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 6; j++) {
			result[i][j] = result[i][j] / Count[i];
		}
	delete[] Count;
	return result;
}
// thuat toan kmean
//Input:vector 2 chieu luu toa do cua off stroke,index luu chi cua so nhom offstroke duoc chon la offstroke new line
//Output:vector flag  danh dau 1,2,3,45 dai dien cho 5 cluste. Dong thoi, cap nhat vi tri cua index
bool Check(vector<int> flag_before, vector<int> flag_after)
{
	int Count = 0; // dem so phan tu giong nhau giua 2 lan phan nhom
	if (flag_after.empty() || flag_before.empty())
		return false;
	for (int i = 0; i < flag_after.size(); i++)
	{
		if (flag_after[i] == flag_before[i])
			Count++;
	}
	double div =(double) Count / flag_after.size();
	if ( div ==1)
		return true;
	return false;
}
vector<int> Kmeans(vector<vector<double>> offstroke,int &index) {
	vector<vector<double>> feature1;
	vector<vector<double>> feature2;
	vector<double> feature3,feature4;
	FeatureExtract(offstroke, feature1, feature2, feature3, feature4);
	//Centroids: Luu gia tri trung binh cua 5 cluster
	vector<vector<double>> Centroids;
	vector<double>temp_centroid;

	// first we will take 5 value-sets to assign into 5 centroids repetitive
	// each centroid storing 6 agrument : Ox1 ,Oy1,Ox2,Oy2,distance,direction
	for (int j = 0; j < 5; j++) {
		int i = j * 10;
		temp_centroid.push_back(feature1[i].front());
		temp_centroid.push_back(feature1[i].back());
		temp_centroid.push_back(feature2[i].front());
		temp_centroid.push_back(feature2[i].back());
		temp_centroid.push_back(feature3[i]);
		temp_centroid.push_back(feature4[i]);
		Centroids.push_back(temp_centroid);
		temp_centroid.clear();
	}
	
	//tao 1 vector flag danh dau 1,2,3,45 dai dien cho 5 cluster
	vector<int> flag;
	vector<int>temp_flag;
	// consider each offstroke to delivery to each centroid
	// first loop
	int count = 0;
	while (true)
	{
		// assign each offstroke into the store in which corresponding
		for (int i = 0; i < offstroke.size();i++) {
			vector<double>point1 = offstroke[i];
			i++;
			vector<double>point2 = offstroke[i];
			int pos=0;
			pos = findMinDistance(point1, point2, Centroids);
			flag.push_back(pos);
			flag.push_back(pos);
		}
		// calculate average for each centroid
		Centroids=Average(offstroke,flag);
		if (Check(temp_flag, flag)) {
			cout << count;
			break;
		}
		temp_flag.clear();
		temp_flag = flag;
		flag.clear();
		count++;
		
	} 
	
	int max = 0;

	for (int i = 1; i < 5; i++)
		if (Centroids[i][4] > Centroids[max][4])
			max = i;
	index = max;
	// flag hien gio da phan loai cac offstroke bang cach gan chi so tuong ung voi nhom chua offstroke do
	return flag;
}

