// Usage Examples
//

// This is the only include you need
#include "Fir1.h"

#include <stdio.h>

const double lp[] = {
	-0.00105964, -0.0011159 , -0.00122684, -0.00136109, -0.00146365,
	-0.00145803, -0.00125073, -0.00073776,  0.00018711,  0.00162305,
        0.00365256,  0.0063323 ,  0.00968525,  0.01369476,  0.01830123,
        0.02340178,  0.02885309,  0.03447726,  0.04007059,  0.04541448,
        0.05028793,  0.05448067,  0.05780599,  0.0601124 ,  0.06129316,
        0.06129316,  0.0601124 ,  0.05780599,  0.05448067,  0.05028793,
        0.04541448,  0.04007059,  0.03447726,  0.02885309,  0.02340178,
        0.01830123,  0.01369476,  0.00968525,  0.0063323 ,  0.00365256,
        0.00162305,  0.00018711, -0.00073776, -0.00125073, -0.00145803,
	-0.00146365, -0.00136109, -0.00122684, -0.0011159 , -0.00105964
};

int main (int,char**)
{
	// inits the filter
	Fir1 fir(lp);

	// gets the number of taps
	int taps = fir.getTaps();

	printf("taps = %d\n",taps);

	FILE *finput = fopen("ecg50hz.dat","rt");
	FILE *foutput = fopen("ecg_filtered.dat","wt");
	for(int i=0;i<10000;i++) 
	{
		double a;
		if (fscanf(finput,"%lf\n",&a)<1) break;
		a = fir.filter(a);
		fprintf(foutput,"%f\n",a);
	}
	fclose(finput);
	fclose(foutput);
	fprintf(stderr,"Written the filtered ECG to 'ecg_filtered.dat'\n");
}
