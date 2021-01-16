// Floating point example
//

// This is the only include you need
#include "Fir1fixed.h"
#include "assert_print.h"

#include <stdio.h>

int main (int,char**) {
	const int b = 8;
	const int s = 1 << b;
        const short int c[] = {1*s,3*s,2*s,-5*s,8*s,-8*s,7*s,9*s};
        Fir1fixed fir(c,b);
        int acc = 0;
        for(int i = 0;i < 16;i++) {
		int v = 0;
		if ((i == 1) || (i > 10)) {
			v = 1;
		}
		// let's filter a delta pulse at time step 1 and
		// a unit step at time step 10
		v = fir.filter(v);
		// now let's check if the filter has done the right ops
		// the delta pulse should reproduce the impulse respnse
		if ( (i < 8) && (i > 0) ) {
			assert_print(
				(c[i-1] >> b) == v,
				"Impulse response calc mismatch.");
		}
		// and the step response should accumulate it
		if (i > 10) {
			acc = acc + (c[i - 11] >> b);
			assert_print(
				v == acc,
				"Step response calc mismatch.");
		}
        }
}
