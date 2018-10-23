package uk.me.berndporr.firj;

import android.util.Log;

public class Fir1 {

    static final String TAG = "Fir1";

    private long instance = 0;

    public Fir1(double[] coefficients) {
        instance = getInstance(coefficients);
    }
    public double filter(double v) {
        return filterInstance(instance,v);
    }
    public void release() {
        releaseInstance(instance);
    }

    private static native long getInstance(double[] coefficients);
    private static native double filterInstance(long instance, double v);
    private static native void releaseInstance(long instance);

    static {
        System.loadLibrary("fir-lib");
        Log.d(TAG,"Fir1 library loaded");
    }

}
