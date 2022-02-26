#include "Decorator.h"
#include <iostream>

Espresso::Espresso()
{
	description = "Espresso";
}

double Espresso::cost()
{
	return 1.99;
}

HouseBlend::HouseBlend()
{
	description = "House Blend Coffee";
}

double HouseBlend::cost()
{
	return 0.89;
}

Mocha::Mocha(Beverage* beverage)
{
	this->beverage = beverage;
}

Mocha::~Mocha()
{
	delete beverage;
}

string Mocha::getDescription()
{
	return beverage->getDescription() + ", Mocha";
}

double Mocha::cost()
{
	return 0.20 + beverage->cost();
}

Soy::Soy(Beverage* beverage)
{
	this->beverage = beverage;
}

Soy::~Soy()
{
	delete beverage;
}

string Soy::getDescription()
{
	return beverage->getDescription() + ", Soy";
}

double Soy::cost()
{
	return 0.15 + beverage->cost();
}

Whip::Whip(Beverage* beverage)
{
	this->beverage = beverage;
}

Whip::~Whip()
{
	delete beverage;
}

string Whip::getDescription()
{
	return beverage->getDescription() + ", Whip";
}

double Whip::cost()
{
	return 0.10 + beverage->cost();
}

DarkRoast::DarkRoast()
{
	description = "Dark Roast";
}

double DarkRoast::cost()
{
	return 0.99;
}

Decat::Decat()
{
	description = "Decat";
}

double Decat::cost()
{
	return 1.05;
}

void DecoratorPattern::DecoratorPatternDisplay()
{
	Beverage* beverage = new Espresso();
	cout << beverage->getDescription() + " $" + to_string(beverage->cost()) << endl;
	beverage->Eat();

	Beverage* beverage2 = new DarkRoast();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	cout << beverage2->getDescription() + " $" + to_string(beverage2->cost()) << endl;
	beverage2->Eat();

	Beverage* beverage3 = new HouseBlend();
	beverage3 = new Soy(beverage3);
	beverage3 = new Mocha(beverage3);
	beverage3 = new Whip(beverage3);
	cout << beverage3->getDescription() + " $" + to_string(beverage3->cost()) << endl;
	beverage3->Eat();
}

void Beverage::Eat()
{
	cout << "this " + getDescription() + " has been eaten.\n";
	delete this;
}
