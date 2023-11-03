#include "test_lp.h"

STATUS
(__cdecl _MultithreadFibonacci)(
	IN_OPT PVOID Context
	)
{
	STATUS status = STATUS_UNSUCCESSFUL, status1, status2;
	PLP_FIB_THREAD_CONTEXT context =
		(PLP_FIB_THREAD_CONTEXT)Context;
	if (context->Index == 0 || context->Index == 1) {
		context->Result = 1;
		return STATUS_SUCCESS;
	}
	LP_FIB_THREAD_CONTEXT context1 = { .Index = context->Index - 1 , .Result = 0 };
	LP_FIB_THREAD_CONTEXT context2 = { .Index = context->Index - 2 , .Result = 0 };
	PTHREAD thread1 = NULL;
	PTHREAD thread2 = NULL;
	char thName[MAX_PATH];
	__try
	{
		snprintf(thName, MAX_PATH, " Fib -% d ", context1.Index);
		status1 = ThreadCreate(thName,
			ThreadPriorityDefault,
			_MultithreadFibonacci,
			&context1,
			&thread1
		);

		snprintf(thName, MAX_PATH, " Fib -% d ", context2.Index);
		status2 = ThreadCreate(thName,
			ThreadPriorityDefault,
			_MultithreadFibonacci,
			&context2,
			&thread2
		);

		ThreadWaitForTermination(thread1, &status1);
		ThreadWaitForTermination(thread2, &status2);

		if (!SUCCEEDED(status1))
		{
			LOG_FUNC_ERROR(" ThreadCreate ", status1);
			__leave;
		}

		if (!SUCCEEDED(status2))
		{
			LOG_FUNC_ERROR(" ThreadCreate ", status2);
			__leave;
		}

		status = STATUS_SUCCESS;
		context->Result = context1.Result + context2.Result;
	}
	__finally
	{
		if (thread1)
		{
			ThreadCloseHandle(thread1);
		}
		if (thread2)
		{
			ThreadCloseHandle(thread2);
		}
	}
	return status;
}