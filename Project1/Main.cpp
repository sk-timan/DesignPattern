#pragma once
#include "test.h"
//#include <stdio>


void main()
{
	/*test::origin = ("owoztneoer");
	test T;
	printf("The real number = %d",T.originalDigits(test::origin));*/

	Duck* mallard = new MallardDuck();
	mallard->performQuack();
	mallard->performFly();
	mallard->Display();

	mallard = new ModelDuck();
	mallard->performFly();
	mallard->setFlyBehavior(new IFlyRocketPowered());
	mallard->performFly();

}