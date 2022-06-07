#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define ENUM_TO_STRING(x) #x

enum class PizzaClass
{
	cheese,
	pepperoni,
	clam,
	veggie
};

class IPizza
{
public:
	IPizza();

	virtual void prepare();
	virtual void bake();
	virtual void cut();
	virtual void box();
	virtual void eat();

public:
	string getName();

public:
	string Name;
	string dough;
	string sauce;
	vector<string> toppings;
};

class CheesePizza : public IPizza
{
public:
	CheesePizza();

};

class PepperoniPizza : public IPizza
{
public:
	PepperoniPizza();
};

class ClamPizza : public IPizza
{
public:
	ClamPizza();
};

class VeggiePizza : public IPizza
{
public:
	VeggiePizza();
};

class SimplePizzaFactory
{
public:
	IPizza* createPizza(string type);
};

class PizzaStore
{
public:
	PizzaStore(SimplePizzaFactory* factory);

	IPizza* orderPizza(string type);

private:
	SimplePizzaFactory* factory;
};

class SimpleFactory
{
public:
	static void SimpleFactoryDisplay()
	{
		SimplePizzaFactory* MySimpleFactory = new SimplePizzaFactory();
		PizzaStore* MyPizzaStore = new PizzaStore(MySimpleFactory);
		string PizzaName = ENUM_TO_STRING(PizzaClass::clam);
		PizzaName = &PizzaName[PizzaName.find("::") + 2];
		IPizza* MyPizza = MyPizzaStore->orderPizza(PizzaName);
		if (MyPizza)
			MyPizza->eat();
		else
			cout << "Don't have this type of Pizza!\n";

		delete MyPizzaStore;
		delete MySimpleFactory;
	}
};