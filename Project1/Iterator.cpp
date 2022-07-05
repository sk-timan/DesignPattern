#include "Iterator.h"
#include <iostream>

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(string name, string description, bool vegetarian, double price)
{
	this->name = name;
	this->description = description;
	this->vegetarian = vegetarian;
	this->price = price;
}

bool MenuItem::operator==(MenuItem* in)
{
	if (in == nullptr)
	{
		if (name == "")
			return true;
		else
			return false;
	}
	
	else
		if (this->name == in->name
			&& this->description == in->description
			&& this->vegetarian == in->vegetarian
			&& this->price == in->price)
		{
			return true;
		}
		else
			return false;
}

string MenuItem::getName()
{
	return name;
}

string MenuItem::getDescription()
{
	return description;
}

double MenuItem::getPrice()
{
	return price;
}

bool MenuItem::isVegetarian()
{
	return vegetarian;
}

PancakeHouseMenu::PancakeHouseMenu()
{
	addItem("K&B's Pancake Breakfast",
		"Pancakes with scrambled eggs",
		true,
		2.99);

	addItem("Regular Pancake Breakfast",
		"Pancakes with fried eggs, sausage",
		false,
		2.99);

	addItem("Blueberry Pancakes",
		"Pancakes made with fresh blueberries",
		true,
		3.49);

	addItem("Waffles",
		"Waffles, with your choice of blueberries or strawberries",
		true,
		3.59);
}

void PancakeHouseMenu::addItem(string name, string description, bool vegetarian, double price)
{
	menuItems.push_back(MenuItem(name, description, vegetarian, price));
}

vector<MenuItem>& PancakeHouseMenu::getMenuItems()
{
	return menuItems;
}

IIterator* PancakeHouseMenu::createIterator()
{
	return new PancakeHouseMenuIterator(move(menuItems));
}

DinerMenu::DinerMenu()
{
	menuItems = new MenuItem[MAX_ITEMS];

	addItem("Vegetarian BLT",
		"(Fakin') Bacon with lettuce & tomato on whole wheat",
		true,
		2.99);

	addItem("BLT",
		"Bacon with lettuce & tomato on whole wheat",
		false,
		2.99);

	addItem("Soup of the day",
		"Soup of the day, with a side of potato salad",
		false,
		3.99);

	addItem("Hotdog",
		"A hot dog, with saurkraut, relish, onions, topped with cheese",
		false,
		3.05);
}

void DinerMenu::addItem(string name, string description, bool vegetarian, double price)
{
	if (numberOfItems >= MAX_ITEMS)
		cout << "Sorry, menu is full! Can't add item to menu\n";
	else
	{
		menuItems[numberOfItems] = MenuItem(name, description, vegetarian, price);
		numberOfItems += 1;
	}
}

MenuItem& DinerMenu::getMenuItems()
{
	return *menuItems;
}

IIterator* DinerMenu::createIterator()
{
	return new DinerMenuIterator(menuItems, MAX_ITEMS);
}

DinerMenuIterator::DinerMenuIterator(MenuItem* items, int size)
{
	this->items = items;
	this->size = size;
}

bool DinerMenuIterator::hasNext()
{
	if (position >= size || items[position] == nullptr)
		return false;
	else
		return true;
}

void* DinerMenuIterator::next()
{
	MenuItem* menuItem = &items[position];
	position += 1;

	return menuItem;
}

PancakeHouseMenuIterator::PancakeHouseMenuIterator(vector<MenuItem>&& items)
{
	this->items = items;
}

bool PancakeHouseMenuIterator::hasNext()
{
	if (position >= items.size() || items[position] == nullptr)
		return false;
	else
		return true;
}

void* PancakeHouseMenuIterator::next()
{
	MenuItem* menuItem = &items[position];
	position += 1;

	return menuItem;
}

Waitress::Waitress(vector<IMenu*>& menus)
{
	/*this->pancakeHouseMenu = pancakeHouseMenu;
	this->dinerMenu = dinerMenu;
	this->cafeMenu = cafeMenu;*/

	Menus = menus;
	cout << &menus << endl;
	cout << &Menus << endl;
}

void Waitress::printMenu()
{
	/*IIterator* pancakeIterator = pancakeHouseMenu->createIterator();
	IIterator* dinerIterator = dinerMenu->createIterator();
	IIterator* cafeIterator = cafeMenu->createIterator();*/
	
	/*cout << "MENU\n---\nBREAKFAST" << endl;
	printMenu_Internal(pancakeIterator);
	cout << "\nLUNCH" << endl;
	printMenu_Internal(dinerIterator);
	cout << "\nCAFE" << endl;
	printMenu_Internal(cafeIterator);*/

	vector<IMenu*>::iterator iter;
	for (iter = Menus.begin(); iter < Menus.end(); iter++)
	{
		printMenu_Internal((*iter)->createIterator());
	}

}

void Waitress::printMenu_Internal(IIterator* iterator)
{
	while (iterator->hasNext())
	{
		MenuItem* menuItem = (MenuItem*)iterator->next();
		cout << menuItem->getName() + ", ";
		cout << to_string(menuItem->getPrice()) + " -- ";
		cout << menuItem->getDescription() << endl;
	}
}

void Iterator::IteratorTestFunc()
{
	PancakeHouseMenu* pancakeHouseMenu = new PancakeHouseMenu();
	DinerMenu* dinerMenu = new DinerMenu();
	CafeMenu* cafeMenu = new CafeMenu();
	vector<IMenu*> menus = { pancakeHouseMenu,dinerMenu,cafeMenu };
	/*vector<IMenu*> menus2 = move(menus);
	Waitress* waitress = new Waitress(move(menus2));
	string a = "abc";
	string b = move(a);

	int* A = new int ;
	vector<int*> integer = { A,new int(2),new int(3) };
	vector<int*> intergerteam = move(integer);*/

	Waitress* waitress = new Waitress(menus);

	waitress->printMenu();
}

CafeMenu::CafeMenu()
{
	addItem("Veggie Burger and Air Fries",
		"Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
		true,
		3.99);

	addItem("Soup of the day",
		"Soup of the day, with a side salad",
		false,
		3.69);

	addItem("Burrito",
		"A large burrito, with whole pinto beans, salsa, guacamole",
		true,
		4.29);
}

void CafeMenu::addItem(string name, string description, bool vegetarian, double price)
{
	menuItems.insert(pair<string, MenuItem>(name, MenuItem(name, description, vegetarian, price)));
}

unordered_map<string, MenuItem> CafeMenu::getItems()
{
	return menuItems;
}

IIterator* CafeMenu::createIterator()
{
	return new CafeMenuIterator(&menuItems);
}

CafeMenuIterator::CafeMenuIterator(unordered_map<string, MenuItem>* items)
{
	this->items = items;
}

bool CafeMenuIterator::hasNext()
{
	if (position >= items->size())
		return false;
	else
		return true;
}

void* CafeMenuIterator::next()
{
	int i = 0;
	for (auto& item : *items)
	{
		if (position == i)
		{
			MenuItem* menuItem = &item.second;
			position += 1;
			return menuItem;
		}

		i++;
	}

	return nullptr;
}
