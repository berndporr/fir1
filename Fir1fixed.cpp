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

/* (C) 2013 Graeme Hattan & Bernd Porr */

#include "Fir1fixed.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

Fir1fixed::Fir1fixed(short int *coefficients,
		     unsigned bitshift,
		     unsigned number_of_taps) :
	coefficients(coefficients),
	// addition of brackets should mean the array is 
	// value-initialised to be all zeros
	buffer(new short int[number_of_taps]()),  
	taps(number_of_taps),
	offset(0),
	numberOfBitsToShift(bitshift)
{}

// one coefficient per line
Fir1fixed::Fir1fixed(const char* coeffFile, 
		     unsigned bitshift,
		     unsigned number_of_taps) :
	offset(0),
	taps(number_of_taps),
	numberOfBitsToShift(bitshift)
{
	buffer = NULL;
	coefficients = NULL;

	FILE* f=fopen(coeffFile,"rt");
	if (!f)
	{
		char tmp[256];
		sprintf(tmp,"Could not read the coefficients from %s\n",coeffFile);
		taps = 0;
		throw std::invalid_argument(tmp);
	}

	if (taps == 0)
	{
		float a;
		while (fscanf(f,"%f\n",&a)>0) taps++;
		rewind(f);
	}

	assert (taps > 0);
	
	buffer = new short int[taps];
	coefficients = new short int[taps];

	assert( buffer != NULL );
	assert( coefficients != NULL );

	for(int i=0;i<taps;i++)
	{
		float a;
		// we scan  first as float because C gets
		// upset with numbers written as 6E2.
		if (fscanf(f,"%f\n",&a)<1)
		{
			char tmp[256];
			sprintf(tmp,"Could not read the coefficients from %s\n",coeffFile);
			taps = 0;
			throw std::invalid_argument(tmp);
		}
		coefficients[i] = (short int)(a);
	}
	fclose(f);
}


Fir1fixed::~Fir1fixed()
{
  delete[] buffer;
  delete[] coefficients;
}

short int Fir1fixed::filter(short int input)
{
	short int *coeff     = coefficients;
	short int *coeff_end = coefficients + taps;

	short int *buf_val = buffer + offset;

	*buf_val = input;
	int output_ = 0;
	
	while(buf_val >= buffer)
		output_ += *buf_val-- * *coeff++;
	
	buf_val = buffer + taps-1;
	
	while(coeff < coeff_end)
		output_ += *buf_val-- * *coeff++;
	
	if(++offset >= taps)
		offset = 0;
	
	return output_ >> numberOfBitsToShift;
}

void Fir1fixed::reset()
{
	memset(buffer, 0, sizeof(short int)*taps);
	offset = 0;
}
