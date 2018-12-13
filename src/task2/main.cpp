#include "task1.h"
#include "task2.h"
using namespace std;

void DrawPixels(HWND hwnd) {
	string str = ".\\VNOnDB_Paragraph\\train_set.txt";
	vector<string> name = readNameFile(str);
	//for (int i = 0; i < 4; i++) {
	//string filename = ".\\VNOnDB_Paragraph\\InkData\\"+name[8];
	string filename = ".\\test.inkml"; // could you provide this test file
	const wchar_t * impath = L".\\example\\test.png";

	// Draw strokes to screen
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint(hwnd, &ps);
	vector<vector<int>>offstroke;
	vector<vector<int>> results = readfile(filename.c_str(), offstroke);
	cout << "Loading something..." << endl;
	vector<vector<int>>newline = Kmeans(offstroke);
	vector<int>x_coordinates = (vector<int>)results.front();
	vector<int>y_coordinates = (vector<int>)results.back();
	for (int i = 0; i < x_coordinates.size(); i++) {
		double x =(double) x_coordinates[i] / 40; // (int / int) is not float
		double y =(double) y_coordinates[i] / 40;
		SetPixel(hdc, x, y, RGB(0, 0, 255));
	}
	for (int i = 0; i < newline.size(); i++) {

		double x =(double) newline[i].front() / 40;
		double y =(double) newline[i].back() / 40;
		SetPixel(hdc, x, y, RGB(255, 0, 0));
	}
	EndPaint(hwnd, &ps);

	// Print screen to file
	RECT rect_1 = { 0 };
	GetWindowRect(hwnd, &rect_1);
	ATL::CImage* image_ = new CImage();
	image_->Create(1300, 700, 32);
	HDC device_context_handle = image_->GetDC();
	PrintWindow(hwnd, device_context_handle, PW_CLIENTONLY);

	image_->Save(impath, Gdiplus::ImageFormatPNG);
	image_->ReleaseDC();
	delete image_;
	//	int n = (i + 1);
	//	sleepcp(10000*n);
	//}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };

	//If you want to create a new console later you can call AllocConsole.
	//Then reopen the stdout for "cout" operator
	BOOL allocConsole_flag = AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	if (allocConsole_flag == TRUE) {
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
		100, 100, 1300, 750, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	srand(time(NULL));

	return (int)msg.wParam;
}