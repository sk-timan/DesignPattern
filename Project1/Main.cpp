#pragma once
#include <algorithm>
#include "StrategyPattern.h"
#include "Observer.h"
#include "Decorator.h"
#include "SimpleFactory.h"
#include "Factory.h"
#include "AbstractFactory.h"
#include "Singleton.h"
#include "MethodInvocation.h"
#include "Adapter.h"
#include "Facade.h"
#include <map>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

//#include "Iterator.h"


namespace MoveAndForward
{
	void foo(int& f)
	{
		int temp = f;
		std::cout << "f is lvalue\n";
		std::cout << "f's address:  " << &f << endl;
	}
	
	void foo(int&& f)
	{
		int temp = f;
		std::cout << "f is rvalue\n";
		std::cout << "f's address:  " << &f << endl;
	}
	
	/************************************************************************/
	/*  �������ã��������Ĳ�������ֵ��T��agr���ᱻ�Ƶ�Ϊ��ֵ����
		�紫�룺 int x = 27; T��agr���ͱ�Ϊ int&
				 const int cx = x; T��agr���ͱ�Ϊ const int&
				 const int& rx = x; T��agr���ͱ�Ϊ const int&
	*/
	/************************************************************************/
	template<typename T>
	void deduce(T&& agr)
	{
		std::cout << "agr's address: " << &agr << endl;
		/************************************************************************/
		/*	���к����βν�Ϊ��ֵ
			std::forward<>������ǿ���ͱ�ת��
			��������deduce��ʵ������ֵ������£�ִ������ֵ�ͱ��ǿ��ת��
		*/
		/************************************************************************/
		foo(std::forward<T>(agr));

		/**
		 * std::forward<>����ǿת��ֵ
		 */
		//foo(std::forward<T>(std::move(agr)));
	}

	int& RefInput(int& in)
	{
		return in;
	}

	int ValInput(int& in)
	{
		return in;
	}

	int* PInput(int in)
	{
		int a = in;
		return &in;
	}

	static void MoveSemanticsAndPerfectForwarding()
	{
		int i;
		int b = 1;
		/************************************************************************/
		/*  move��������ǿ�ƽ���������ת��Ϊ��ֵ���ã����ܴ���ʲô����,
			��ʵ��ת��Ϊ����ֵ
			remove_reference_t<_Ty> = typename remove_reference<_Ty>::type;
		*/
		/************************************************************************/
		int&& j = std::move(2);
		int p = std::move(3);
		int&& k = 6;
		int& m = b;
		const int c = 5;
		volatile int d = 6;

		foo(std::move(j));
		foo(j);
		
		std::cout << "i's address: " << &i << endl;
		deduce(i);

		std::cout << "b's address: " << &b << endl;
		deduce(b);
		deduce(1);
		deduce(1);

		std::cout << "j's address: " << &j << endl;
		deduce(j);
		
		deduce(std::move(1));
		std::cout << "i's address: " << &i << endl;
		deduce(std::move(i));

		deduce(std::move(j));
	
		deduce(p);

		deduce(std::move(k));

		deduce(m);

		deduce(RefInput(m));
		deduce(ValInput(m));
		deduce(*PInput(m));
		deduce(std::move(m));
		deduce(std::move(RefInput(m)));

	}
}

namespace SharedPointerTest
{
	struct MediaAsset
	{
		virtual ~MediaAsset() = default; // make it polymorphic
	};

	struct Song : public MediaAsset
	{
		std::wstring artist;
		std::wstring title;
		Song(const std::wstring& artist_, const std::wstring& title_) :
			artist{ artist_ }, title{ title_ } {}
	};

	struct Photo : public MediaAsset
	{
		std::wstring date;
		std::wstring location;
		std::wstring subject;
		Photo(
			const std::wstring& date_,
			const std::wstring& location_,
			const std::wstring& subject_) :
			date{ date_ }, location{ location_ }, subject{ subject_ } {}
	};


