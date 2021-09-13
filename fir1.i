%module fir1
%include exception.i

%{
	#define SWIG_FILE_WITH_INIT
	#include "Fir1.h"
%}

%include "numpy.i"

%exception {
    try {
        $action
    } catch (const std::exception& e) {
	PyErr_SetString(PyExc_RuntimeError, e.what());
	return NULL;
    }
}


%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double *coefficients, unsigned number_of_taps)};
%apply (double* ARGOUT_ARRAY1, int DIM1) {(double *coeff_data, unsigned number_of_taps)};

%include "Fir1.h"
