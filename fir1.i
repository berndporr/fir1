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

// Python only feature:
// Calling getCoeff() without an argument returns a numpy array of the filter weights.
// This is fine in Python, everything is very dynamic. It might be dangerous in C(++)

%feature("shadow") Fir1::getCoeff(double *, unsigned) const %{
def getCoeff(*args):
        if len(args) < 2 :
                // Only one argument given, and that is self.
                // Set the number of taps to return from the number of weights.
                return $action(args[0], args[0].getTaps())
        else :
                // If any other arguments are supplied, pass them through to the C++ library.
                return $action(*args)
%}

%apply (double* IN_ARRAY1, int DIM1) {(double *coefficients, unsigned number_of_taps)};
%apply (double* ARGOUT_ARRAY1, int DIM1) {(double *coeff_data, unsigned number_of_taps)};

%include "Fir1.h"
