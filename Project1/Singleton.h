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

// �����߳�ʵ��
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
	 * 1.��� getInstance ���Ǻ�Ƶ����ʹ�ã��Ǿ�ʲô��������
	 * 2.������Ǵ�����ʹ�ã�һ�ַ�ʽ���þ�̬��ʼ����������ǰ������ϣ�
	 * 3.��һ�ַ�ʽʹ��˫�ؼ��������ͬ��������
	 */

	//static Singleton* uniqueInstance;

	//�������̶߳�Ҫ�õ�ĳһ�������Ҹñ�����ֵ�ᱻ�ı�ʱ��Ӧ���� volatile ������
	//�ùؼ��ֵ������Ƿ�ֹ�Ż��������ѱ������ڴ�װ�� CPU �Ĵ����С�
	//���������װ��Ĵ�������ô�����߳��п���һ��ʹ���ڴ��еı�����һ��ʹ�üĴ����еı�����
	//�����ɳ���Ĵ���ִ�С�
	//volatile ����˼���ñ�����ÿ�β����ñ���ʱһ��Ҫ���ڴ�������ȡ����������ʹ���Ѿ����ڼĴ����е�ֵ
	volatile static Singleton* uniqueInstance;
};