//stub

#include <iostream>
#include "led-matrix.h"
#include "threaded-canvas-manipulator.h"
#include "transformer.h"
#include "graphics.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <algorithm>

// Types exported by the RGB-Matrix library.
using rgb_matrix::Canvas;
using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;

using namespace std;
using namespace rbb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
	interrupt_received = true;
}

int main()
{
	//setup LED Matrix

	//setup Buttons

	//display screen
	//read button
	//act on button read depending on current screen

	cout << "This program will run the LED Matrix" << endl;
	
	//to make the console not disappear at conclusion of debug put a breakpoint here.

	
	RGBMatrix::Options matrix_options;
	rgb_matrix::RuntimeOptions runtime_opt;
	RGBMatrix *matrix = CreateMatrixFromOptions(matrix_options, runtime_opt);
	Canvas *canvas = matrix;
		
	

	
	
	return 0;
}
