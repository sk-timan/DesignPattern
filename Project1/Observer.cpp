#include "Observer.h"
#include <iostream>

void IObserver::update(float temp, float humidity, float pressure)
{
}

WeatherDate::WeatherDate()
{
	//observers.push_back(new IObserver());
}

void WeatherDate::registerObserver(IObserver* observer)
{
	observers.push_back(observer);
}

void WeatherDate::removeObserver(IObserver* observer)
{
	vector<IObserver*>::iterator iter = find(observers.begin(), observers.end(), observer);
	if (iter == observers.end())
		return;
	else
	{
		int index = distance(observers.begin(), iter);
		if (index >= 0)
			observers.erase(iter);
	}
}

void WeatherDate::notifyObserver()
{
	for (int i = 0; i < observers.size(); i++)
	{
		IObserver* obs = observers[i];
		obs->update(temperature,humidity,pressure);
	}
}

void WeatherDate::measurementsChanged()
{
	notifyObserver();
}

void WeatherDate::setMeasurements(float temperature, float humidity, float pressure)
{
	this->temperature = temperature;
	this->humidity = humidity;
	this->pressure = pressure;
	measurementsChanged();
}

CurrentConditionsDisplay::CurrentConditionsDisplay(ISubject* weatherData)
{
	this->weatherData = weatherData;
	weatherData->registerObserver(this);
}

void CurrentConditionsDisplay::update(float temperature, float humidity, float pressure)
{
	this->temperature = temperature;
	this->humidity = humidity;
	display();

}

void CurrentConditionsDisplay::display()
{
	cout << "Current conditions: " << temperature << " F degrees and " << "s% humidity"
		<< humidity;
}
