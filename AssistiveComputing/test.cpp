//to test how to draw my stuff to matrix

#include <stdio.h>
#include <signal.h>
#include "../matrix/include/led-matrix.h" //needed to include relative dir otherwise it wouldn't compile
#include "threaded-canvas-manipulator.h"
#include <iostream>
#include <unistd.h> // for f_ok
#include <assert.h> // for assert
#include <errno.h> // for errors
#include <string.h>

using rgb_matrix::RGBMatrix;
using namespace std;

#define TERM_ERR "\033[1;31m"
#define TERM_NORM "\033[0m"


struct Pixel {
	Pixel() : red(0), green(0), blue(0){}
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct Image {
	Image() : width(-1), height(-1), image(NULL) {}
	~Image() { Delete(); }
	void Delete() { delete[] image; Reset(); }
	void Reset() { image = NULL; width = -1; height = -1; }
	inline bool IsValid() { return image && height > 0 && width > 0; }
	const Pixel &getPixel(int x, int y) {
		static Pixel black;
		if (x < 0 || x >= width || y < 0 || y >= height) return black;
		return image[x + width * y];
	}

	int width;
	int height;
	Pixel *image;
};


volatile bool interrupt_received = false;
static void InterruptHandler(int signo){
	interrupt_received = true;
}

// Read line, skip comments.
char *ReadLine(FILE *f, char *buffer, size_t len) {
	char *result;
	do {
		result = fgets(buffer, len, f);
	} while (result != NULL && result[0] == '#');
	return result;
}

Image LoadPPM(const char *filename) {
	cout << "loading image"<<endl;
	Image new_image_;
	
	FILE *f = fopen(filename, "r");
	// check if file exists
	if (f == NULL && access(filename, F_OK) == -1) {  //pi recognises the relevant headers included above
		cout << "it can't open the file" << endl;
		//error reports
		perror("Error opening file");
		printf("Error code opening file: %d\n", errno);
		printf("Error opening file: %s\n", strerror(errno));
		fprintf(stderr, "File \"%s\" doesn't exist\n", filename);
		//return false;
	}
	//if (f == NULL) return 0;
	cout << "starting to read file" << endl;
	char header_buf[256];
	const char *line = ReadLine(f, header_buf, sizeof(header_buf));
#define EXIT_WITH_MSG(m) { fprintf(stderr, "%s: %s |%s", filename, m, line); fclose(f);}// return false; }
	
	if (sscanf(line, "P6 ") == EOF){
		cout << "wrong file type" << endl;
		EXIT_WITH_MSG("Can only handle P6 as PPM type.");
	}
	line = ReadLine(f, header_buf, sizeof(header_buf));
	int new_width, new_height;
	if (!line || sscanf(line, "%d %d ", &new_width, &new_height) != 2){
		cout << "can't find dimensions" << endl;
		EXIT_WITH_MSG("Width/height expected");
	}
	int value;
	line = ReadLine(f, header_buf, sizeof(header_buf));
	if (!line || sscanf(line, "%d ", &value) != 1 || value != 255){
		cout << "over 255" << endl;
		EXIT_WITH_MSG("Only 255 for maxval allowed.");
	}
	const size_t pixel_count = new_width * new_height;
	cout << "got pixel count" << endl;
	Pixel *new_image = new Pixel[pixel_count];
	assert(sizeof(Pixel) == 3);   // we make that assumption.
	if (fread(new_image, sizeof(Pixel), pixel_count, f) != pixel_count) {
		line = "";
		EXIT_WITH_MSG("Not enough pixels read.");
	}
//#undef EXIT_WITH_MSG
	fclose(f);
//	fprintf(stderr, "Read image '%s' with %dx%d\n", filename,
//		new_width, new_height);
	
	//MutexLock l(&mutex_new_image_);
	new_image_.Delete();  // in case we reload faster than is picked up
	new_image_.image = new_image;
	new_image_.width = new_width;
	new_image_.height = new_height;
	return new_image_;
}




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
	//testing opening file
	//FILE * test;
	//test = fopen("I-AM-HERE", "w");
	//fputs("testing test", test);
	//if (test == NULL){ 
	//	cout << "YOU SUCK" << endl;

	//	//error reports
	//	perror("Error opening file");
	//	printf("Error code opening file: %d\n", errno);
	//	printf("Error opening file: %s\n", strerror(errno));
	//	exit(-1);
	//	
	//	fclose(test); 
	//}
	
	cout<<"going to load image"<<endl;

	//read in ppm to canvas
	Image loaded = LoadPPM("MenuBlack.ppm");
	cout<<"Theoretically an image was loaded\n"<<endl;
	cout<<"image width = "<< loaded.width<<" image height = "<<loaded.height<<endl;


	//  .. now use matrix
	// 32x64, see if this makes interestng colours on LED matrix
	while(!interrupt_received){
		//send image to screen
		for (int i = 0; i < loaded.width; i++){
			printf("line %d\n", i);
			for (int j = 0; j < loaded.height; j++){
				matrix->SetPixel(i, j,loaded.getPixel(i,j).red, loaded.getPixel(i,j).green, loaded.getPixel(i,j).blue);
			}
		}
	}

	signal(SIGTERM, InterruptHandler);
	signal(SIGINT, InterruptHandler);

	delete matrix;   // Make sure to delete it in the end.
}
