#pragma once
#include "StrategyPattern.h"
#include "Observer.h"
#include "Decorator.h"
#include "SimpleFactory.h"
#include "Factory.h"
#include "AbstractFactory.h"
#include "Singleton.h"
#include <algorithm>

namespace MoveAndForward
{
	void foo(int& f)
	{
		std::cout << "f is lvalue\n";
	}
	
	void foo(int&& f)
	{
		std::cout << "f is rvalue\n";
	}
	
	//template<class T>
	//void deduce(T& agr)
	//{
	//	foo(agr);
	//	foo(std::forward<T>(agr));
	//}
	
	template<typename T>
	void deduce(T&& agr)
	{
		//foo(agr);
		foo(std::forward<T>(agr));
		//foo(static_cast<T&&>(agr));
		//foo(std::move(agr));
	}
	
	static void MoveSemanticsAndPerfectForwarding()
	{
		int i;
		int b = 1;
		int&& j = std::move(2);
		int p = std::move(3);
		int&& k = 6;
	
		deduce(i);
		deduce(1);
		deduce(j);
		deduce(std::move(1));
		deduce(std::move(i));
		deduce(std::move(j));
	
	
		//foo(i);
		//foo(j);
	
		//foo(std::move(j));
		//foo(3);
		//foo(std::move(i));
	
		//foo(std::forward<int>(i));
		//foo(std::forward<int>(i));
	
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
		vector<shared_ptr<Song>> v{
				make_shared<Song>(L"Bob Dylan", L"The Times They Are A Changing"),
				make_shared<Song>(L"Aretha Franklin", L"Bridge Over Troubled Water"),
				make_shared<Song>(L"Thalía", L"Entre El Mar y Una Estrella")
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

}

namespace WeakPointerTest
{
	class Controller
	{
	public:
		int Num;
		wstring Status;
		//vector<shared_ptr<Controller>> others;  // shared_ptr将造成环形引用
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
	void pass_by_value(int* p)
	{
		//Allocate memory for int and store the address in p
		p = new int;
		
	}

	void pass_by_reference(int*& p)
	{
		p = new int;
	}

	int PassByRefTestFun()
	{
		int* p1 = NULL;
		int* p2 = NULL;

		pass_by_value(p1); //p1 will still be NULL after this call
		pass_by_reference(p2); //p2 's value is changed to point to the newly allocate memory

		cout << "p1's address = " << p1 << endl;
		cout << "p2's address = " << p2 << endl;
		return 0;
	}
}

int main()
{
	//StrategyPattern::StrategyPatternDisplay();
	//Observer::ObserverTest();
	//DecoratorPattern::DecoratorPatternDisplay();
	//SimpleFactory::SimpleFactoryDisplay();
	//Factory::FactoryDisplay();
	//AbstractFactory::AbstractFactoryDisplay();
	//MoveAndForward::MoveSemanticsAndPerfectForwarding();
	//SharedPointerTest::SharedPointerTestSong();
	//SharedPointerTest::SharedPointerTestPhoto();
	//WeakPointerTest::WeakPointerTestFun();
	//PassByRefTest::PassByRefTestFun();
	//ZTYThreadFuncTest();
	Singleton::SingletonMultithreadFunc();
}
	