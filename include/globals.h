#ifndef GLOBALS_H
#define GLOBALS_H

#include<windows.h>
#include<vector>

extern std::vector<int>numbers;
extern HANDLE startEvent;			
extern std::vector<HANDLE> stopEvents;
extern std::vector<HANDLE> doneEvents;
extern CRITICAL_SECTION cs;

#endif // GLOBALS_H