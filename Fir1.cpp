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

#include "Fir1.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

// give the filter an array of doubles for the coefficients
Fir1::Fir1(double *coefficients, unsigned number_of_taps) :
	coefficients(coefficients),
	// addition of brackets should mean the array is 
	// value-initialised to be all zeros
	buffer(new double[number_of_taps]()),  
	taps(number_of_taps),
	offset(0)
{}

// init all coefficients and the buffer to zero
Fir1::Fir1(unsigned number_of_taps) :
	coefficients(new double[number_of_taps]()),
	buffer(new double[number_of_taps]()),  
	taps(number_of_taps),
	offset(0)
{}

// one coefficient per line
Fir1::Fir1(const char* coeffFile, unsigned number_of_taps) :
	offset(0),
	taps(number_of_taps)
{
	buffer = NULL;
	coefficients = NULL;

	FILE* f=fopen(coeffFile,"rt");
	if (!f)
	{
		fprintf(stderr,"Could not open file with coefficients: %s\n",coeffFile);
		taps = 0;
		return;
	}

	if (taps == 0)
	{
		double a;
		while (fscanf(f,"%lf\n",&a)>0) taps++;
		rewind(f);
	}

	assert (taps > 0);
	
	buffer = new double[taps];
	coefficients = new double[taps];

	assert( buffer != NULL );
	assert( coefficients != NULL );

	for(int i=0;i<taps;i++)
	{
		if (fscanf(f,"%lf\n",coefficients+i)<1)
		{
			fprintf(stderr,"Could not read coefficients.\n");
			exit(1);
		}
	}
	fclose(f);
}


Fir1::~Fir1()
{
  delete[] buffer;
  delete[] coefficients;
}


void Fir1::lms_update(double error)
{
	double *coeff_p = coefficients;
	double *buff_p = buffer;

	for(int i = 0; i < taps; i++) {
		*coeff_p = *coeff_p + mu * error * *buff_p++;
		coeff_p++;
	}
}


double Fir1::filter(double input)
{
	double *coeff     = coefficients;
	double *coeff_end = coefficients + taps;

	double *buf_val = buffer + offset;

	*buf_val = input;
	double output_ = 0;
	
	while(buf_val >= buffer)
		output_ += *buf_val-- * *coeff++;
	
	buf_val = buffer + taps-1;
	
	while(coeff < coeff_end)
		output_ += *buf_val-- * *coeff++;
	
	if(++offset >= taps)
		offset = 0;
	
	return output_;
}

void Fir1::reset()
{
	memset(buffer, 0, sizeof(double)*taps);
	offset = 0;
}
