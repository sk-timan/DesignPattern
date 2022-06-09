#pragma once
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_THREADS 3
#define BUF_SIZE 255

DWORD WINAPI MyThreadFunction(PVOID lpParam);
void ErrorHandler(const LPWSTR lpszFunction);

// Sample custom data structure for threads to use.
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).
typedef struct MyData
{
	int val1;
	int val2;
}MYDATA, *PMYDATA;

// 创建线程实例
void ZTYThreadFuncTest();

class Singleton
{
private:
	Singleton();
	~Singleton();

public:
	  static volatile Singleton* getInstance();

	  static void SingletonMultithreadFunc();

	  int count = 0;

	  static DWORD SingletonThreadWork(LPVOID lpParm);

private:
	/**
	 * 1.如果 getInstance 不是很频繁的使用，那就什么都不做；
	 * 2.如果总是创建并使用，一种方式采用静态初始化，在运行前创建完毕；
	 * 3.另一种方式使用双重检查锁减少同步次数。
	 */

	//static Singleton* uniqueInstance;

	//当两个线程都要用到某一个变量且该变量的值会被改变时，应该用 volatile 声明，
	//该关键字的作用是防止优化编译器把变量从内存装入 CPU 寄存器中。
	//如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，
	//这会造成程序的错误执行。
	//volatile 的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值
	volatile static Singleton* uniqueInstance;
};