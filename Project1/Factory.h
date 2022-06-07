#pragma once
#include "SimpleFactory.h"


/**
* ÅûÈøÀà
*/

class NYStyleCheesePizza : public CheesePizza
{
public:
	NYStyleCheesePizza();
};

class ChicagoStyleCheesePizza : public CheesePizza
{
public:
	ChicagoStyleCheesePizza();

	virtual void cut() override;
};

class NYStyleVeggiePizza : public VeggiePizza
{
public:
	NYStyleVeggiePizza() { Name = "NYStyleVeggiePizza"; }
};

class ChicagoStyleVeggiePizza : public VeggiePizza
{
public:
	ChicagoStyleVeggiePizza() { Name = "ChicagoStyleVeggiePizza"; }
};

class NYStyleClamPizza : public ClamPizza
{
public:
	NYStyleClamPizza() { Name = "NYStyleClamPizza"; }
};

class ChicagoStyleClamPizza : public ClamPizza
{
public:
	ChicagoStyleClamPizza() { Name = "ChicagoStyleClamPizza"; }
};

class NYStylePepperoniPizza : public PepperoniPizza
{
public:
	NYStylePepperoniPizza() { Name = "NYStylePepperoniPizza"; }
};

class ChicagoStylePepperoniPizza : public PepperoniPizza
{
public:
	ChicagoStylePepperoniPizza() { Name = "ChicagoStylePepperoniPizza"; }
};


/**
* µêÆÌÀà
*/

class AbstractPizzaStore
{
public:
	IPizza* orderPizza(string type);
	virtual IPizza* createPizza(string type) = 0;
};

class NYPizzaStore : public AbstractPizzaStore
{
public:
	virtual IPizza* createPizza(string item) override;
};

class ChicagoPizzaStore : public AbstractPizzaStore
{
public:
	virtual IPizza* createPizza(string item) override;
};

class Factory
{
public:
	static void FactoryDisplay()
	{
		AbstractPizzaStore* nyStore = new NYPizzaStore();
		AbstractPizzaStore* chicagoStore = new ChicagoPizzaStore();

		string PizzaName = ENUM_TO_STRING(PizzaClass::cheese);
		PizzaName = &PizzaName[PizzaName.find("::") + 2];

		IPizza* MyPizza = nyStore->orderPizza(PizzaName);
		cout << "Ethan ordered a " + MyPizza->getName() + "\n";
		if (MyPizza)
			MyPizza->eat();
		else
			cout << "Don't have this type of Pizza!\n";

		MyPizza = chicagoStore->orderPizza(PizzaName);
		cout << "Ethan ordered a " + MyPizza->getName() + "\n";
		if (MyPizza)
			MyPizza->eat();
		else
			cout << "Don't have this type of Pizza!\n";

		delete chicagoStore;
		delete nyStore;
	}
};