#pragma once
#include <string>
#include <vector>

using namespace std;

class IMenuComponent
{
public:
	virtual void add(IMenuComponent* menuComponent) = 0;
	virtual void remove(IMenuComponent* menuComponent) = 0;
	virtual IMenuComponent* getChild(int i) = 0;
	virtual string getName() = 0;
	virtual string getDescription() = 0;
	virtual double getPrice() = 0;
	virtual bool isVegetarian() = 0;
	virtual void print() = 0;

};

class MenuItemComponent : public IMenuComponent
{
public:
	MenuItemComponent();

	MenuItemComponent(
		string name,
		string description,
		bool vegetarian,
		double price
	);

	//bool operator==(MenuItem* in);

public:
	virtual string getName() override;
	virtual string getDescription() override;
	virtual double getPrice() override;
	virtual bool isVegetarian() override;
	virtual void print() override;
private:
	string name;
	string description;
	bool vegetarian;
	double price;
};

class Menu : public IMenuComponent
{
public:
	Menu(string name, string description);


public:
	virtual void add(IMenuComponent* menuComponent) override;
	virtual void remove(IMenuComponent* menuComponent) override;
	virtual MenuItemComponent* getChild(int i) override;
	virtual string getName() override;
	virtual string getDescription() override;
	virtual void print() override;

private:
	vector<IMenuComponent*> menuComponents;
	string name;
	string description;
};

class Composite
{

};

