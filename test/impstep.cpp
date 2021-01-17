// Floating point example
//

// This is the only include you need
#include "Fir1.h"
#include "assert_print.h"
#include "math.h"

#include <stdio.h>

int main (int,char**) {
        const double c[] = {1,3,2,-5,8,-8,7,9};
        Fir1 fir(c);
        double acc = 0;
        for(int i = 0;i < 16;i++) {
		double v = 0;
		if ((i == 1) || (i > 10)) {
			v = 1;
		}
		// let's filter a delta pulse at time step 1 and
		// a unit step at time step 10
		v = fir.filter(v);
		// now let's check if the filter has done the right ops
		// the delta pulse should reproduce the impulse respnse
		if ( (i < 9) && (i > 0) ) {
			assert_print(
				round(c[i-1]) == round(v),
				"Impulse response calc mismatch.");
		}
		// and the step response should accumulate it
		if (i > 10) {
			acc = acc + c[i - 11];
			assert_print(
				round(v) == round(acc),
				"Step response calc mismatch.");
		}
        }
}
