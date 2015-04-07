#include "matrix.h"
using namespace std;

int func(int const num);

int main()
{
	vector<int> vec = {1,2,3,14,15,6,7,8,19,10,11,12,3,14,15,16};
	Matrix<int> matrix = Matrix<int>(4,4,vec);
	cout << matrix.trace();
	vector<int> const vec2 = {10,2,3,14,15,6,7,8,19,10,11,1,3,14,15,16};
	Matrix<int> matrix2 = Matrix<int>(4,4,vec2);
	int i = 0;
	Matrix<int> matrix3 = matrix - matrix2;
	for(typename Matrix<int>::iterator iter = matrix3.begin(); iter != matrix3.end(); iter++)
	{
		std::cout << *iter << " ";
	}

	cout << matrix2.trace();
	return 0;
}

int func(int const num)
{
	return num*2;
}