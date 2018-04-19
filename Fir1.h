/*
License: MIT License (http://www.opensource.org/licenses/mit-license.php)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/* (C) 2013-2018 Graeme Hattan & Bernd Porr */

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
	Fir1(double *coefficients, unsigned number_of_taps);

	// coefficients as a text file (for example from MATLAB)
	// The number of taps is automatically detected
	// when the taps are kept zero
	Fir1(const char* coeffFile, unsigned number_of_taps = 0);

	// init all coefficients and the buffer to zero
	// This is useful for adaptive filters where we start with
	// zero coefficients
	Fir1(unsigned number_of_taps);

	// destructor
	~Fir1();

	// the actual filter function
	double filter(double input);

	// Adaptive filter weight update
	// Every filter coefficient is updates with:
	// w_k(n+1) = w_k(n) + learning_rate * buffer_k(n) * error(n)
	// the error is calculated differently for different
	// applications such as artefact removal or system identification.
	void lms_update(double error);

	// setting the learning rate for the LMS algorithm
	void setLearningRate(double _mu) {mu = _mu;};
	double getLearningRate() {return mu;};

	// reset the buffer
	void reset();

	// returns the number of taps
	unsigned getTaps() {return taps;};

private:
	double        *coefficients = NULL;
	double        *buffer = NULL;
	unsigned      taps = 0, offset = 0;
	double        mu = 0;
};

#endif
