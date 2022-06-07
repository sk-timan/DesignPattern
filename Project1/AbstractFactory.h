#pragma once
#include "Factory.h"

/**
* 调料类
*/

class Dough { public: string Name; };
class Sauce { public: string Name; };
class Cheese { public: string Name; };
class Veggies { public: string Name; };
class Pepperoni { public: string Name; };
class Clams { public: string Name; };

class ThinCrustDough : public Dough
{
public:
	ThinCrustDough() { this->Name = "ThinCrustDough"; };
};

class MarinaraSauce : public Sauce
{
public:
	MarinaraSauce() { this->Name = "MarinaraSauce"; };
};

class ReggianoCheese : public Cheese
{
public:
	ReggianoCheese() { this->Name = "ReggianoCheese"; };
};


class Garlic : public Veggies
{
public:
	Garlic() { this->Name = "Garlic"; };
};

class Onion : public Veggies
{
public:
	Onion() { this->Name = "Onion"; };
};

class Mushroom : public Veggies
{
public:
	Mushroom() { this->Name = "Mushroom"; };
};

class RedPepper : public Veggies
{
public:
	RedPepper() { this->Name = "RedPepper"; };
};

class SlicedPepperoni : public Pepperoni
{
public:
	SlicedPepperoni() { this->Name = "SlicedPepperoni"; };
};

class FreshClams : public Clams
{
public:
	FreshClams() { this->Name = "FreshClams"; };
};

/**
* 工厂类
*/

class IPizzaIngredientFactory
{
public:
	virtual Dough& CreateDough() = 0;
	virtual Sauce& CreateSaouce() = 0;
	virtual Cheese& CreateCheese() = 0;
	virtual vector<Veggies>& CreateVeggies() = 0;
	virtual Pepperoni& CreatePepperoni() = 0;
	virtual Clams& CreateClams() = 0;
};

class NYPizzaIngredientFactory : public IPizzaIngredientFactory
{
public:
	virtual Dough& CreateDough() override;
	virtual Sauce& CreateSaouce() override;
	virtual Cheese& CreateCheese() override;
	virtual vector<Veggies>& CreateVeggies() override;
	virtual Pepperoni& CreatePepperoni() override;
	virtual Clams& CreateClams() override;
};

// 新一代进阶披萨，指定纯正风味，来自正宗的原料工厂，严格把关每一道制作工艺
class IPizzaBase : public IPizza
{
public:

	string toString();
	void setName(string name);

public:
	Dough DoughBase;
	Sauce SauceBase;
	vector<Veggies> VeggiesBase;
	Cheese CheeseBase;
	Pepperoni PepperoniBase;
	Clams ClamBase;

};

class CheesePizzaBase : public IPizzaBase
{
public:
	CheesePizzaBase(IPizzaIngredientFactory* indgredientFactory);

	virtual void prepare() override;

public:
	IPizzaIngredientFactory* indgredientFactory;
};

class VeggiePizzaBase : public IPizzaBase
{
public:
	VeggiePizzaBase(IPizzaIngredientFactory* indgredientFactory);

	virtual void prepare() override;

public:
	IPizzaIngredientFactory* indgredientFactory;
};

class ClamPizzaBase : public IPizzaBase
{
public:
	ClamPizzaBase(IPizzaIngredientFactory* indgredientFactory);

	virtual void prepare() override;

public:
	IPizzaIngredientFactory* indgredientFactory;
};

class PepperoniPizzaBase : public IPizzaBase
{
public:
	PepperoniPizzaBase(IPizzaIngredientFactory* indgredientFactory);

	virtual void prepare() override;

public:
	IPizzaIngredientFactory* indgredientFactory;
};

// 全新披萨店上线，在保证纯正工艺的基础上，拥有各种本地风味可供选择
class NewNYPizzaStore : public NYPizzaStore
{
protected:
	virtual IPizzaBase* createPizza(string item) override;
};

class AbstractFactory
{
public:
	static void AbstractFactoryDisplay()
	{
		AbstractPizzaStore* nyStore = new NewNYPizzaStore();

		string PizzaName = ENUM_TO_STRING(PizzaClass::veggie);
		PizzaName = &PizzaName[PizzaName.find("::") + 2];

		IPizza* MyPizza = nyStore->orderPizza(PizzaName);
		cout << "Ethan ordered a " + MyPizza->getName() + "\n";
		if (MyPizza)
			MyPizza->eat();
		else
			cout << "Don't have this type of Pizza!\n";

		delete nyStore;
	}
};