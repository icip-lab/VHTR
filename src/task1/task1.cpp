#include "stdafx.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd);

int Ten(int size)
{
	int result = 1;
	if (size == 0)
		return result;
	for (int i = 0; i<size; i++)
		result = result * 10;
	return result;
}

vector<vector<int>> readfile(const char *filename)
{
	vector<vector<int>> result;
	fstream fp(filename);
	if (fp.fail()) {
		cout << "can't read file !!!" << endl;
		return result;
	}
	else {
		string temp;
		char comma;
		int Temp;
		int x_temp, y_temp;
		vector<int> x_coordinates;
		vector<int> y_coordinates;
		bool isempty = false;
		while (!fp.eof()) {
			do {
				fp >> temp;
				if (fp.eof())
					break;
			} while (temp != "<trace");

			if (fp.eof())
				break;
			fp >> temp;

			for (int i = 0; i<temp.size(); i++)
				if (temp[i] == '>') {
					int Makenumber = 0;
					for (int j = i + 1; j<temp.size(); j++) {
						string a;
						a.push_back(temp[j]);
						Makenumber = Makenumber + atoi(a.c_str())*Ten(temp.size() - j - 1);
					}
					x_coordinates.push_back(Makenumber);
					fp >> Temp;
					y_coordinates.push_back(Temp);
					break;
				}
			do {
				fp >> comma;
				if (comma == '<')
					break;
				fp >> x_temp;
				fp >> y_temp;

				x_coordinates.push_back(x_temp);
				y_coordinates.push_back(y_temp);
			} while (comma != '<');
		}
		fp.close();
		result.push_back(x_coordinates);
		result.push_back(y_coordinates);
	}
	return result;
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
	string filename = ".\\example\\test1.txt";
	const wchar_t * impath = L".\\example\\test1.png";

	// Draw strokes to screen
	PAINTSTRUCT ps;
	
	HDC hdc = BeginPaint(hwnd, &ps);
	vector<vector<int>> results = readfile(filename.c_str());
	cout << "Loading something..." << endl;

	vector<int>x_coordinates = (vector<int>)results.front();
	vector<int>y_coordinates = (vector<int>)results.back();
	for (int i = 0; i<x_coordinates.size() / 2; i++) {

		float x = x_coordinates[i] / 40;//% r.right;//x_coordinates[i];
		float y = y_coordinates[i] / 40;//% r.bottom;
		SetPixel(hdc, x, y, RGB(0, 0, 255));
	}
	EndPaint(hwnd, &ps);

	// Print screen to file
	RECT rect_1 = { 0 };
	GetWindowRect(hwnd, &rect_1);
	ATL::CImage* image_ = new CImage();
	image_->Create(rect_1.right - rect_1.left, rect_1.bottom - rect_1.top, 32);
	HDC device_context_handle = image_->GetDC();
	PrintWindow(hwnd, device_context_handle, PW_CLIENTONLY);
	image_->Save(impath, Gdiplus::ImageFormatPNG);
	image_->ReleaseDC();
	delete image_;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };

	//If you want to create a new console later you can call AllocConsole.
	//Then reopen the stdout for "cout" operator
	BOOL allocConsole_flag = AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	if (allocConsole_flag == true) {
		cout << "Successfully allocated new console" << endl;
	}
	else {
		cout << "Unsuccessfully allocated new console" << endl;
	}

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