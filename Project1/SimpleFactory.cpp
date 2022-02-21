#include "SimpleFactory.h"

IPizza* SimplePizzaFactory::createPizza(string type)
{
	IPizza* pizza = nullptr;
	if (type._Equal("cheese"))
		pizza = new CheesePizza();
	else if (type._Equal("pepperoni"))
		pizza = new PepperoniPizza();
	else if (type._Equal("clam"))
		pizza = new ClamPizza();
	else if (type._Equal("veggie"))
		pizza = new VeggiePizza();

	return pizza;
}

PizzaStore::PizzaStore(SimplePizzaFactory* factory)
{
	this->factory = factory;
}

IPizza* PizzaStore::orderPizza(string type)
{
	IPizza* pizza;

	pizza = factory->createPizza(type);
	if (pizza != nullptr)
	{
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();
	}

	return pizza;
}

IPizza::IPizza()
{
	Name = "OriginalPizza";
}

void IPizza::prepare()
{
	cout << "Preparing " + Name << endl;
	cout << "Tossing dough..." << endl;
	cout << "Adding sauce..." << endl;
	/*cout << "Adding toppings: " << endl;
	for (int i = 0; i < toppings.size(); i++)
		cout << "   " + toppings[i];*/

}

void IPizza::bake()
{
	cout << "Bake for 25 minutes at 350" << endl;
}

void IPizza::cut()
{
	cout << "Cutting the pizza into diagonal slices" << endl;
}

void IPizza::box()
{
	cout << "Place pizza in official PizzaStore box" << endl;
}

void IPizza::eat()
{
	cout << "This " + Name + " has been eaten\n";
	delete this;
}

string IPizza::getName()
{
	return Name;
}

CheesePizza::CheesePizza()
{
	Name = "CheesePizza";
}

PepperoniPizza::PepperoniPizza()
{
	Name = "PepperoniPizza";
}

ClamPizza::ClamPizza()
{
	Name = "ClamPizza";
}

VeggiePizza::VeggiePizza()
{
	Name = "VeggiePizza";
}
