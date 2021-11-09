#include<iostream>
#include <iomanip>
#include<vector>
using namespace std;

int main()
{
	int row, column;
	cout << "행과 열의 개수를 입력하시오:" << endl;
	cin >> row >> column;
	double** matrix = new double*[row];
	for (int count = 0; count < row; ++count) {
		matrix[count] = new double[column];
	}
	double** matrix2 = new double*[row];
	for (int count = 0; count < row; ++count) {
		matrix2[count] = new double[column];
	}
	double** matrix3 = new double*[row];
	for (int count = 0; count < row; ++count) {
		matrix3[count] = new double[column];
	}

	cout << "행과 열의 요소(0이 아닌 정수)를 입력하시오: " << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cin >> matrix[i][j];
		}
		cout << "\n";
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			matrix3[i][j]= matrix[i][j];
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <row; j++)
		{
			if (i == j)matrix2[i][j] = 1;
			else matrix2[i][j]=0;
		}
	}

	for (int i = 0; i < row ; i++) {
		
		for (int k = i + 1; k < row; k++) {
			double  term = matrix[k][i] / matrix[i][i];
			matrix2[k][i] = term;
			for (int j = 0; j < column; j++) {
				matrix[k][j] = matrix[k][j] - term*matrix[i][j];
				if ( matrix[k][j] < 0.000001 && -0.000001 < matrix[k][j])
				{
					matrix[k][j] = 0;
				}
			}

		}
		
	}
	cout << "A=LU 출력:"<< endl;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cout << setw(9) << matrix3[i][j] << "  ";
			}
			cout << "|";
			for (int j = 0; j < row; j++) {
				cout << setw(9) << matrix2[i][j] << "  ";
			}
			cout << "|";

			for (int j = 0; j < column; j++) {
				cout << setw(9)<<matrix[i][j] << "  ";
			}
			cout << "|";
			
			cout << "\n";
		}
		
		return 0;

	}