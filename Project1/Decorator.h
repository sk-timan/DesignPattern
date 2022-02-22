#pragma once
#include <string>
#include <vector>
using namespace std;


class Beverage
{
public:
	virtual string getDescription() { return description; };
	virtual double cost() = 0;
	virtual ~Beverage() {};
	void Eat();

protected:
	string description = "Unknown Beverage";

};

class CondimentDecorator : public Beverage
{
public:
};

class Espresso : public Beverage
{
public:
	Espresso();

	virtual double cost() override;
};

class HouseBlend : public Beverage
{
public:
	HouseBlend();

	virtual double cost() override;
};

class DarkRoast : public Beverage
{
public:
	DarkRoast();

	virtual double cost() override;
};

class Decat : public Beverage
{
public:
	Decat();

	virtual double cost() override;
};

class Mocha : public CondimentDecorator
{
public:
	Mocha(Beverage* beverage);
	~Mocha();

	virtual string getDescription() override;
	virtual double cost() override;
private:
	Beverage* beverage;
};

class Soy : public CondimentDecorator
{
public:
	Soy(Beverage* beverage);
	~Soy();

	virtual string getDescription() override;
	virtual double cost() override;
private:
	Beverage* beverage;
};

class Whip : public CondimentDecorator
{
public:
	Whip(Beverage* beverage);
	~Whip();

	virtual string getDescription() override;
	virtual double cost() override;
private:
	Beverage* beverage;
};

class DecoratorPattern
{
public:
	static void DecoratorPatternDisplay();
};