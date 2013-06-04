/* Written by Graeme Hattan */

#include "Fir1.h"

#include <string.h>
#include <stdlib.h>

Fir1::Fir1(float *coefficients, unsigned taps) :
    coefficients(coefficients),
    // addition of brackets should mean the array is 
    // value-initialised to be all zeros
    buffer(new float[taps]()),  
    taps(taps),
    offset(0)
{}

// one coefficient per line
Fir1::Fir1(const char* coeffFile, unsigned taps) :
    buffer(new float[taps]()),  
    taps(taps),
    coefficients(new float[taps]),
    offset(0)
{
	FILE* f=fopen(coeffFile,"rt");
	if (!f)
	{
		fprintf(stderr,"Could not open file with coefficients.\n");
		exit(1);
	}
	
	for(int i=0;i<taps;i++)
	{
		if (fscanf(f,"%f\n",coefficients+i)<1)
		{
			fprintf(stderr,"Could not read coefficients.\n");
			exit(1);
		}
		fprintf(stderr,"%f\n",coefficients[i]);
	}
	fclose(f);
}


Fir1::~Fir1()
{
  delete[] buffer;
  delete[] coefficients;
}

float Fir1::filter(float input)
{
  float *coeff     = coefficients;
  float *coeff_end = coefficients + taps;

  float *buf_val = buffer + offset;

  *buf_val = input;
  float output_ = 0;

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
  memset(buffer, 0, taps);
  offset = 0;
}
