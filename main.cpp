// OS_Lab3.cpp: определяет точку входа для приложения.
//

#include "OS_Lab3.h"
#include<vector>
#include<windows.h>
#include"marker.cpp"
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

	vector<int>numbers(size, 0);
	vector<HANDLE>threads(threadAmount);
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


	HANDLE startEvent;
	startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (startEvent == nullptr)
	{
		//
	}

	SetEvent(startEvent);
	WaitForMultipleObjects(threadAmount, threads.data(), TRUE, INFINITE);

	for (HANDLE thread : threads)
	{
		CloseHandle(thread);
	}
	CloseHandle(startEvent);
	return 0;
}
