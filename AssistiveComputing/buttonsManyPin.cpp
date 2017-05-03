#include <iostream>
#include <string>
#include "../wiringPi/wiringPi/wiringPi.h"

using namespace std;

int main(void)
{
	wiringPiSetupGpio();

	//button 1
	pinMode(14, INPUT);
	pullUpDnControl(14, PUD_UP);

	//button 2
	pinMode(15, INPUT);
	pullUpDnControl(15, PUD_UP);

	//infinite loop for monitoring buttons
	while (1){
		if (digitalRead(14) == 0){
			cout << "button 1 pressed" << endl;
		}
	
		if (digitalRead(15) == 0){
			cout << "button 2 pressed" << endl;
		}
		
	}
	
	//closing shop
	gpio14->unexport_gpio();
	gpio15->unexport_gpio();

	return 0;
}