	static void SharedPointerTestSong()
	{
		auto deleter = [](Song* song)
		{
			cout << "Call custom Deleter.\n";
			wcout << song->artist << L"'s " << song->title << " ��ɾ��" << endl;
			delete song;
			song = nullptr;
		};

		shared_ptr<Song> song1{ new Song(L"��ղ",L"��ղ�ĸ�"),deleter };
		shared_ptr<Song> song2 = make_shared<Song>(L"��ɲ", L"�ո�");
		shared_ptr<Song> song3;
		song2 = song1;
		song3 = song2;


		vector<shared_ptr<Song>> v{
				make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
				make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
				make_shared<Song>(L"Thal��a", L"Entre El Mar y Una Estrella")
		};

		vector<shared_ptr<Song>> v2;
		std::remove_copy_if(v.begin(), v.end(), back_inserter(v2),
			[](shared_ptr<Song> s) {return s->artist.compare(L"Bob Dylan") == 0; }
		);

		for (const auto& s : v2)
		{
			wcout << s->artist << L":" << s->title << endl;
		}
	};

	static void SharedPointerTestPhoto()
	{
		vector <shared_ptr<MediaAsset>> assets
		{
			make_shared<Song>(L"Himesh Reshammiya", L"Tera Surroor"),
			make_shared<Song>(L"Penaz Masani", L"Tu Dil De De"),
			make_shared<Photo>(L"2011-04-06", L"Redmond, WA", L"Soccer field at Microsoft.")
		};

		vector<shared_ptr<MediaAsset>> photos;

		copy_if(assets.begin(), assets.end(), back_inserter(photos),
			[](shared_ptr<MediaAsset> p)->bool
			{
				shared_ptr<Photo> temp = dynamic_pointer_cast<Photo>(p); // MediaAsset class is polymorphic
				return temp.get() != nullptr;
			});

		for (const auto& p : photos)
		{
			wcout << "Photo location: " << (static_pointer_cast<Photo>(p))->location << endl;
		}
	}

	static void UniquePtrTestFunc()
	{
		auto deleter = [](Song* song)
		{
			cout << "unique_ptr custom deleter called.\n";
			wcout << song->artist << L"'s " << song->title << L" ��ɾ����" << endl;
			delete song;
			song = nullptr;
		};

		unique_ptr<Song, decltype(deleter)> song2{ new Song(L"��ղ",L"��ղ��һ�޶��ĸ�"),deleter };

		vector<unique_ptr<Song>> songs;

		// Create a few new unique_ptr<Song> instances
		// and add them to vector using implicit move semantics.
		songs.push_back(make_unique<Song>(L"B'z", L"Juice"));
		songs.push_back(make_unique<Song>(L"Namie Amuro", L"Funky Town"));
		songs.push_back(make_unique<Song>(L"Kome Kome Club", L"Kimi ga Iru Dake de"));
		songs.push_back(make_unique<Song>(L"Ayumi Hamasaki", L"Poker Face"));

		// Pass by const reference when possible to avoid copying.
		for (const auto& song : songs)
		{
			wcout << L"Artist: " << song->artist << L"   Title: " << song->title << endl;
		}
	}

	unique_ptr<Song> SongFactory(const std::wstring& artist, const std::wstring& title)
	{
		// Implicit move operation into the variable that stores the result.
		return make_unique<Song>(artist, title);
	}

	static void UniquePtrTestFunc2()
	{
		// Create a new unique_ptr with a new object.
		auto song = make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

		// Use the unique_ptr.
		vector<wstring> titles = { song->title };

		// Move raw pointer from one unique_ptr to another.
		unique_ptr<Song> song2 = std::move(song);

		// Obtain unique_ptr from function that returns by value.
		auto song3 = SongFactory(L"Michael Jackson", L"Beat It");
	}

}

namespace WeakPointerTest
{
	class Controller
	{
	public:
		int Num;
		wstring Status;
		//vector<shared_ptr<Controller>> others;  // shared_ptr����ɻ�������
		vector<weak_ptr<Controller>> others;

		explicit Controller(int i) : Num(i), Status(L"On")
		{
			wcout << L"Creating Controller" << Num << endl;
		}

		~Controller()
		{
			wcout << L"Destroying Controller" << Num << endl;
		}

		// Demonstrates how to test whether the pointed-to memory still exists or not.
		void CheckStatuses() const 
		{
			for_each(others.begin(), others.end(), [](weak_ptr<Controller> wp)
				{
					auto p = wp.lock();
					if (p)
					{
						wcout << L"Status of " << p->Num << " = " << p->Status << endl;
					}
					else
					{
						wcout << L"Null object" << endl;
					}
				});
		}
	};

