#include "StrategyPattern.h"
#include <iostream>
using namespace std;

void IFlyBehavior::fly()
{
}

void IFlyWithWings::fly()
{
	cout << "I'm flying!!\n";
}

void IFlyNoWay::fly()
{
	cout << "I can't fly\n";
}

void IQuack::quack()
{
	cout << "Quack\n";
}

void IMuteQuack::quack()
{
	cout << "<< Silence >>\n";
}

void ISqueak::quack()
{
	cout << "Squeak\n";
}

Duck::Duck()
{
	flyBehavior = nullptr;
	quackBehavior = nullptr;
}

void Duck::setFlyBehavior(IFlyBehavior* fb)
{
	flyBehavior = fb;
}

void Duck::setQuackBehavior(IQuackBehavior* qb)
{
	quackBehavior = qb;
}

void Duck::Display()
{
	cout << "I'm a duck\n";
}

void Duck::performFly()
{
	flyBehavior->fly();
}

void Duck::performQuack()
{
	quackBehavior->quack();
}
void Duck::swim()
{
	cout << "All ducks float, even decoys!";
}

MallardDuck::MallardDuck()
{
	quackBehavior = new IQuack();
	flyBehavior = new IFlyWithWings();
}

void MallardDuck::Display()
{
	cout << "I'm a real Mallard duck\n";
}

ModelDuck::ModelDuck()
{
	flyBehavior = new IFlyNoWay();
	quackBehavior = new IQuack();
}

void ModelDuck::Display()
{
	cout << "I'm a model duck\n";
}

void IFlyRocketPowered::fly()
{
	cout << "I'm flying with a rocket!\n";
}
