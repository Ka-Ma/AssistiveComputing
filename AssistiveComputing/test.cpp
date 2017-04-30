//to test how to draw my stuff to matrix

#include <stdio.h>
#include "../matrix/include/led-matrix.h" //needed to include relative dir otherwise it wouldn't compile

using rgb_matrix::RGBMatrix;

int main(int argc, char **argv) {
	// Set some defaults
	RGBMatrix::Options my_defaults;
	my_defaults.hardware_mapping = "adafruit-hat";  
	my_defaults.chain_length = 2;
	my_defaults.show_refresh_rate = true;
	my_defaults.disable_hardware_pulsing=true;
	rgb_matrix::RuntimeOptions runtime_defaults;
	runtime_defaults.drop_privileges = 1;
	RGBMatrix *matrix = rgb_matrix::CreateMatrixFromFlags(&argc, &argv,
		&my_defaults,
		&runtime_defaults);
	if (matrix == NULL) {
		//stderr not declared
		//PrintMatrixFlags(stderr, my_defaults, runtime_defaults);
		printf("Farout Errors Mann");
		return 1;
	}

	// matrix->ApplyStaticTransformer(...);  // Optional

	// Do your own command line handling with the remaining options.

	//  .. now use matrix
	// 32x64, see if this makes interestng colours on LED matrix
	for(int count = 0; count < 3000; count++){
		for (int i = 0; i < 64; i++){
			for (int j = 0; j < 32; j++){
				matrix->SetPixel(i, j, i + j, i, j);
			}
		}
	}

	delete matrix;   // Make sure to delete it in the end.
}
