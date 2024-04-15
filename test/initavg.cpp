#include "Fir1.h"
#include "assert_print.h"
#include <stdio.h>
#include <math.h>

int main (int,char**)
{
    // inits the filter
    Fir1 fir(10,0.1);
    
    // resets the delay line to zero
    fir.reset ();
    
    for(int i=0;i<30;i++) 
    {
	float a=1;
	double b = fir.filter(a);
	if (i < 10) {
	    const double a = 0.1*(i+1);
	    assert_print(fabs(b - a) < 1E-6,"Average wrongly calculated.");
	}
	if (i > 10) {
	    assert_print(fabs(b - 1.0) < 1E-6,"Average wrongly calculated.");
	}
    }
}
