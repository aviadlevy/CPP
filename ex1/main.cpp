#include <iostream>

using namespace std;

#define size 6

int main()
{
	float numbers[size];
	int indices[size], max = 0, size2 = size;
	cout << "enter 6 numbers between 0 and 1:\n";
	for (int i = 0; i < size; i++)
	{
		cin >> numbers[i];
	}
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] <= 0 || numbers[i] >= 1)
		{
			i = -1;
			cout << "ERROR\n";
			for (int j = 0; j < size; j++)
			{
				cin >> numbers[j];
			}
		}
	}
	cout << "sorted indices:\n";
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < size; i++)
		{
			if (numbers[max] < numbers[i])
			{
				max = i;
			}
		}
		indices[--size2] = max;
		numbers[max] = 0;
		max = 0;
	}
	for (int i = 0; i < size; i++)
	{
		cout << ' ' << indices[i];
	}
	return 0;
}
