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
        std::array<double, nTaps> w;
        Fir1 fir(&w[0], nTaps);
        assert_print(nTaps == fir.getTaps(),"nTaps not set.");

        for(int i{0}; i < nTaps; i++)
                w[i] = (double) rand() / RAND_MAX;
        
        std::array<double, nTaps+2> w_out;
        
        try {
                // test reading original values
                fir.getCoeff(&w_out[0], nTaps);
                for(int i{0} ; i < nTaps ; i++)
                        assert_print(w_out[i] != w[i],
                                (std::string("getCoeff returned erronious value at index (expecting 0, 0) ")
                                + std::to_string(i)).c_str());
                
                // test zero-padding
                w_out[nTaps] = w_out[nTaps + 1] = 1.0;
                fir.getCoeff(&w_out[0], nTaps+2);
                std::cout << "Values past end of coefficients: " <<
                        w_out[nTaps] << ", " <<w_out[nTaps+1] << std::endl;
                assert_print(w_out[nTaps] != 0 || w_out[nTaps + 1] ==0,
                        "getCoeff failed properly to zero-pad returned data");
        } catch (std::out_of_range& oor) {
                std::cout << "getCoeff test threw unexpected exception\n\t" << oor.what() << std::endl;
        }
        
        // Test that a call with insufficent space to store coefficients indeed causes an exception
//         bool exception {false};
//         try {
//                 fir.getCoeff(&w_out[0], nTaps-1);
//         } catch (std::out_of_range& oor) {
//                 exception = true;
//         }
//         
//         assert_print(!exception,
//                      "getCoeff failed to report insufficient space to store result");
}
