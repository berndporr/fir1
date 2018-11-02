import numpy as np
import pylab as pl
import scipy.signal as signal
import fir1

fs = 1000

NTAPS = 100
LEARNING_RATE = 0.0005

ecg = np.loadtxt("ecg50hz.dat")
pl.figure(1)
pl.plot(ecg)

f = fir1.Fir1(NTAPS)
f.setLearningRate(LEARNING_RATE);

y= np.empty(len(ecg))
for i in range(len(ecg)):
    ref_noise = np.sin(2.0 * np.pi / 20.0 * i);
    canceller = f.filter(ref_noise)
    output_signal = ecg[i] - canceller
    f.lms_update(output_signal)
    y[i] = output_signal

pl.figure(2)
pl.plot(y)
pl.show()
