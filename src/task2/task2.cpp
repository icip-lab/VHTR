#include "task2.h"
using namespace std;

// vector<int> point1 : a pair of coordernate x,y of point1

//phia duoi em goi ham D (tinh khoang cach giua 2 diem ) theo nhieu kieu du lieu nen em tao toi 3 ham D 
double D(vector<int>point1, vector<double>point2) { // computute the distance between two points
	double x = (point1.front() - point2.front())*(point1.front() - point2.front());
	double y = (point1.back() - point2.back())*(point1.back() - point2.back());
	return sqrt((double)(x + y));
}

double D(vector<int>point1, vector<int>point2) { // compute the distance between two points
	double x = (point1.front() - point2.front())*(point1.front() - point2.front());
	double y = (point1.back() - point2.back())*(point1.back() - point2.back());
	return sqrt((double)(x + y));
}

double D(vector<double>point1, vector<double>point2) {
	double x = (point1.front() - point2.front())*(point1.front() - point2.front());
	double y = (point1.back() - point2.back())*(point1.back() - point2.back());
	return sqrt((double)(x + y));
}

// point1 & point2 are two pairs of coordernate of an offstroke( first coor & last coor)
// ham nay dung de tim noi chua cua cai offstroke dang xet trong 5 bo Centroid ( chua trong vector<vector> Centroids)
// em da danh so thu tu cho 5 set va ham nay se tra ve vi tri Centroid chua cai offstroke dang xet 
int findMinDistance(vector<int> point1,vector<int>point2,vector<vector<double>> Centroids)
{
	vector<double>temp;
	temp = Centroids[0];
	vector<double>temp1, temp2;

	// temp[0] , temp[1] are a pair of begin coor of an offstroke 
	temp1.push_back(temp[0]);
	temp1.push_back(temp[1]);
	double d1 = D(point1, temp1);
	// temp[2] , temp[3] are a pair of last coor of an offstroke 

	temp2.push_back(temp[2]);
	temp2.push_back(temp[3]);
	double d2 = D(point2, temp2);
	double min = d1*d1 + d2*d2 + (D(temp1, temp2) - temp[4])*(D(temp1, temp2) - temp[4]);
	int pos = 0;
	temp.clear();
	temp1.clear();
	temp2.clear();
	for (int i = 1; i < 5; i++) {
		temp = Centroids[i];
		temp1.push_back(temp[0]);
		temp1.push_back(temp[1]);
		double d1 = D(point1, temp1);
		temp2.push_back(temp[2]);
		temp2.push_back(temp[3]);
		double d2 = D(point2, temp2);
		double distance = d1*d1 + d2*d2 + (D(temp1, temp2) - temp[4])*(D(temp1, temp2) - temp[4]);
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
// ham Direction la cai feature thu 4 , tim huong cua cai offstroke dang xet
double Direction(vector<int> point1, vector<int>point2) // calculate the direction of an offstroke ( using corner)
{
	double tan; // calculate the conrner of an offstroke
	if (point1.front() < point2.front())
	{

		double d = D(point1, point2);
		double pytago = sqrt((double)d*d - (double)point2.back()*point2.back());
		tan = point2.back() / pytago;
	}
	else
	{

		double d = D(point1, point2);
		double pytago = sqrt((double)d*d - (double)point1.back()*point1.back());
		tan = point1.back() / pytago;

	}
	return tan;
}


//ham FeatureExtract: vector<vector> offstroke chua thong tin toa do cua cac offstroke ,
// o day em luu vao vector<vector> offstroke theo kieu cu 2 phan tu ke tiep nhau la toa do dau( khi nhac but len) va toa
//  do cuoi( khi dat but xuong) cua 1 offstroke
// muc dich cua ham FeatureExtract la dua vao vector<vector>offstroke em se tao ra duoc 4 cai dac trung nhu o phia duoi
void FeatureExtract(vector<vector<int>> offstroke, vector<vector<int>> &feature1, vector<vector<int>> &feature2, vector<double> &feature3, vector<double> &feature4)
{
	vector<int> temp;

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
vector<double> Average(vector<vector<int>> Store)
{
	vector<double> result;
	vector<int> Ox1, Ox2, Oy1, Oy2; // coordernate of an offstroke
	vector<double> length,dir; // length of an offstroke
	for (int i = 0; i< Store.size(); i = i + 2)
	{
		Ox1.push_back(Store[i].front());
		Ox2.push_back(Store[i + 1].front());
		Oy1.push_back(Store[i].back());
		Oy2.push_back(Store[i + 1].back());
		double d = sqrt((double)pow(Store[i].front() - Store[i+1].front(), 2) + (double)pow(Store[i ].back() - Store[i + 1].back(), 2));
		dir.push_back(Direction(Store[i], Store[i + 1]));
		length.push_back(d);
	}
	int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	double s5=0,s6=0;
	for (int i = 0; i<Ox1.size(); i++)
	{
		s1 = s1 + Ox1[i];
		s2 = s2 + Ox2[i];
		s3 = s3 + Oy1[i];
		s4 = s4 + Oy2[i];
		s5 = s5 + length[i];
		s6 = s6 + dir[i];
	}

	int size = Ox1.size();
	// check if size is equal 0
	if (size == 0)
		size = 1;
	result.push_back(s1 / size);
	result.push_back(s3 / size);
	result.push_back(s2 / size);
	result.push_back(s4 / size);
	result.push_back(s5 / size);
	result.push_back(s6 / size);


	return result;


}
// thuat toan kmean
vector<vector<int>> Kmeans(vector<vector<int>> offstroke) {
	/// what does offstroke consist of?
	// make 5 stores corresponding to 5 Centroids 
	// what does "5 stores" mean? --> 5 clusters/groups? 
	// 5 stores phia duoi tuong ung voi 5 bo chua cac offstroke 
	// cai kmean nay em dung de phan ra 5 loai offstroke do anh( short, long, newline...)
	// nen 5 cai stores se chua cac offstroke tuong ung
	vector<vector<vector<int>>> Store;
	vector<vector<int>> Store0, Store1, Store2, Store3, Store4;
	vector<vector<int>> feature1;
	vector<vector<int>> feature2;
	vector<double> feature3,feature4;

	// 5 centroids

	/// Please explain how does "FeatureExtract" work?
	// sau khi goi ham nay minh tim duoc 4 cai dac trung cua tung offstroke
	//feature1 se luu lan luot toa do x,y cua diem thu 1( luc nhac but len) cua offstroke
	//feature2 se luu lan luot toa do x,y cua diem thu 2 cua offstroke( khi dat but xuong)
	// feature3 luu chieu dai cua offstroke
	// feature4 luu huong cua offstroke ( o day em tinh huong bang cach tinh tan cua goc giua duong thang 
	//noi 2 diem cua offstroke voi truc hoanh )
	FeatureExtract(offstroke, feature1, feature2, feature3, feature4);

	vector<double>short_offstroke_centroid;
	vector<double>long_offstroke_centroid;
	vector<double>newline_offstroke_centroid;
	vector<double>mark_offstroke_centroid;
	vector<double>delayedstroke_centroid;
	vector<vector<double>> Centroids;

	// first we will take 5 value-sets to assign into 5 centroids repetitive
	// each centroid storing 6 agrument : Ox1 ,Oy1,Ox2,Oy2,distance,direction
	short_offstroke_centroid.push_back(feature1[0].front());//0
	short_offstroke_centroid.push_back(feature1[0].back());
	short_offstroke_centroid.push_back(feature2[0].front());
	short_offstroke_centroid.push_back(feature2[0].back());

	short_offstroke_centroid.push_back(feature3[0]);
	short_offstroke_centroid.push_back(feature4[0]);
	long_offstroke_centroid.push_back(feature1[1].front());//1
	long_offstroke_centroid.push_back(feature1[1].back());
	long_offstroke_centroid.push_back(feature2[1].front());
	long_offstroke_centroid.push_back(feature2[1].back());
	long_offstroke_centroid.push_back(feature3[1]);
	long_offstroke_centroid.push_back(feature4[1]);
	newline_offstroke_centroid.push_back(feature1[2].front());//2
	newline_offstroke_centroid.push_back(feature1[2].back());
	newline_offstroke_centroid.push_back(feature2[2].front());
	newline_offstroke_centroid.push_back(feature2[2].back());
	newline_offstroke_centroid.push_back(feature3[2]);
	newline_offstroke_centroid.push_back(feature4[2]);
	mark_offstroke_centroid.push_back(feature1[3].front());//3
	mark_offstroke_centroid.push_back(feature1[3].back());
	mark_offstroke_centroid.push_back(feature2[3].front());
	mark_offstroke_centroid.push_back(feature2[3].back());
	mark_offstroke_centroid.push_back(feature3[3]);
	mark_offstroke_centroid.push_back(feature4[3]);
	delayedstroke_centroid.push_back(feature1[4].front());//4
	delayedstroke_centroid.push_back(feature1[4].back());
	delayedstroke_centroid.push_back(feature2[4].front());
	delayedstroke_centroid.push_back(feature2[4].back());
	delayedstroke_centroid.push_back(feature3[4]);
	delayedstroke_centroid.push_back(feature4[4]);
	// Centroids dung de chua 5 bo o tren
	Centroids.push_back(short_offstroke_centroid);
	Centroids.push_back(long_offstroke_centroid);
	Centroids.push_back(newline_offstroke_centroid);
	Centroids.push_back(mark_offstroke_centroid);
	Centroids.push_back(delayedstroke_centroid);
	// consider each offstroke to delivery to each centroid
	int Count = 0;// first loop
	while (Count <= 15)
	{
		// assign each offstroke into the store in which corresponding
		for (int i = 0; i < offstroke.size();i++) {
			vector<int>point1 = offstroke[i];
			i++;
			vector<int>point2 = offstroke[i];
			int pos;
			pos = findMinDistance(point1, point2, Centroids);
			if (pos == 0)
			{
				Store0.push_back(point1);
				Store0.push_back(point2);
			}
			if (pos == 1)
			{
				Store1.push_back(point1);
				Store1.push_back(point2);
			}
			if (pos == 2)
			{
				Store2.push_back(point1);
				Store2.push_back(point2);
			}
			if (pos == 3)
			{
				Store3.push_back(point1);
				Store3.push_back(point2);
			}
			if (pos == 4)
			{
				Store4.push_back(point1);
				Store4.push_back(point2);
			}

		}
		Store.push_back(Store0);
		Store.push_back(Store1);
		Store.push_back(Store2);
		Store.push_back(Store3);
		Store.push_back(Store4);
		Store0.clear();
		Store1.clear();
		Store2.clear();
		Store3.clear();
		Store4.clear();

		// calculate average for each centroid
		for (int t = 0; t < 5; t++)
			Centroids[t]=Average(Store[t]);
		if(Count<15)
			Store.clear();
		// caculate average value of each store and update centroids
		// each store stroring couple coordenate information of off stroke, after computating the distance between them
		// step 2: we made the data with 5 value, after comutating average of each value
		//

		Count++;
	}
	// return store[i] that has largest centroid[i][4]   (centroid[i][4] is length of offstroke)
	int max = 0;

	for (int i = 1; i < 5; i++)
		if (Centroids[i][4] > Centroids[max][4])
			max = i;

	//return
	return Store[max];
	
}

