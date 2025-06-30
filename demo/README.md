# Demos

## 50Hz removal
This demo removes 50Hz from an ECG file. You first need
to calc the coefficients and then you can filter it:

 - `create_bandstop_coeff.py`: calculates the bandstop coefficients for firdemo.
 - `firdemo.cpp`: removes 50Hz noise from `ecg50hz.dat` and saves it to `ecg_filtered.dat`.

## Lowpass filtering
Similar to above but the ECG file is lowpass filtered below 50Hz
which results in smoothing. Instead of loading the coefficients
from a text-file they are in a C-array.

## LMS adaptive filtering
`lmsdemo.cpp`: removes 50Hz from `ecg50hz.dat` with an adptive LMS filter and saves it to `ecg_filtered.dat`. The adaptive filter uses a 50Hz reference.

## Python wrapper demo
`filter_ecg.py`: Pure python program which loads the fir1 module to filter out 50Hz.
