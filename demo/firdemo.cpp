// Usage Examples
//
// This shows you how to operate the filters
//

// This is the only include you need
#include "Fir1.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>

int main (int,char**)
{
	const int taps = 1000;

	Fir1 f("coefficients.dat");

	f.reset ();

	FILE *fimpulse = fopen("impulse.dat","wt");
	for(int i=0;i<taps*2;i++) 
	{
		float a=0;
		if (i==10) a = 1;
		float b = f.filter(a);
		fprintf(fimpulse,"%f\n",b);
	}
	fclose(fimpulse);
	
}
