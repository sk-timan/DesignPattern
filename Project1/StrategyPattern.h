#pragma once
#include <string>
using namespace std;

class IFlyBehavior
{
public:
	virtual void fly();
};

class IFlyWithWings : public IFlyBehavior
{
public:
	virtual void fly() override;

};

class IFlyNoWay : public IFlyBehavior
{
public:
	virtual void fly() override;

};

class IFlyRocketPowered : public IFlyBehavior
{
public:
	virtual void fly() override;
};

class IQuackBehavior
{
public:
	virtual void quack() {};
};

class IQuack : public IQuackBehavior
{
public:
	virtual void quack() override;
};

class IMuteQuack : public IQuackBehavior
{
public:
	virtual void quack() override;
};

class ISqueak : public IQuackBehavior
{
public:
	virtual void quack() override;
};

class Duck
{
public:
	Duck();

	IFlyBehavior* flyBehavior;
	IQuackBehavior* quackBehavior;

public:
	virtual void Display();
	void performFly();
	void performQuack();
	void swim();
	void setFlyBehavior(IFlyBehavior* fb);
	void setQuackBehavior(IQuackBehavior* qb);


};

class MallardDuck : public Duck
{
public:
	MallardDuck();
	virtual void Display() override;
};

class ModelDuck : public Duck
{
public:
	ModelDuck();
	virtual void Display() override;
};

class StrategyPattern
{
public:
	static void StrategyPatternDisplay()
	{
		Duck* mallard = new MallardDuck();
		mallard->performQuack();
		mallard->performFly();
		mallard->Display();

		delete mallard;

		mallard = new ModelDuck();
		mallard->performFly();
		IFlyRocketPowered* flyPowered = new IFlyRocketPowered();
		mallard->setFlyBehavior(flyPowered);
		mallard->performFly();

		delete mallard;
	}
};