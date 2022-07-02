#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class IIterator;

class MenuItem
{
public:
	MenuItem();
	MenuItem(
		string name,
		string description,
		bool vegetarian,
		double price
	);

	bool operator==(MenuItem* in);

public:
	string getName();
	string getDescription();
	double getPrice();
	bool isVegetarian();

private:
	string name;
	string description;
	bool vegetarian;
	double price;
};

class IMenu
{
public:
	virtual IIterator* createIterator() = 0;
};

class PancakeHouseMenu : public IMenu
{
public:
	PancakeHouseMenu();

public:
	void addItem(
		string name,
		string description,
		bool vegetarian,
		double price
	);

	// 我们不再需要这个方法
	vector<MenuItem>& getMenuItems();

	virtual IIterator* createIterator() override;

private:
	vector<MenuItem> menuItems;
};

class DinerMenu : public IMenu
{
public:
	DinerMenu();

public:
	void addItem(
		string name,
		string description,
		bool vegetarian,
		double price
	);

	// 我们不再需要这个方法
	MenuItem& getMenuItems();

	virtual IIterator* createIterator() override;

private:
	static const int MAX_ITEMS = 6;
	int numberOfItems = 0;
	MenuItem* menuItems;
};

class CafeMenu : public IMenu
{
public:
	CafeMenu();
	
public:
	void addItem(
		string name,
		string description,
		bool vegetarian,
		double price
	);

	unordered_map<string, MenuItem> getItems();

	virtual IIterator* createIterator() override;

private:
	unordered_map<string, MenuItem> menuItems;
};

class IIterator
{
public:
	virtual bool hasNext() = 0;
	virtual void* next() = 0;
};

class PancakeHouseMenuIterator : public IIterator
{
public:
	PancakeHouseMenuIterator(vector<MenuItem>&& items);

public:
	virtual bool hasNext() override;
	virtual void* next() override;

private:
	vector<MenuItem> items;
	int position = 0;
};

class DinerMenuIterator : public IIterator
{
public:
	DinerMenuIterator(MenuItem* items, int size);

public:
	virtual bool hasNext() override;
	virtual void* next() override;

private:
	MenuItem* items;
	int size;
	int position = 0;
};

class CafeMenuIterator : public IIterator
{
public:
	CafeMenuIterator(unordered_map<string, MenuItem>* items);

public:
	virtual bool hasNext() override;
	virtual void* next() override;

private:
	unordered_map<string, MenuItem>* items;
	int position = 0;
};

class Waitress
{
public:
	Waitress(vector<IMenu*>&& menus);

public:
	void printMenu();

private:
	void printMenu_Internal(IIterator* iterator);

private:
	IMenu* pancakeHouseMenu;
	IMenu* dinerMenu;
	IMenu* cafeMenu;
	vector<IMenu*> Menus;
};

class Iterator
{
public:
	static void IteratorTestFunc();
};