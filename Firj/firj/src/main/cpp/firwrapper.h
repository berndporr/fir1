#ifndef FIR_H
#define FIR_H

class Fir
{
public:
    // Coefficients as double floats and the number of taps
    Fir(double *coefficients, unsigned number_of_taps);

    // destructor
    ~Fir();

    // the actual filter function
    double filter(double input);

    // Resets the buffer (but not the coefficients)
    void reset();

    // Sets all coefficients to zero
    void zeroCoeff();

    // returns the number of taps
    unsigned getTaps() {return taps;};

private:
    double        *coefficients = NULL;
    double        *buffer = NULL;
    unsigned      taps = 0, offset = 0;
    double        mu = 0;
};



extern "C" {



}






#endif
