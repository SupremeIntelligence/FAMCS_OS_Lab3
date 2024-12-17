#include<iostream>
#include<windows.h>
#include<vector>
#include"globals.h"
#include<time.h>

using namespace std;

DWORD WINAPI marker(LPVOID lpParameter)
{

	int ID = *static_cast<int*>(lpParameter);

	WaitForSingleObject(startEvent, INFINITE);
	EnterCriticalSection(&cs);
	cout << "Thread " << ID << " started." << endl;
	LeaveCriticalSection(&cs);

	srand(ID);

	while (true)
	{
		int markedCount = 0;
		int number = rand();
		int index = number % numbers.size();

		EnterCriticalSection(&cs);
		if (numbers[index] == 0)
		{
			Sleep(5);
			numbers[index] = ID;
			markedCount++;
			Sleep(5);
		}
		else
		{

			cout << endl << "\tThread ID:\t" << ID << endl;
			cout << "\tAmount of marked array elements:\t" << markedCount << endl;
			cout << "\tIndex of the element that cannot be marked:\t" << index << endl << endl;
			LeaveCriticalSection(&cs);

			SetEvent(doneEvents[ID]);						//передаем потоку main сигнал о невозможности продолжения работы
			WaitForSingleObject(stopEvents[ID], INFINITE);	//ожидаем сигнал завершения работы от потока main
			if (WaitForSingleObject(stopEvents[ID], 0) == WAIT_OBJECT_0)
			{
				break;
			}
		}
		LeaveCriticalSection(&cs);
	}
	if (WaitForSingleObject(stopEvents[ID], 0) == WAIT_OBJECT_0)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] == ID)	numbers[i] = 0;
		}
	}

	cout << "Thread " << ID << " finished." << endl;
	SetEvent(doneEvents[ID]); // Сигнал завершения работы

	return 0;
}