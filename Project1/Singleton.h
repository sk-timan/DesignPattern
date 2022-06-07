#pragma once
#include <windows.h>

CRITICAL_SECTION SingletonScopeLock;

class Singleton
{
private:
	Singleton();
	~Singleton();

public:
	  static volatile Singleton* getInstance();

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

//Singleton* Singleton::uniqueInstance = new Singleton();
volatile Singleton* Singleton::uniqueInstance = nullptr;