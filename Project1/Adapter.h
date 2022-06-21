#pragma once

class IDuck
{
public:
	virtual void quack() = 0;
	virtual void fly() = 0;

};

class NewMallardDuck : public IDuck
{
public:
	virtual void quack() override;
	virtual void fly() override;
};

class ITurkey
{
public:
	virtual void gobble() = 0;
	virtual void fly() = 0;
};

class WildTurkey : public ITurkey
{
public:
	virtual void gobble() override;
	virtual void fly() override;
};

class TurkeyAdapter : public IDuck
{
public:
	TurkeyAdapter(ITurkey* turkey);
	virtual void quack() override;
	virtual void fly() override;

private:
	ITurkey* turkey;
};

class Adapter
{
public:
	static void DuckTestDrive();
private:
	static void testDuck(IDuck* duck);
};