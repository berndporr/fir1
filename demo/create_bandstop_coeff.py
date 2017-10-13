import numpy as np
import pylab as pl
import scipy.signal as signal

fs = 1000
f1 = 45
f2 = 55
scale = 2**12

b = signal.firwin(999,[f1/fs*2,f2/fs*2])
b = b*scale
b = b.astype(int)
np.savetxt("coeff12bit.dat",b)
