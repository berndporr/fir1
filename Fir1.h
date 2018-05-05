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

class Fir1
{
public:
	// Coefficients as double floats and the number of taps
	Fir1(double *coefficients, unsigned number_of_taps);

	// Coefficients as a text file (for example from Python)
	// The number of taps is automatically detected
	// when the taps are kept zero.
	Fir1(const char* coeffFile, unsigned number_of_taps = 0);

	// Inits all coefficients and the buffer to zero
	// This is useful for adaptive filters where we start with
	// zero valued coefficients.
	Fir1(unsigned number_of_taps);

	// destructor
	~Fir1();

	// the actual filter function
	double filter(double input);

	// Adaptive filter weight update:
	// every filter coefficient is updated with:
	// w_k(n+1) = w_k(n) + learning_rate * buffer_k(n) * error(n)
	void lms_update(double error);

	// Setting the learning rate for the adaptive filter
	void setLearningRate(double _mu) {mu = _mu;};
	// Getting the learning rate for the adaptive filter
	double getLearningRate() {return mu;};

	// Resets the buffer (but not the coefficients)
	void reset();

	// Sets all coefficients to zero
	void zeroCoeff();

	// returns the number of taps
	unsigned getTaps() {return taps;};

	// Returns the power of the of the buffer content:
	// sum_k buffer[k]^2
	// which is needed to implement a normalised LMS algorithm
	double getTapInputPower();

private:
	double        *coefficients = NULL;
	double        *buffer = NULL;
	unsigned      taps = 0, offset = 0;
	double        mu = 0;
};

#endif
