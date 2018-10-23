# FIR1

![alt tag](fir.png)

An efficient finite impulse response (FIR) filter class
in C++ and JAVA wrapper for Android.

The floating point class offers also adaptive filtering
using the least mean square (LMS) or normalised least mean
square (NLMS) algorithm.


## Installation

### Linux / Unix / MACOSX: compilation from source

The build system is `cmake`. Install the library with
the standard sequence:
```
cmake .
make
sudo make install
sudo ldconfig
```
or for debugging run cmake with:
```cmake -DCMAKE_BUILD_TYPE="Debug" .```
By default optimised release libraries are generated.

### Ubuntu packages for xenial and bionic

Add this repository to your package manager:
```
sudo add-apt-repository ppa:berndporr/usbdux
sudo apt-get update
```
This adds `fir1-dev` and `fir1` to your package list.
The demo files are in `/usr/share/doc/fir1-dev`. Copy them into a working
directory, type `gunzip *.gz`, `cmake .` and `make`.

### Windows

Under windows only the static library is generated which
should be used for your code development.

```
cmake -G "Visual Studio 15 2017 Win64" .
```
and then start Visual C++ and compile it. Usually
you want to compile both the release and debug
libraries because they are not compatible to each
other under Windows.

### Android / JAVA

The subdirectory `firj` contains an Android project. Load
it into Android studio and build it either as a release
or debug binary. This generates an Android aar which you
can import into your project. See the `InstrumentedTest.java`
for an instructional example.


## How to use it

### Generating the FIR filter coefficients

You can set the coefficients either with a C floating point array or
with a text file containing the coefficients. The text file or
the floating point arrary with the
coefficients can easily be generated by Python or OCTAVE/MATLAB:

1. Python: use the `firwin` command to generate the coefficients:
```
# Sampling rate
fs = 1000
# bandstop between 45 and 55 Hz:
f1 = 45
f2 = 55
b = signal.firwin(999,[f1/fs*2,f2/fs*2])
np.savetxt("h.dat",b)
```
this text file can then be imported into the filter at
runtime or you turn the textfile into a C++ floating point array and
point the filter to it.

For fixed point you need to scale up the coefficients,
for example by 16 bits: np.savetxt("h.dat",b*65536)

2. octave/MATLAB:
```
octave:1> h=fir1(100,0.1);
octave:2> save 'h.dat' h -ascii
```
which creates the coefficients of a lowpass filter with 100 taps
and normalised cutoff 0.1 to Nyquist.

Again, for fixed point "h" needs to be scaled.

3. JAVA: You need to convert the ascii file into a double array.

### Initialisation

1. C++ floating point FIR filter:
```
Fir1 fir("h.dat");
```
or import the coefficients as a floating point array (double).
```
Fir1 fir(coefficients,number_of_coefficients)
```

2. C++ integer FIR filter:
```
Fir1fixed fir("h_fixed.dat",12);
```
where the coefficients have been scaled up by 2^12 and the
filter will scale them down by this amount (with the help of
a bitshift operation).

3. JAVA:
```
Fir1 fir = new Fir1(coeff);
```
where `coeff` is an array of double precision coefficients
and returns the fir filter class.

### Realtime filtering

1. C++ double:
```
double b = fir.filter(a);
```

2. C++ integer:
```
int b = fir.filter(a);
```

3. JAVA:
```
double b = fir.filter(a)
```

### Destructor

1. C++
```
delete fir;
```

2. JAVA
```
fir.release();
```
to release the underlying C++ class.

## LMS algorithm

The least mean square algorithm adjusts the FIR coefficients w_k
with the help of an error signal
```
w_k(t+1) = w_k(t) + learning_rate * buffer_k(t) * error(t)
```
using the function `lms_update(error)` while performing
the filtering with `filter()`.

### How to use the filter

- Construct the Fir filter with all coefficients set to zero: `Fir1(nCoeff)`
- Set the learning_rate with the method `setLearningRate(learning_rate)`.
- Define the signal1 to the FIR filter and use its standard `filter` method to filter it.
- Define your error which needs to be minimised: `error = signal2 - fir_filter_output`
- Feed the error back into the filter with the method `lms_update(error)`.

The `lmsdemo` in the demo directory makes this concept much clearer how to remove
artefacts with this method.

![alt tag](lms.png)

The above plot shows the filter in action which removes 50Hz noise with the adaptive
filter. Learning is very fast and the learning rate here is deliberately kept low to
show how it works.

### Stability

The FIR filter itself is stable but the error signal changes the filter coefficients which
in turn change the error and so on. There is a rule of thumb that the learning rate
should be less than the "tap power" of the input signal which is just the sum of all
squared values held in the different taps:
```
learning_rate < 1/getTapInputPower()
```
That allows an adaptive learning rate which is called "normalised LMS". From
my experiments that works in theory but in practise the realtime value of getTapInputPower()
can make the algorithm easily unstable because it might suggest infinite learning rates
and can fluctuate wildly. A better approach is to keep the learning rate constant and rather
control the power of the input signal by, for example, normalising the input signal or limiting
it.

See the demo below which removes 50Hz from an ECG which uses a normalised 50Hz signal
which guarantees stability by design.


## Demos
Demo programs are in the "demo" directory which show how to use the
filters for both floating point and fixed point.
1. `firdemo` sends an impulse into the filter and you should see the impulse
response at its output.
2. `fixeddemo` filters an example ECG with 50Hz noise. The coefficients
are 12 bit and you can generate them either with OCTAVE/MATLAB or Python.
The scripts are also provided.
3. `lmsdemo` filters out 50Hz noise from an ECG with the help of
adaptive filtering by using the 50Hz powerline frequency as the input
to the filter. This can be replaced by any reference artefact signal
or signal which is correlated with the artefact.
4. JAVA has an `InstrumentedTest` which filters both a delta pulse and
a step function.


## Credits

This library has been adapted form Graeme Hattan's original C code.

Enjoy!

Bernd Porr & Graeme Hattan
