package uk.me.berndporr.firj;

public class Fir {

    private long instance = 0;

    public void init(double[] coefficients) {
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
    }

}
