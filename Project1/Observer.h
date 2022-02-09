#pragma once
#include <array>
#include <vector>

using namespace std;

class IObserver
{
public:
	virtual void update(float temperature, float humidity, float pressure);

};

class ISubject
{
public:
	virtual void registerObserver(IObserver* observer) = 0;
	virtual void removeObserver(IObserver* observer) = 0;
	virtual void notifyObserver() = 0;

};

class IDisplayElement
{
public:
	virtual void display() = 0;

};

class WeatherDate : public ISubject
{
public:
	WeatherDate();

	virtual void registerObserver(IObserver* observer) override;
	virtual void removeObserver(IObserver* observer) override;
	virtual void notifyObserver() override;

	void measurementsChanged();
	void setMeasurements(float temperature, float humidity, float pressure);

private:
	vector<IObserver*> observers;
	float temperature = 0;
	float humidity = 0;
	float pressure = 0;

};

class CurrentConditionsDisplay : public IObserver, IDisplayElement
{
public:
	CurrentConditionsDisplay(ISubject* weatherData);

	virtual void update(float temp, float humidity, float pressure) override;
	virtual void display() override;

private:
	float temperature = 0;
	float humidity = 0;
	ISubject* weatherData;

};