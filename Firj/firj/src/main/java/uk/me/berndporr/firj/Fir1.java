package uk.me.berndporr.firj;

import android.util.Log;

public class Fir1 {

    static final String TAG = "Fir1";

    private long instance = 0;

    /**
     * Constructor: takes the FIR coefficients and sets the
     * length of the filter
     * @param coefficients: FIR coefficients
     */
    public Fir1(double[] coefficients) {
        instance = getInstance(coefficients);
    }

    /**
     * Inits an FIR filter with all coefficients and the buffer set to zero.
     * That's useful for setting up the LMS filter.
     * @param numberOfTaps of the FIR filter.
     */
    public Fir1(int numberOfTaps) {
        instance = getInstanceLMS(numberOfTaps);
    }

    /**
     * Gets the number of taps
     * @return Number of taps
     */
    public int getTaps() {return getTaps(instance);}

    /**
     * Realtime / causal filter operation: one sample in and
     * one sample out
     * @param v: input value
     * @return is the filtered value
     */
    public double filter(double v) {
        return filter(instance,v);
    }

    /**
     * LMS filter update
     * @param error is the error applied to all weights
     */
    public void lmsUpdate(double error) {
        lmsUpdate(instance,error);
    }

    /**
     * Sets the learning rate which defines how strong
     * the error influences the weights
     * @param mu learning rate
     */
    public void setLearningRate(double mu) {
        setLearningRate(instance,mu);
    }

    /**
     * Gets the tap input power to normalised LMS
     * @return tap input power
     */
    public double getTapInputPower() {
        return getTapInputPower(instance);
    }

    /**
     * Gets the coefficients
     * @return A double array of the coefficients
     */
    public double[] getCoeff() {return getCoeff(instance,getTaps(instance)); }

    /**
     * Gets the coefficients
     * @return A double array of the coefficients
     */
    public double[] getCoeff(int n) {return getCoeff(instance,n); }

    /**
     * Needs to be called when the filter is no longer being
     * used. This frees up the memory for both the ringbuffer
     * and the coefficients.
     */
    public void release() {
        instance = releaseInstance(instance);
    }

    private static native long getInstance(double[] coefficients);
    private static native long getInstanceLMS(int numberOfTaps);
    private static native int getTaps(long instance);
    private static native double filter(long instance, double v);
    private static native long releaseInstance(long instance);
    private static native void lmsUpdate(long instance, double error);
    private static native void setLearningRate(long instance, double mu);
    private static native double getTapInputPower(long instance);
    private static native double[] getCoeff(long instance, int n);

    static {
        System.loadLibrary("fir-lib");
        Log.d(TAG,"Fir1 library loaded");
    }

}