	static void WeakPointerTestFun()
	{
		vector<shared_ptr<Controller>> v
		{
			make_shared<Controller>(0),
			make_shared<Controller>(1),
			make_shared<Controller>(2),
			make_shared<Controller>(3),
			make_shared<Controller>(4)
		};

		// Each controller depends on all others not being deleted.
		// Give each controller a pointer to all the others.
		for (int i = 0; i < v.size(); i++)
		{
			for_each(v.begin(), v.end(), [&v, i](shared_ptr<Controller> p)
				{
					if (p->Num != i)
					{
						v[i]->others.push_back(static_cast<weak_ptr<Controller>>(p));
						wcout << L"push_back to v[" << i << "]: " << p->Num << endl;
					}
				});

		}

		for_each(v.begin(), v.end(), [](shared_ptr<Controller>& p)
			{
				wcout << L"use_count = " << p.use_count() << endl;
				p->CheckStatuses();
			});
	}
}

namespace PassByRefTest
{

	void PassBy(int n)
	{
		cout << "Pass by Value." << endl;
	}

	void PassBy(int& n)
	{
		cout << "Pass by Reference." << endl;
	}

	void pass_by_value(int* p)
	{
		//Allocate memory for int and store the address in p
		cout << &p << endl;
		p = new int;
		cout << &p << endl;
	}

	void pass_by_reference(int*& p)
	{
		cout << &p << endl;
		p = new int;
		cout << &p << endl;
	}

	void pass_by_Val(int p)
	{
		cout << &p << endl;
		p = *new int(254);
		cout << &p << endl;
	}

	void pass_by_Ref(int& p)
	{
		cout << &p << endl;
		p = *new int(259);
		cout << &p << endl;
	}

	int PassByRefTestFun()
	{
		int* p1 = NULL;
		int* p2 = NULL;
		int p3 = 0;
		int p4 = 1;
		//cout << &p1 << endl;
		//cout << &p2 << endl;
		cout << &p3 << endl;
		cout << &p4 << endl;


		pass_by_value(p1); //p1 will still be NULL after this call
		pass_by_reference(p2); //p2 's value is changed to point to the newly allocate memory
		pass_by_Val(p3);
		pass_by_Ref(p4);

		cout << "p1's address = " << p1 << endl;
		cout << "p2's address = " << p2 << endl;
		cout << "p3's val = " << p3 << endl;
		cout << "p4's val = " << p4 << endl;

		return 0;
	}
}

class A
{
public:
	virtual void test()
	{
		cout << "A test\n";
	}
	~A()
	{
		cout << "A ����\n";
	}
};
class B : public A
{
public:
	void test()
	{
		cout << "B test\n";
	}
	~B()
	{
		cout << "B ����\n";
	}
};

namespace HashSet
{
	class MyHashMap
	{
	public:
		MyHashMap() : buckets(BUCKET_SIZE) {};

		void put(int key, int value)
		{
			for (int i = 0; i < buckets[hash(key)].size(); i++)
			{
				if (key == buckets[hash(key)][i].first)
				{
					buckets[hash(key)][i].second = value;
					return;
				}
			}

			buckets[hash(key)].push_back(pair<int, int>(key, value));
		}

		int get(int key)
		{
			for (int i = 0; i < buckets[hash(key)].size(); i++)
			{
				if (key == buckets[hash(key)][i].first)
					return buckets[hash(key)][i].second;
			}
			return -1;
		}

		void remove(int key)
		{
			for (int i = 0; i < buckets[hash(key)].size(); i++)
			{
				if (key == buckets[hash(key)][i].first)
				{
					buckets[hash(key)].erase(buckets[hash(key)].begin() + i);
					return;
				}
			}
		}

	private:
		inline int hash(int key) const noexcept
		{
			return key % BUCKET_SIZE;
		}
	private:
		vector<vector<pair<int, int>>> buckets;
		static const int BUCKET_SIZE = 765;
	};

