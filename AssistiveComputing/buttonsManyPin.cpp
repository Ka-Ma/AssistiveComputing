#include <iostream>
#include <string>
#include "../wiringPi/wiringPi/wiringPi.h"

using namespace std;

int main(void)
{
	int count = 0;

	wiringPiSetupGpio(); //required to determine pin number

	//button 1
	pinMode(14, INPUT);
	pullUpDnControl(14, PUD_UP);

	//button 2
	pinMode(15, INPUT);
	pullUpDnControl(15, PUD_UP);

	//button 3
	pinMode(18, INPUT);
	pullUpDnControl(18, PUD_UP);

	//button 4
	pinMode(24, INPUT);
	pullUpDnControl(24, PUD_UP);

	//button 5
	pinMode(25, INPUT);
	pullUpDnControl(25, PUD_UP);

	//initial read
	cout << "button 1 is " << digitalRead(14) << endl;
	cout << "button 2 is " << digitalRead(15) << endl;
	cout << "button 3 is " << digitalRead(18) << endl;
	cout << "button 4 is " << digitalRead(24) << endl;
	cout << "button 5 is " << digitalRead(25) << endl;

	//change direction
	pullUpDnControl(14, PUD_DOWN);
	pullUpDnControl(15, PUD_DOWN);
	pullUpDnControl(18, PUD_DOWN);
	pullUpDnControl(24, PUD_DOWN);
	pullUpDnControl(25, PUD_DOWN);

	//reread
	cout << "button 1 is " << digitalRead(14) << endl;
	cout << "button 2 is " << digitalRead(15) << endl;
	cout << "button 3 is " << digitalRead(18) << endl;
	cout << "button 4 is " << digitalRead(24) << endl;
	cout << "button 5 is " << digitalRead(25) << endl;

	//change direction again
	pullUpDnControl(14, PUD_UP);
	pullUpDnControl(15, PUD_UP);
	pullUpDnControl(18, PUD_UP);
	pullUpDnControl(24, PUD_UP);
	pullUpDnControl(25, PUD_UP);

	//infinite loop for monitoring buttons
	while (1){
		cout << "count is: " << count << " pin reads are: " << digitalRead(14) << digitalRead(15) << digitalRead(18) << digitalRead(24) << digitalRead(15) << endl;
		count++;
		delay(400);

		if (digitalRead(14) == 0){
			cout << "button 1 pressed" << endl;
		}
	
		if (digitalRead(15) == 0){
			cout << "button 2 pressed" << endl;
		}

		if (digitalRead(18) == 0){
			cout << "button 3 pressed" << endl;
		}

		if (digitalRead(24) == 0){
			cout << "button 4 pressed" << endl;
		}

		if (digitalRead(25) == 0){
			cout << "button 5 pressed" << endl;
		}
		
	}
	
	
	return 0;
}