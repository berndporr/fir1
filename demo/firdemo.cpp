// Floating point example
//

// This is the only include you need
#include "Fir1.h"

#include <stdio.h>

int main (int,char**)
{
	// inits the filter
	Fir1 fir("coefficients.dat");

	// resets the delay line to zero
	fir.reset ();
      
	// gets the number of taps
	int taps = fir.getTaps();

	printf("Number of taps = %d\n",taps);

	FILE* fin = fopen("ecg50hz.dat","rt");
	FILE* fout = fopen("ecg_filtered.dat","wt");
	for(;;) 
	{
	    float a;
	    if (fscanf(fin,"%f\n",&a) < 1) break;
	    a = (a - 2048.0) / 2048.0;
	    const float b = fir.filter(a);
	    fprintf(fout,"%f\n",b);
	}
	fclose(fin);
	fclose(fout);
	fprintf(stderr,"Written filtered ECG to ecg_filtered.dat.\n");
}
