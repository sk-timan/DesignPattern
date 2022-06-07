#include "Factory.h"

IPizza* AbstractPizzaStore::orderPizza(string type)
{
	IPizza* pizza;
	pizza = createPizza(type);
	if (pizza != nullptr)
	{
		pizza->prepare();
		pizza->bake();
		pizza->cut();
		pizza->box();

		return pizza;
	}
	return nullptr;
}

IPizza* NYPizzaStore::createPizza(string item)
{
	IPizza* pizza = nullptr;

	if (item._Equal("cheese"))
		pizza = new NYStyleCheesePizza();
	else if (item._Equal("pepperoni"))
		pizza = new NYStylePepperoniPizza();
	else if (item._Equal("clam"))
		pizza = new NYStyleClamPizza();
	else if (item._Equal("veggie"))
		pizza = new NYStyleVeggiePizza();

	return pizza;
}

NYStyleCheesePizza::NYStyleCheesePizza()
{
	Name = "NYStyleCheesePizza";
	dough = "Thin Crust Dough";
	sauce = "Marinara Sauce";
	toppings.push_back("Grated Reggiano Cheese");
}

ChicagoStyleCheesePizza::ChicagoStyleCheesePizza()
{
	Name = "ChicagoStyle DeepDishCheesePizza";
	dough = "Extra Thick Crust Dough";
	sauce = "Plum Tomato Sauce";
	toppings.push_back("Shredded Mozzarella Cheese");
}

void ChicagoStyleCheesePizza::cut()
{
	cout << "Cutting the pizza into square slices" << endl;
}

IPizza* ChicagoPizzaStore::createPizza(string item)
{
	IPizza* pizza = nullptr;

	if (item._Equal("cheese"))
		pizza = new ChicagoStyleCheesePizza();
	else if (item._Equal("pepperoni"))
		pizza = new ChicagoStylePepperoniPizza();
	else if (item._Equal("clam"))
		pizza = new ChicagoStyleClamPizza();
	else if (item._Equal("veggie"))
		pizza = new ChicagoStyleVeggiePizza();

	return pizza;
}
