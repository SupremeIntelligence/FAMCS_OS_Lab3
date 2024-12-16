#ifndef GLOBALS_H
#define GLOBALS_H

#include<windows.h>
#include<vector>

extern std::vector<int>numbers;
extern std::vector<HANDLE>threads;
extern HANDLE startEvent;
extern HANDLE stopEvent;
extern HANDLE continueEvent;

#endif // GLOBALS_H