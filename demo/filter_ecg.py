import numpy as np
import pylab as pl
import scipy.signal as signal
import fir1

fs = 1000
f1 = 45
f2 = 55

b = signal.firwin(999,[f1/fs*2,f2/fs*2])

ecg = np.loadtxt("ecg50hz.dat")
pl.figure(1)
pl.plot(ecg)

f = fir1.Fir1(b)

y= np.empty(len(ecg))
for i in range(len(ecg)):
    y[i] = f.filter(ecg[i])

pl.figure(2)
pl.plot(y[1000:])
pl.show()
