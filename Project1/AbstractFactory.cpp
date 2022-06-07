#include "AbstractFactory.h"

Dough& NYPizzaIngredientFactory::CreateDough()
{
	return *new ThinCrustDough();
}

Sauce& NYPizzaIngredientFactory::CreateSaouce()
{
	return *new MarinaraSauce();
}

Cheese& NYPizzaIngredientFactory::CreateCheese()
{
	return *new ReggianoCheese();
}

vector<Veggies>& NYPizzaIngredientFactory::CreateVeggies()
{
	//vector<Veggies> veggies{ *new Garlic(),Onion(),Mushroom(),RedPepper() };
	Garlic* a = new Garlic();
	vector<Veggies>* veggies = new vector<Veggies>{ Onion(),Mushroom(),RedPepper() };
	veggies->push_back(*a);
	delete a;
	return *veggies;
}

Pepperoni& NYPizzaIngredientFactory::CreatePepperoni()
{
	return *new SlicedPepperoni();
}

Clams& NYPizzaIngredientFactory::CreateClams()
{
	return *new FreshClams();
}

string IPizzaBase::toString()
{
	return "This is a/an " + getName();
}

void IPizzaBase::setName(string name)
{
	this->Name = name;
}

CheesePizzaBase::CheesePizzaBase(IPizzaIngredientFactory* indgredientFactory)
{
	this->indgredientFactory = indgredientFactory;
}

void CheesePizzaBase::prepare()
{
	cout << "Preparing " + getName() << endl;
	DoughBase = indgredientFactory->CreateDough();
	cout << "Add " + DoughBase.Name << endl;
	SauceBase = indgredientFactory->CreateSaouce();
	cout << "Add " + SauceBase.Name << endl;
	CheeseBase = indgredientFactory->CreateCheese();
	cout << "Add " + CheeseBase.Name << endl;

}

ClamPizzaBase::ClamPizzaBase(IPizzaIngredientFactory* indgredientFactory)
{
	this->indgredientFactory = indgredientFactory;
}

void ClamPizzaBase::prepare()
{
	cout << "Preparing " + getName() << endl;
	DoughBase = indgredientFactory->CreateDough();
	SauceBase = indgredientFactory->CreateSaouce();
	CheeseBase = indgredientFactory->CreateCheese();
	ClamBase = indgredientFactory->CreateClams();

}

IPizzaBase* NewNYPizzaStore::createPizza(string item)
{
	IPizzaBase* pizza = nullptr;
	IPizzaIngredientFactory* PizzaIngredientFactory = new NYPizzaIngredientFactory();

	if (item._Equal("cheese"))
	{
		pizza = new CheesePizzaBase(PizzaIngredientFactory);
		pizza->setName("New York Style Cheese Pizza");
	}
	else if (item._Equal("veggie"))
	{
		pizza = new VeggiePizzaBase(PizzaIngredientFactory);
		pizza->setName("New York Style Veggie Pizza");
	}
	else if (item._Equal("clam"))
	{
		pizza = new ClamPizzaBase(PizzaIngredientFactory);
		pizza->setName("New York Style Clam Pizza");
	}
	else if (item._Equal("pepperoni"))
	{
		pizza = new PepperoniPizzaBase(PizzaIngredientFactory);
		pizza->setName("New York Style Pepperoni Pizza");
	}

	return pizza;
}

VeggiePizzaBase::VeggiePizzaBase(IPizzaIngredientFactory* indgredientFactory)
{
	this->indgredientFactory = indgredientFactory;
}

void VeggiePizzaBase::prepare()
{
	cout << "Preparing " + getName() << endl;
	DoughBase = indgredientFactory->CreateDough();
	SauceBase = indgredientFactory->CreateSaouce();
	VeggiesBase = indgredientFactory->CreateVeggies();
	for (Veggies veg : VeggiesBase)
		cout << "Add " + veg.Name << endl;

}

PepperoniPizzaBase::PepperoniPizzaBase(IPizzaIngredientFactory* indgredientFactory)
{
	this->indgredientFactory = indgredientFactory;
}

void PepperoniPizzaBase::prepare()
{
	cout << "Preparing " + getName() << endl;
	DoughBase = indgredientFactory->CreateDough();
	VeggiesBase = indgredientFactory->CreateVeggies();
}

