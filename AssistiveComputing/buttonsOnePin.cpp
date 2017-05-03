/***********************************************************************
* Filename: Switches.c (i called it buttons.cpp KJM)
* This program demonstrates a way to simulate an analog read by measuring
* the time it takes to charge a capacitor through a resistance. It uses
* resistors in series and buttons between them.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../wiringPi/wiringPi/wiringPi.h"

int ButtonPin = 5;   // Resistors in series and capacitor connected to pin five, physical pin 18, GPIO24. (changed from zero KJM)

/***********************************************************************
* RCtime() - Function, uses a digital pin to measure resistance by first
* discharging capacitor then measuring the time it takes to charge the
* capacitor through the resistance. When the voltage rises to Vcc/2 the
* pin will go high.
***********************************************************************/
long RCtime(int RCpin)
{
	pinMode(RCpin, OUTPUT);             // Set pin to output,
	digitalWrite(RCpin, LOW);           // and pull to low.    

	delay(4);                           // Allow time to let capacitor discharge.

	long time = micros();

	pinMode(RCpin, INPUT);              // Now set the pin to an input,
	pullUpDnControl(RCpin, PUD_OFF);    // turn off internal pull down resistor,
	while (digitalRead(RCpin) == LOW);  // and wait for it to go high.

	long PinVal = micros() - time;

	return PinVal;
}

/**************************************************************************
* loop() - function runs in a continuous loop until program is stopped.
**************************************************************************/
void loop(void)
{
	long ButtonReading = RCtime(ButtonPin); // Read Buttons into ButtonReading.

	switch (ButtonReading)
	{
	case 7000 ... 8000:
	{
						  printf("%ld - No button pressed.\n", ButtonReading);
						  break;
	}
	case 6000 ... 6900:
	{
						  printf("%ld - button one pressed.\n", ButtonReading);
						  break;
	}
	case 5000 ... 5900:
	{
						  printf("%ld - button two pressed.\n", ButtonReading);
						  break;
	}
	case 3600 ... 4499:
	{
						  printf("%ld - button three pressed.\n", ButtonReading);
						  break;
	}
	case 2500 ... 2999:
	{
						  printf("%ld - button four pressed.\n", ButtonReading);
						  break;
	}
	case 1000 ... 1999:
	{
						  printf("%ld - button five pressed.\n", ButtonReading);
						  break;
	}
	}
	delay(100);
}

/***********************************************************************
* setup() - function is run by main() one time when the program starts.
***********************************************************************/
void setup(void)
{
	wiringPiSetup();   // Required.

	RCtime(ButtonPin); // Throw out first reading.
}

/***********************************************************************
* main() - required
***********************************************************************/
int main(void)
{
	setup();

	while (1)
	{
		loop();
	}
}
