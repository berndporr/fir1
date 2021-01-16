#include "Fir1.h"
#include "assert_print.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include <stdio.h>

// Testing if the LMS filter is able to learn to eliminate
// a cosine signal with a sine signal!

const int nTaps = 10;
double mu = 0.1;

int main (int,char**) {
        Fir1 fir(nTaps);
        assert_print(nTaps == fir.getTaps(),"nTaps not set.");
	fir.setLearningRate(mu);

	double output_signal = 0;
	for(int i=0;i<100;i++) {
		double input_signal = cos(2*M_PI/20*i) * 0.1;
                double ref_noise = sin(2*M_PI/20*i);
                double canceller = fir.filter(ref_noise);
                output_signal = input_signal - canceller;
                fir.lms_update(output_signal);
                fprintf(stderr,"%le %le %le\n",output_signal,canceller,ref_noise);
	}
	fprintf(stderr,"%le\n",output_signal);
        assert_print(fabs(output_signal) < 1E-5,
		     "LMS did not cancel the sine wave with the cosine wave.");
}
