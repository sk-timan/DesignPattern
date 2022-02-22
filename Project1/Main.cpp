#pragma once
#include "StrategyPattern.h"
#include "Observer.h"
#include "Decorator.h"

int main()
{
	StrategyPattern::StrategyPatternDisplay();
	Observer::ObserverTest();
	DecoratorPattern::DecoratorPatternDisplay();
}