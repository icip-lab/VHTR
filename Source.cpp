#include <windows.h>
#include <time.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <atlstr.h> 
#include <atlimage.h>
using namespace std;

int Ten(int size)
{
	int result = 1;
	if (size == 0)
		return result;
	for (int i = 0; i<size; i++)
		result = result * 10;
	return result;
}
vector<vector<int>> readfile(char *filename)
{
	vector<vector<int>> result;
	fstream fp(filename);
	if (fp.fail())
	{
		cout << "can't read file !!!" << endl;
		return result;
	}
	else
	{
		string temp;
		char dauphay;
		int Temp;
		int x_temp, y_temp;
		vector<int> x_coordinates;
		vector<int> y_coordinates;
		bool isempty = false;
		while (!fp.eof())
		{
			do
			{
				fp >> temp;
				if (fp.eof())
					break;

			} while (temp != "<trace");

			if (fp.eof())
				break;
			fp >> temp;

			for (int i = 0; i<temp.size(); i++)
				if (temp[i] == '>')
				{
					int Makenumber = 0;
					for (int j = i + 1; j<temp.size(); j++)
					{

						string a;
						a.push_back(temp[j]);
						Makenumber = Makenumber + atoi(a.c_str())*Ten(temp.size() - j - 1);
					}
					x_coordinates.push_back(Makenumber);
					fp >> Temp;
					y_coordinates.push_back(Temp);
					break;
				}
			do
			{
				fp >> dauphay;
				if (dauphay == '<')
					break;
				fp >> x_temp;
				fp >> y_temp;

				x_coordinates.push_back(x_temp);
				y_coordinates.push_back(y_temp);

			} while (dauphay != '<');
		}
		fp.close();
		result.push_back(x_coordinates);
		result.push_back(y_coordinates);


	}
	return result;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"Pixels";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Pixels",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 300, 250, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	srand(time(NULL));

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_PAINT:

		DrawPixels(hwnd);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void DrawPixels(HWND hwnd) {

	PAINTSTRUCT ps;
	RECT rect = { 0 };

	GetClientRect(hwnd, &rect);
	if (rect.bottom == 0) {

		return;
	}
	GetWindowRect(hwnd, &rect);
	ATL::CImage* image_ = new CImage();
	image_->Create(rect.right - rect.left, rect.bottom - rect.top, 32);
	HDC hdc = GetDC(NULL);
	hdc=BeginPaint(hwnd, &ps);
	vector<vector<int>> results = readfile("test1.txt");
	vector<int>x_coordinates = (vector<int>)results.front();
	vector<int>y_coordinates = (vector<int>)results.back();
	for (int i = 0; i<x_coordinates.size()/2; i++) {
		
		float x = x_coordinates[i]/40;//% r.right;//x_coordinates[i];
		float y = y_coordinates[i]/40;//% r.bottom;
		SetPixel(hdc, x, y, RGB(0, 0, 255));
		if(image_)
		hdc = image_->GetDC();
	}
	
	string impath = "D:\RVH\Win32Project1\Win32Project1";
	EndPaint(hwnd, &ps);
	
	image_->Save((LPCTSTR)impath.c_str(), Gdiplus::ImageFormatPNG);
	image_->ReleaseDC();
	delete image_;
}
