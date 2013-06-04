#ifndef FIR1_H
#define FIR1_H

#include <stdio.h>
#include <cmath>
#include <complex>

class Fir1
{
public:
	// coefficients as floating point
	// if the taps are left zero the program counts
	// the number of coefficients by itself.
	Fir1(float *coefficients, unsigned taps);

	// coefficients as a text file (for example from MATLAB)
	Fir1(const char* coeffFile, unsigned filtertaps = 0);

	// destructor
	~Fir1();

	// the actual filter function
	float filter(float input);

	// reset the buffer
	void reset();
	
private:
	float        *coefficients;
	float        *buffer;
	unsigned      taps, offset;
	
};

#endif
