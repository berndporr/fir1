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

%feature("shadow") Fir1::getCoeff(double *, unsigned) const %{
def getCoeff(*args):
        print(args)
        if len(args) < 2 :
                return $action(args[0], args[0].getTaps())
        else :
                return $action(*args)
%}

%apply (double* IN_ARRAY1, int DIM1) {(double *coefficients, unsigned number_of_taps)};
%apply (double* ARGOUT_ARRAY1, int DIM1) {(double *coeff_data, unsigned number_of_taps)};

%include "Fir1.h"
