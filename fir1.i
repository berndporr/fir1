%module fir1
%{
	#define SWIG_FILE_WITH_INIT
	#include "Fir1.h"
%}

%include "numpy.i"

%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double *coefficients, unsigned number_of_taps)};

%include "Fir1.h"
