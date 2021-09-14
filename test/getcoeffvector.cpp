#include "Fir1.h"
#include "assert_print.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <array>
#include <string>
#include <stdexcept>
#include <iostream>

// Testing whether a randomly assigned FIR can have its coefficients read back

constexpr int nTaps = 10;

int main (int,char**) {
        std::vector<double> w;
        for(unsigned int i = 0; i < nTaps; i++)
                w.push_back((double) rand() / RAND_MAX);
        Fir1 fir(w);
        assert_print(nTaps == fir.getTaps(),"nTaps not set.");
        
        std::vector <double> w_out = fir.getCoeffVector();
        
	for(unsigned int i=0 ; i < nTaps ; i++) {
		assert_print(w_out[i] == w[i],
			     (std::string("getCoeff returned erronious value at index ")
			      + std::to_string(i)).c_str());
	}
        
}
