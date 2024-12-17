// OS_Lab3.cpp: определяет точку входа для приложения.

#include<vector>
#include<windows.h>
#include"marker.cpp"
#include"globals.h"
using namespace std;


HANDLE startEvent;
vector<HANDLE> stopEvents;
vector<HANDLE> doneEvents;
vector<int>numbers;
CRITICAL_SECTION cs;

void ArrayOutput(const vector<int>& arr)
{
	cout << "[ ";
	for (int i = 0; i < numbers.size(); i++)
	{
		cout << numbers[i] << " ";
	}
	cout << "]" << endl;
}

int main()
{
	InitializeCriticalSection(&cs);

	int size, threadAmount;
	cout << "Enter the size of the array:\t";
	cin >> size;
	cout << "Enter the number of threads:\t";
	cin >> threadAmount;
	cout << endl;
	if (threadAmount <= 0)
	{
		//exception handling
	}

	numbers.resize(size, 0);
	stopEvents.resize(threadAmount);
	doneEvents.resize(threadAmount);
	vector<HANDLE>threads(threadAmount);
	vector<int>threadIDs(threadAmount);

	for (int i = 0; i < threadAmount; i++)
	{
		threadIDs[i] = i;
		threads[i] = CreateThread(NULL, 0, marker, &threadIDs[i], 0, NULL);
		stopEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
		doneEvents[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
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

	if (!SetEvent(startEvent))
	{
		//
	}
	int terminatedThreads = 0;
	while (true)
	{
		if (terminatedThreads == threadAmount)
		{
			cout << "All threads finished." << endl;
			break;
		}

		bool ThreadsDone = true;

		for (int i = 0; i < threadAmount; i++)
		{
			if (WaitForSingleObject(doneEvents[i], 0) != WAIT_OBJECT_0)
			{
				ThreadsDone = false;
				break;
			}
		}

		if (ThreadsDone)
		{
			EnterCriticalSection(&cs);
			cout << endl << "Main output #1:\t";	
			ArrayOutput(numbers);
			LeaveCriticalSection(&cs);

			int stopThreadID = -1;
			do 
			{
				cout << "Enter a valid ID of thread you want to stop:\t";
				cin >> stopThreadID;
			} while (stopThreadID < 0 || stopThreadID >= threadAmount);

			SetEvent(stopEvents[stopThreadID]);						//подаем указанному потоку сигнал о завершении работы
			WaitForSingleObject(threads[stopThreadID], INFINITE);	//ожидаем от потока сигнал о завершении работы
			terminatedThreads++;

			EnterCriticalSection(&cs);
			cout << endl << "Main output #2:\t";	
			ArrayOutput(numbers);
			LeaveCriticalSection(&cs);

			for (int i = 0; i < threadAmount; ++i)
			{
				if (i != stopThreadID)
				{
					ResetEvent(stopEvents[i]);	//переводим сигнал остановки в несигнальное состояние, сообщая другим потокам продолжить работу
				}
			}
		}
	}

	WaitForMultipleObjects(threadAmount, threads.data(), TRUE, INFINITE);

	CloseHandle(startEvent);
	for (int i = 0; i < threadAmount; i++)
	{
		CloseHandle(threads[i]);
		CloseHandle(stopEvents[i]);
		CloseHandle(doneEvents[i]);
	}

	DeleteCriticalSection(&cs);
	return 0;
}
