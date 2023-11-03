#pragma once
#include "HAL9000.h"
#include "thread.h"


typedef struct _LP_FIB_THREAD_CONTEXT {
	int Index;
	unsigned long Result;
}LP_FIB_THREAD_CONTEXT, * PLP_FIB_THREAD_CONTEXT;


STATUS
(__cdecl _MultithreadFibonacci)(IN_OPT PVOID Context);