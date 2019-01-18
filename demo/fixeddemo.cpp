// Usage Examples
//
// This shows you how to operate the filters
// fixed preceision
// the ADC data has 12 bits
// the number of taps is 1000 = 10 bits
// the coefficients have 12 bits
// 34 bits (!) in the accumulator which works because
// the gain of the filter is 1 and we get only a temporary
// overflow while we add up the coefficients.
//

// This is the only include you need
#include "Fir1fixed.h"

#include <stdio.h>

int main (int,char**)
{
	// inits the filter
	Fir1fixed fir("coeff12bit.dat",12);

	// resets the delay line to zero
	fir.reset ();
      
	// gets the number of taps
	int taps = fir.getTaps();

	printf("taps = %d\n",taps);

	FILE *finput = fopen("ecg50hz.dat","rt");
	FILE *foutput = fopen("ecg_filtered.dat","wt");
	for(int i=0;i<10000;i++) 
	{
		float a;
		// we scan as float because the %d gets confused
                // with 6E2 which is outputted by octave
		if (fscanf(finput,"%f\n",&a)<1) break;
		short int b = fir.filter((short int)a);
		fprintf(foutput,"%f\n",(float)b);
	}
	fclose(finput);
	fclose(foutput);
	fprintf(stderr,"Written the filtered ECG to 'ecg_filtered.dat'\n");
}
