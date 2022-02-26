#pragma once
#include "StrategyPattern.h"
#include "Observer.h"
#include "Decorator.h"
#include "SimpleFactory.h"

int main()
{
	StrategyPattern::StrategyPatternDisplay();
	Observer::ObserverTest();
	DecoratorPattern::DecoratorPatternDisplay();
	//StrategyPattern::StrategyPatternDisplay();
	//Observer::ObserverTest();
	SimpleFactory::SimpleFactoryDisplay();
}