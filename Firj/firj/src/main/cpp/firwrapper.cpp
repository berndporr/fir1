#include <jni.h>
#include <string>

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>

#include "../../../../../Fir1.h"

extern "C" {

jlong
Java_uk_me_berndporr_firj_Fir1_getInstance(JNIEnv *env,
                                          jclass clazz,
                                          jdoubleArray coeffArray) {

    double *coeffValues = env->GetDoubleArrayElements(coeffArray, 0);
    unsigned nTaps = (unsigned) env->GetArrayLength(coeffArray);

    Fir1 *fir = new Fir1(coeffValues, nTaps);

    env->ReleaseDoubleArrayElements(coeffArray, coeffValues, 0);

    return (jlong) fir;
}


jdouble
Java_uk_me_berndporr_firj_Fir1_filterInstance(JNIEnv *env,
                                             jclass clazz,
                                             jlong instance,
                                             jdouble value) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return 0;
    return fir->filter(value);
}


void Java_uk_me_berndporr_firj_Fir1_releaseInstance(JNIEnv *env,
                                                   jclass clazz,
                                                   jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return;
    delete fir;
}


}