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
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class InstrumentedTest {

    String TAG="InstrumentedTest";

    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();
        assertEquals("uk.me.berndporr.firj.test", appContext.getPackageName());

        double[] c = {0,1,2,3,4,5,6,7};
        Fir1 fir = new Fir1(c);
        for(int i = 0;i < (c.length * 2);i++) {
            double v = 0;
            if (i == 1) {
                v = 1;
            }
            v = fir.filter(v);
            Log.d(TAG,"Fir1: t="+i+",v="+v);
        }
        fir.release();
    }
}
