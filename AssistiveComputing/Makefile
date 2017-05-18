# Assistive Computing Makefile to compile our project on Raspberry Pi
# -Wall is Warning option, -O3 is an optimisation level, -g is a debugging option
CFLAGS=-Wall -O3 -g 
#-I/$(RGB_INCDIR) -I/$(RGB_LIBDIR)
CXXFLAGS=$(CFLAGS)
OBJECTS=test.o buttonsOnePin.o buttonsManyPin.o
BINARIES=test buttonsOnePin buttonsManyPin

# Where our library resides. You mostly only need to change the
# RGB_LIB_DISTRIBUTION, this is where the library is checked out.
RGB_LIB_DISTRIBUTION=../matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

all: $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

test: $(RGB_LIBRARY)
	@echo "making test"
	$(CXX) $(CFLAGS) $< test.cpp -o $@ $(LDFLAGS) -I/$(RGB_INCDIR)
	@echo "made test"
	
buttonsOnePin: 
	@echo "making buttonsOnePin"
	$(CXX) -o buttonsOnePin -I/../wiringPi/wiringPi/ -L/../wiringPi/wiringPi/ -lwiringPi buttonsOnePin.cpp
	@echo "made buttons"
	
buttonsManyPin: 
	@echo "making buttonsManyPin"
	$(CXX) -o buttonsManyPin -I/../wiringPi/wiringPi/ -L/../wiringPi/wiringPi/ -lwiringPi buttonsManyPin.cpp
	@echo "made buttons"

clean:
	rm -f $(OBJECTS) $(BINARIES)

FORCE:
.PHONY: FORCE clean
