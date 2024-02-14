#include <iostream>

using namespace std;

void next_permut(char arr[], int size)
{
	int index{ 0 }, min{ 0 }, min_ind{ 0 }, buf{ 0 };
	for (int i{ size - 1 }; i > 0; --i)
	{
		if (arr[i] > arr[i - 1])
		{
			index = i;
			min = arr[i];
			min_ind = i;

			for (int j{ i }; j < size; ++j)
			{
				if (min > arr[j] && arr[j] > arr[i - 1])
				{
					min = arr[j];
					min_ind = j;
				}
			}

			buf = arr[index - 1];
			arr[index - 1] = arr[min_ind];
			arr[min_ind] = buf;
			break;
		}
	}

	for (int i{ index }; i < index + (size - index) / 2; ++i)
	{
		buf = arr[i];
		arr[i] = arr[size - i + index - 1];
		arr[size - i + index - 1] = buf;
	}

	for (int i{ 0 }; i < size; ++i)
	{
		cout << arr[i] << " ";
	}
}

int main()
{
	int size{ 0 };

	cin >> size;
	char* arr = new char[size];

	for (int i{ 0 }; i < size; ++i)
	{
		cin >> arr[i];
	}

	next_permut(arr, size);

	return 0;
}