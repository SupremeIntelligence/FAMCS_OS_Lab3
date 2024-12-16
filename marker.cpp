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
	cout << "Thread " << ID << " started to work" << endl;

	srand(ID);

	while (true)
	{
		int markedCount = 0;
		int number = rand();
		int index = number % numbers.size();

		if (numbers[index] == 0)
		{
			Sleep(5);
			numbers[index] == ID;
			markedCount++;
			Sleep(5);
		}
		else
		{
			cout << "\tThread ID:\t" << ID << endl;
			cout << "\tAmount of marked array elements:\t" << markedCount << endl;
			cout << "\tIndex of the element that cannot be marked:\t" << "???" << endl;
		}
		SetEvent(stopEvent);
		WaitForSingleObject(continueEvent, INFINITE);
		if (WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	if (WaitForSingleObject(stopEvent, 0) == WAIT_OBJECT_0)
	{
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] == ID)	numbers[i] = 0;
		}
	}
	return 0;
}