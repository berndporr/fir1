package uk.me.berndporr.firj;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 */
@RunWith(AndroidJUnit4.class)
public class InstrumentedTest {

    String TAG="InstrumentedTest";

    @Test
    public void firTest() {
        double[] c = {1,3,2,-5,8,-8,7,9};
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
                assertEquals(Math.round(c[i-1]),Math.round(v));
            }
            // and the step response should accumulate it
            if (i > 10) {
                acc = acc + c[i - 11];
                assertEquals(Math.round(v),Math.round(acc));
            }
            Log.d(TAG,"Fir1: t="+i+",v="+v);
        }
        fir.release();
    }

}
