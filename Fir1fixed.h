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

/* (C) 2013-2020 Graeme Hattan & Bernd Porr */

#ifndef FIR1FIXED_H
#define FIR1FIXED_H

#include <stdio.h>
#include <cmath>
#include <complex>

/**
 * Fixed point FIR filter with short int coefficients and data processed as int.
 **/
class Fir1fixed {
public:
        /**
         * Coefficients as an array of short ints (and length provided separately)
         * \param coefficients Array of the coefficients scaled up by 2^bitshift
         * \param bitshift Scaling factor of the coefficients as power of 2: 2^bitshift
         * \param number_of_taps Number of taps (= number of coefficients)
         **/
	Fir1fixed(short int *coefficients, 
		  unsigned bitshift,
		  unsigned number_of_taps);

	/**
         * Coefficients as an const array of short ints (and length automatically detected)
         * \param _coefficients Array of the coefficients (const short) scaled up by 2^bitshift
         * \param bitshift Scaling factor of the coefficients as power of 2: 2^bitshift
         **/
        template <unsigned nTaps> Fir1fixed(const short int (&_coefficients)[nTaps],
					    unsigned bitshift) :
		coefficients(new short int[nTaps]),
		buffer(new int[nTaps]),  
		taps(nTaps),
		numberOfBitsToShift(bitshift) {
			for(unsigned i = 0; i < nTaps; i++) {
				coefficients[i] = _coefficients[i];
				buffer[i] = 0;
			}
		}

	/**
	 * Coefficients as a text file (for example from MATLAB).
	 * The number of taps is automatically detected
	 * when the taps are kept zero.
         * \param coeffFile File containing the coefficients
         * \param bitshift Scaling factor of the coefficients as power of 2: 2^bitshift
         * \param number_of_taps Number of taps (= number of coefficients)
         **/
	Fir1fixed(const char* coeffFile,
		  unsigned  bitshift,
		  unsigned number_of_taps = 0);

	/**
	 * The actual filtering operation. Takes one sample and returns
	 * the filtred one with the same type. The input type is usually
	 * short int but can be also int or char if special care it taken against 
	 * overflows.
	 * \param input is the input sample of any integer type (int,short,char)
	 **/
	template <typename Sample> inline Sample filter(Sample input) {
		short int *coeff     = coefficients;
		short int *coeff_end = coefficients + taps;
		
		int *buf_val = buffer + offset;
		
		*buf_val = static_cast<Sample>(input);
		int output_ = 0;
		
		while(buf_val >= buffer)
			output_ += *buf_val-- * *coeff++;
		
		buf_val = buffer + taps-1;
		
		while(coeff < coeff_end)
			output_ += *buf_val-- * *coeff++;
		
		if(++offset >= taps)
			offset = 0;
		
		return static_cast<Sample>(output_ >> numberOfBitsToShift);
	}

	
	/**
         * Frees the buffer and coefficients
         **/
	~Fir1fixed();

	/** 
         * Resets the buffer
         **/
	void reset();

	/**
         * Returns the number of taps
         **/
	unsigned getTaps() {return taps;};
	
private:
	short int        *coefficients;
	int              *buffer;
	unsigned         taps;
	unsigned         offset = 0;
	unsigned         numberOfBitsToShift;
};

#endif
