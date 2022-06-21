#include "Adapter.h"
#include <iostream>

void NewMallardDuck::quack()
{
	std::cout << "Quack\n";
}

void NewMallardDuck::fly()
{
	std::cout << "I'm flying\n";
}

void WildTurkey::gobble()
{
	std::cout << "Gobble gobble\n";
}

void WildTurkey::fly()
{
	std::cout << "I'm flying a short distance\n";
}

TurkeyAdapter::TurkeyAdapter(ITurkey* turkey)
{
	this->turkey = turkey;
}

void TurkeyAdapter::quack()
{
	turkey->gobble();
}

void TurkeyAdapter::fly()
{
	for (int i = 0; i < 5; i++)
		turkey->fly();
}

void Adapter::DuckTestDrive()
{
	NewMallardDuck* duck = new NewMallardDuck();

	WildTurkey* turkey = new WildTurkey();
	IDuck* turkeyAdapter = new TurkeyAdapter(turkey);

	std::cout << "The Turkey says....\n";
	turkey->gobble();
	turkey->fly();

	std::cout << "\nThe Duck says...\n";
	testDuck(duck);

	std::cout << "\nThe TurkeyAdapter says...\n";
	testDuck(turkeyAdapter);
}

void Adapter::testDuck(IDuck* duck)
{
	duck->quack();
	duck->fly();
}
