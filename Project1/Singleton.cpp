#include "Singleton.h"

CRITICAL_SECTION SingletonScopeLock;
volatile Singleton* Singleton::uniqueInstance = nullptr;

Singleton::Singleton()
{
}


Singleton::~Singleton()
{
	DeleteCriticalSection(&SingletonScopeLock);
}

volatile Singleton* Singleton::getInstance()
{
	if (uniqueInstance == nullptr)
	{
		if (!InitializeCriticalSectionAndSpinCount(&SingletonScopeLock, 0x00000400))
			return nullptr;

		EnterCriticalSection(&SingletonScopeLock);
		//
		if (uniqueInstance == nullptr)
		{
			uniqueInstance = new Singleton();
		}
		//
		LeaveCriticalSection(&SingletonScopeLock);
	}

	return uniqueInstance;
}

void Singleton::SingletonMultithreadFunc()
{
	HANDLE hThreads[MAX_THREADS];
	DWORD wdThreadsIDArray[MAX_THREADS];
	LPVOID lpThreadsCountArray[MAX_THREADS];

	for (int i = 0; i < MAX_THREADS; i++)
	{
		lpThreadsCountArray[i] = new int(i + 1);
		if (lpThreadsCountArray[i] == NULL)
		{
			ExitProcess(1);
		}

		hThreads[i] = CreateThread(
			NULL,
			0,
			SingletonThreadWork,
			lpThreadsCountArray[i],
			0,
			&wdThreadsIDArray[i]);

		if (hThreads[i] == NULL)
		{
			ErrorHandler((LPWSTR)("CreateThread"));
			ExitProcess(3);
		}
	}

	WaitForMultipleObjects(MAX_THREADS, hThreads, TRUE, INFINITE);

	for (int i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(hThreads[i]);

		if (lpThreadsCountArray[i] != NULL)
		{
			delete lpThreadsCountArray[i];
			lpThreadsCountArray[i] = NULL;
		}
	}

}

DWORD Singleton::SingletonThreadWork(LPVOID lpParm)
{
	HANDLE hSTDOut;
	int ThreadID;
	int InstanceCount;

	hSTDOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hSTDOut == INVALID_HANDLE_VALUE)
		return 1;

	ThreadID = *(int*)lpParm;

	InstanceCount = ++getInstance()->count;


	TCHAR msgBuf[BUF_SIZE];
	StringCchPrintf(msgBuf, BUF_SIZE, L"Thread: %d ;current count = %d\n", ThreadID,InstanceCount);
	size_t cchStringSize;
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	DWORD dwChars;
	WriteConsole(hSTDOut, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

	return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	HANDLE hStdout;
	PMYDATA pDataArray;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive out results
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because
	// it was checked for NULL before the thread was created.
	pDataArray = (PMYDATA)lpParam;

	// Print the parameter values using thread-safe functions.
	StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Parameters = %d, %d\n"),
		pDataArray->val1, pDataArray->val2);
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL); 

	return 0;
}

void ErrorHandler(const LPWSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0,
		NULL);

	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(
		LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction,
		dw,
		lpMsgBuf);

	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	// Free error-handling buffer allocations.
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}


void ZTYThreadFuncTest()
{
	PMYDATA pDataArray[MAX_THREADS];
	DWORD dwThreadIdArray[MAX_THREADS];
	HANDLE hThreadArray[MAX_THREADS];

	// Create MAX_THREADS worker threads.

	for (int i = 0; i < MAX_THREADS; i++)
	{
		// Allocate memory for thread data.

		pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(MYDATA));

		if (pDataArray[i] == NULL)
		{
			// If the array allocation fails, the system is out of memory
			// so there is no point in trying to print an error message.
			// Just terminate execution.
			ExitProcess(2);
		}

		// Generate unique data for each thread to work with.

		pDataArray[i]->val1 = i;
		pDataArray[i]->val2 = i + 100;

		// Create the thread to begin execution on its own.
		hThreadArray[i] = CreateThread(
			NULL,					// default security attributes
			0,						// use default stack size
			MyThreadFunction,		// thread function name
			pDataArray[i],			// argument to thread function
			0,						// use default creation flags
			&dwThreadIdArray[i]);	// returns the thread identifier

		// Check the return value for success.
		// If CreateThread fails, terminate execution. 
		// This will automatically clean up threads and memory. 
		if (hThreadArray[i] == NULL)
		{
			ErrorHandler((LPWSTR)("CreateThread"));
			ExitProcess(3);
		}
	} // End of main thread creation loop.

	// Wait until all threads have terminated.

	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.
	for (int i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(hThreadArray[i]);
		if (pDataArray[i] != NULL)
		{
			HeapFree(GetProcessHeap(), 0, pDataArray[i]);
			pDataArray[i] = NULL;		// Ensure address is not reused.
		}
	}

}

