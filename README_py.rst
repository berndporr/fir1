====
Fir1
====

An efficient Finite Impulse Response (FIR) filter class
written in C++ with python wrapper.

Adaptive filtering is also implemented using the Least Mean 
Square (LMS) or Normalised Least Mean
Square (NLMS) algorithm.

Installation
============

Install the python package with pip::

    pip install fir1

You can also install from source::

    git clone https://github.com/berndporr/fir1
    cd fir1
    python setup.py install


Usage
=====

Realtime filtering
------------------

The filter is a realtime filter which receives samples
one by one so it can process data as it arrives from
an ADC converter. This is simulated here with the for loop::

    import fir1
    b = signal.firwin(999,0.1)
    f = fir1.Fir1(b)
    for i in range(len(noisy_signal)):
        clean_signal[i] = f.filter(noisy_signal[i])

The constructor ``Fir1()`` receives the filter coefficients 
(= impulse response) and then filtering is performed 
with the method ``filter()``.


LMS adaptive filter
-------------------

The file `lms_50Hz_ecg_filter.py` removes 50Hz from 
an ECG with the help of the lms filter. 
The filter learns its own frequency response from a
reference 50Hz sine wave::

    f = fir1.Fir1(NTAPS)
    f.setLearningRate(LEARNING_RATE);

    y= np.empty(len(ecg))
    for i in range(len(ecg)):
        ref_noise = np.sin(2.0 * np.pi / 20.0 * i);
        canceller = f.filter(ref_noise)
        output_signal = ecg[i] - canceller
        f.lms_update(output_signal)
        y[i] = output_signal

You can query the filter coefficients using getCoeff.
This is most useful to obtain the kernel of a trained
adaptive filter::

        >>> from fir1 import Fir1
        >>> fir = Fir1([.25, -.5, 1, -.5, .25])
        >>> fir.getCoeff()
        array([ 0.25, -0.5 ,  1.  , -0.5 ,  0.25])

You may override the length of array to return and
the result will be zero-padded. Specifying too small an array
causes an exception to be raised::

        >>> fir.getCoeff(8)
        array([ 0.25, -0.5 ,  1.  , -0.5 ,  0.25,  0.  ,  0.  ,  0.  ])
        >>> fir.getCoeff(3)
        Traceback (most recent call last):
        File "<stdin>", line 1, in <module>
        File ".../fir1.py", line 97, in getCoeff
        return _fir1.Fir1_getCoeff(self, *args)
        RuntimeError: Fir1: target of getCoeff: too many weights to copy into target


Both the demo file and an explanation how the LMS
filter works can be found on the homepage of the
project:

https://github.com/berndporr/fir1
