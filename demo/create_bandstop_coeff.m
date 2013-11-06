b = int16(fir1(1000,[45/1000 55/1000]*2,'stop')*2^12);
save -ascii 'coeff12bit.dat' b;
