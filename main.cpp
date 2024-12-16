// OS_Lab3.cpp: определяет точку входа для приложения.
//

#include "OS_Lab3.h"
#include<vector>
#include<windows.h>
#include"marker.cpp"
#include"globals.h"
using namespace std;

int main()
{
	int size, threadAmount;
	cout << "Enter the size of the array:\t";
	cin >> size;
	cout << "Enter the number of threads:\t";
	cin >> threadAmount;
	if (threadAmount <= 0)
	{
		//exception handling
	}

	numbers.resize(size, 0);
	threads.resize(threadAmount);
	vector<int>threadIDs(threadAmount);

	for (int i = 0; i < threadAmount; i++)
	{
		threadIDs[i] = i;
		threads[i] = CreateThread(NULL, 0, marker, &threadIDs[i], 0, NULL);
		if (threads[i] == nullptr)
		{
			//exception handling
		}
	}

	startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (startEvent == nullptr)
	{
		//
	}

	if (SetEvent(startEvent))
	{
		//
	}
	WaitForMultipleObjects(threadAmount, threads.data(), TRUE, INFINITE);

	for (HANDLE thread : threads)
	{
		CloseHandle(thread);
	}

	if (CloseHandle(startEvent))
	{
		//
	}
	return 0;
}
