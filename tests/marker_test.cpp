#define BOOST_TEST_MODULE MarkerTests
#include <boost/test/included/unit_test.hpp>
#include <windows.h>
#include"globals.h"
#include"marker.cpp"

std::vector<int> numbers;
std::vector<HANDLE> stopEvents;
std::vector<HANDLE> doneEvents;
HANDLE startEvent;
CRITICAL_SECTION cs;

struct InitTestData
{
	InitTestData()
	{
		int size = 10;
		numbers.resize(size, 0);
		InitializeCriticalSection(&cs);

		startEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
		BOOST_REQUIRE(startEvent != nullptr);

		int threadAmount = 2;

		stopEvents.resize(threadAmount);
		doneEvents.resize(threadAmount);

		for (int i = 0; i < stopEvents.size(); ++i) {
			stopEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
			doneEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
			BOOST_REQUIRE(stopEvents[i] != nullptr);
			BOOST_REQUIRE(doneEvents[i] != nullptr);
		}
	}

	~InitTestData() {
		for (HANDLE event : stopEvents) {
			CloseHandle(event);
		}
		for (HANDLE event : doneEvents) {
			CloseHandle(event);
		}
		CloseHandle(startEvent);
		DeleteCriticalSection(&cs);
	}
};

BOOST_FIXTURE_TEST_SUITE(MarkerTestsSuite, InitTestData)

BOOST_AUTO_TEST_CASE(MarkerStartTest)
{
	int threadID = 0;
	HANDLE thread = CreateThread(nullptr, 0, marker, &threadID, 0, nullptr);
	BOOST_REQUIRE(thread != nullptr);

	SetEvent(startEvent);

	WaitForSingleObject(doneEvents[threadID], INFINITE);

	EnterCriticalSection(&cs);
	bool foundID = false;
	for (int val : numbers) {
		if (val == threadID) {
			foundID = true;
			break;
		}
	}
	LeaveCriticalSection(&cs);

	BOOST_CHECK(foundID);
	CloseHandle(thread);
}

BOOST_AUTO_TEST_CASE(MarkerArrayFillingTest)
{
	int threadID = 1;
	HANDLE thread = CreateThread(nullptr, 0, marker, &threadID, 0, nullptr);
	BOOST_REQUIRE(thread != nullptr);

	SetEvent(startEvent);

	WaitForSingleObject(doneEvents[threadID], INFINITE);

	EnterCriticalSection(&cs);
	int count = 0;
	for (int val : numbers) {
		if (val == threadID) {
			count++;
		}
	}
	LeaveCriticalSection(&cs);

	BOOST_CHECK_GT(count, 0);
	CloseHandle(thread);
}

BOOST_AUTO_TEST_CASE(MarkerStopTest) {
	int threadID = 1;
	HANDLE thread = CreateThread(nullptr, 0, marker, &threadID, 0, nullptr);
	BOOST_REQUIRE(thread != nullptr);

	SetEvent(startEvent);

	SetEvent(stopEvents[threadID]);
	WaitForSingleObject(doneEvents[threadID], INFINITE);

	BOOST_CHECK(WaitForSingleObject(thread, 0) == WAIT_OBJECT_0);
	CloseHandle(thread);
}

BOOST_AUTO_TEST_SUITE_END()