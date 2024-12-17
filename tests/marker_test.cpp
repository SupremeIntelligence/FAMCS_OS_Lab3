#define BOOST_TEST_MODULE MarkerTests
#include <boost/test/included/unit_test.hpp>
#include <windows.h>
#include"globals.h"

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

BOOST_AUTO_TEST_CASE(MarkerStartTest)
{

}

BOOST_AUTO_TEST_CASE(MarkerStopTest)
{

}

