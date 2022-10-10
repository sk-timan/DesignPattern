#include "Composite.h"
#include <iostream>

MenuItemComponent::MenuItemComponent()
{
}

MenuItemComponent::MenuItemComponent(string name, string description, bool vegetarian, double price)
{
	this->name = name;
	this->description = description;
	this->vegetarian = vegetarian;
	this->price = price;

}

string MenuItemComponent::getName()
{
	return name;
}

string MenuItemComponent::getDescription()
{
	return description;
}

double MenuItemComponent::getPrice()
{
	return price;
}

bool MenuItemComponent::isVegetarian()
{
	return vegetarian;
}

void MenuItemComponent::print()
{
	cout << " " << getName();
	if (isVegetarian())
		cout << "(v)";

	cout << ", " << getPrice() << endl;
	cout << "   -- " << getDescription() << endl;
}

Menu::Menu(string name, string description)
{
	this->name = name;
	this->description = description;
}

void Menu::add(IMenuComponent* menuComponent)
{
	menuComponents.push_back(menuComponent);
}

void Menu::remove(IMenuComponent* menuComponent)
{
	//menuComponents.
}
