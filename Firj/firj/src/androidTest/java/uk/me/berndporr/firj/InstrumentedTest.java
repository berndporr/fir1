package uk.me.berndporr.firj;

import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

import androidx.test.ext.junit.runners.AndroidJUnit4;

/**
 * Instrumented test, which will execute on an Android device.
 */
@RunWith(AndroidJUnit4.class)
public class InstrumentedTest {

    final String TAG="InstrumentedTest";

    final double delta = 1E-40;

    public double[] randArr(int nTaps) {
        double[] a = new double[nTaps];
        for(int i=0;i<nTaps;i++) {
            a[i] = Math.random();
        }
        return a;
    }

    @Test
    public void firTest() {
        double[] c = randArr(8);
        Fir1 fir = new Fir1(c);
        double acc = 0;
        for(int i = 0;i < (c.length * 2);i++) {
            double v = 0;
            if ((i == 1) || (i > 10)) {
                v = 1;
            }
            // let's filter a delta pulse at time step 1 and
            // a unit step at time step 10
            v = fir.filter(v);
            // now let's check if the filter has done the right ops
            // the delta pulse should reproduce the impulse respnse
            if ( (i < 9) && (i > 0) ) {
                assertEquals(Math.round(c[i-1]),Math.round(v),delta);
            }
            // and the step response should accumulate it
            if (i > 10) {
                acc = acc + c[i - 11];
                assertEquals(Math.round(v),Math.round(acc),delta);
            }
            Log.v(TAG,"Fir1: t="+i+",v="+v);
        }
        fir.release();
    }

    @Test
    public void coeffTest() {
        double[] c = randArr(100);
        Fir1 fir = new Fir1(c);
        double[] coeff = fir.getCoeff();
        for(int i=0; i < fir.getTaps(); i++) {
            assertEquals(c[i],coeff[i],delta);
        }
        fir.release();
        Log.v(TAG,"Coeff readout with default length OK.");
    }

    @Test
    public void coeffTest2() {
        int n = 100;
        double[] c = randArr(n);
        Fir1 fir = new Fir1(c);
        double[] coeff = fir.getCoeff(n+10);
        for(int i=0; i < fir.getTaps(); i++) {
            assertEquals(c[i],coeff[i],delta);
        }
        fir.release();
        Log.v(TAG,"Coeff readout with custom length OK.");
    }

    @Test
    public void coeffTest3() {
        int n = 100;
        double[] c = randArr(n);
        Fir1 fir = new Fir1(c);
        boolean exceptionHasHappend = false;
        try {
            double[] coeff = fir.getCoeff(n/2);
            for (int i = 0; i < fir.getTaps(); i++) {
                assertEquals(c[i], coeff[i], delta);
            }
        } catch (Exception e) {
            exceptionHasHappend = true;
            Log.v(TAG,"Exception because of lack of space successfully triggered:",e);
        }
        fir.release();
        assertTrue(exceptionHasHappend);
    }

}
