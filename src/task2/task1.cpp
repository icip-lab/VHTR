#include "task1.h"

int Exp(int size)
{
	int result = 1;
	if (size == 0)
		return result;
	for (int i = 0; i<size; i++)
		result = result * 10;
	return result;
}

vector<string> readNameFile(string filename) {
	vector<string>fileOut;
	fstream fileIn(filename);
	if (fileIn.fail())
		cout << "cannot read file!  ";
	else {
		while (!fileIn.eof()) {
			string str;
			fileIn >> str;
			fileOut.push_back(str);
		}
	}
	return fileOut;
}

vector<vector<double>> readfile(const char *filename, vector<vector<double>>&offstroke)
{
	vector<vector<double>> result;
	fstream fp(filename);
	if (fp.fail()) {
		cout << "can't read file !!!" << endl;
		return result;
	}
	else {
		string temp;
		char comma;
		double Temp;
		double x_temp, y_temp;
		vector<double> x_coordinates;
		vector<double> y_coordinates;
		vector<double> coor_offstroke;
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
					double Makenumber = 0;
					for (int j = i + 1; j<temp.size(); j++) {
						string a;
						a.push_back(temp[j]);
						Makenumber = Makenumber + atoi(a.c_str())*Exp(temp.size() - j - 1);
					}
					x_coordinates.push_back(Makenumber);
					fp >> Temp;
					y_coordinates.push_back(Temp);
					coor_offstroke.push_back(Makenumber);
					coor_offstroke.push_back(Temp);
					offstroke.push_back(coor_offstroke);
					if (!coor_offstroke.empty())
						coor_offstroke.clear();
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
			coor_offstroke.push_back(x_coordinates.back());
			coor_offstroke.push_back(y_coordinates.back());
			offstroke.push_back(coor_offstroke);
			if (!coor_offstroke.empty())
				coor_offstroke.clear();

		}
		fp.close();
		result.push_back(x_coordinates);
		result.push_back(y_coordinates);
	}
	return result;
}

void SetWindowSize(size_t width, size_t height)
{
	HANDLE output_handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (output_handle == INVALID_HANDLE_VALUE)
		return;// false;

	SMALL_RECT rect = {};
	rect.Bottom = static_cast<SHORT>(width);
	rect.Right = static_cast<SHORT>(height);
	if (::SetConsoleWindowInfo(output_handle, TRUE, &rect) == FALSE)
		return;// false

	COORD coord = {};
	coord.X = rect.Bottom + 1;
	coord.Y = rect.Right + 1;

	return;// (::SetConsoleScreenBufferSize(output_handle, coord) != FALSE);
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}