	void HashSetTestFunc()
	{
		// 1. ��ʼ����ϣ��
		unordered_set<int> hashset;
		// 2. ������
		hashset.insert(3);
		hashset.insert(2);
		hashset.insert(1);
		// 3. ɾ����
		hashset.erase(2);
		// 4. ��ѯ���Ƿ�����ڹ�ϣ������
		if (hashset.count(2) <= 0)
			cout << "�� 2 ���ڹ�ϣ������" << endl;
		// 5. ��ϣ���ϵĴ�С
		cout << "��ϣ���ϵĴ�СΪ: " << hashset.size() << endl;
		// 6. ������ϣ����
		for (auto it = hashset.begin(); it != hashset.end(); ++it) {
			cout << (*it) << " ";
		}
		cout << "�ڹ�ϣ������" << endl;
		// 7. ��չ�ϣ����
		hashset.clear();
		// 8. �鿴��ϣ�����Ƿ�Ϊ��
		if (hashset.empty())
		{
			cout << "��ϣ����Ϊ�գ�" << endl;
		}
	}
	void HashMapTestFunc()
	{
		// 1. ��ʼ����ϣ��
		unordered_map<int, int> hashmap;
		// 2. ����һ���µģ�����ֵ����
		hashmap.insert(make_pair(0, 0));
		hashmap.insert(make_pair(2, 3));
		// 3. ����һ���µģ�����ֵ���ԣ����߸���ֵ
		hashmap[1] = 1;
		hashmap[1] = 2;
		// 4. ����ض�����Ӧ��ֵ
		cout << "The value of key 1 is: " << hashmap[1] << endl;
		// 5. ɾ����
		hashmap.erase(2);
		// 6. �����Ƿ�����ڹ�ϣ����
		if (hashmap.count(2) <= 0)
		{
			cout << "�� 2 ���ڹ�ϣ����" << endl;
		}
		// 7. ��ϣ��Ĵ�С
		cout << "��ϣ��Ĵ�СΪ: " << hashmap.size() << endl;
		// 8. ������ϣ��
		for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
			cout << "(" << it->first << "," << it->second << ") ";
		}
		cout << "�ڹ�ϣ����" << endl;
		// 9. ��չ�ϣ��
		hashmap.clear();
		// 10. ����ϣ���Ƿ�Ϊ��
		if (hashmap.empty()) {
			cout << "��ϣ��Ϊ�գ�" << endl;
		}
	}
}

class Solution
{
public:
	int lenLongestFibSubseq(vector<int>& arr)
	{
		int n = arr.size();
		unordered_map<int, int> Index;
		for (int i = 0; i < n; i++)
			Index[arr[i]] = i;

		unordered_map<int, int> temp;
		int outVal = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (arr[i] - arr[j] < arr[j] && Index.count(arr[i] - arr[j]) > 0)
				{
					temp[j * n + i] = temp[Index[arr[i] - arr[j]] * n + j] + 1;
					outVal = max(outVal, temp[j * n + i] + 2);
				}
			}
		}
		return outVal;
	}
};


int main()
{
	//StrategyPattern::StrategyPatternDisplay();
	//Observer::ObserverTest();
	//DecoratorPattern::DecoratorPatternDisplay();
	//SimpleFactory::SimpleFactoryDisplay();
	//Factory::FactoryDisplay();
	//AbstractFactory::AbstractFactoryDisplay();
	//MoveAndForward::MoveSemanticsAndPerfectForwarding();
	SharedPointerTest::SharedPointerTestSong();
	//SharedPointerTest::SharedPointerTestPhoto();
	//SharedPointerTest::UniquePtrTestFunc();
	//SharedPointerTest::UniquePtrTestFunc2();
	//WeakPointerTest::WeakPointerTestFun();
	//PassByRefTest::PassByRefTestFun();
	//ZTYThreadFuncTest();
	//Singleton::SingletonMultithreadFunc();
	//MethodInvocation::RemoteControlTestFunc();
	//MethodInvocation::RemoteLoaderTestFunc();
	//Adapter::DuckTestDrive();
	//Facade::HomeTheaterTestDrive();
	//Iterator::IteratorTestFunc();
	//HashSet::HashSetTestFunc();

	//A a;
	//A a2 = a;
	//cout << noexcept(A()) << endl;
	//cout << noexcept(A(move(a2))) << endl;
	////A a3 = move(a2);
	//B b;
	//B c = b;
	//cout << noexcept(B(move(c))) << endl;
	//B d = move(c);
	//cout << noexcept(B(std::declval<B>())) << endl;    // false
	//cout << noexcept(B(std::declval<B>(), 1)) << endl; // true
	//cout << noexcept(D(std::declval<D>())) << endl;    // true

	/*A* pa = new B();
	B* pb = new B();
	pa->test();
	pb->test();
	delete pa;
	delete pb;*/

	/*Solution a;
	vector<int> v = { 1, 2, 1, 1 };
	cout << a.rob(v);*/

	cout << (int)(3.99) << endl;


}
	