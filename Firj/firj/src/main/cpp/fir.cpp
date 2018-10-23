#include <jni.h>
#include <string>

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>

#include "../../Fir.h"

extern "C" {

jlong
Java_tech_glasgowneuro_ECGrrDetector_Fir_getInstance(JNIEnv *env,
                                                     jclass clazz,
                                                     jdoubleArray coeffArray) {

    double *coeffValues = env->GetDoubleArrayElements(coeffArray, 0);
    int nTaps = env->GetArrayLength(coeffArray);

    Fir1 *fir = new Fir1(coeffValues, nTaps);

    env->ReleaseDoubleArrayElements(coeffArray, coeffValues, 0);

    return (jlong) fir;
}


jdouble Java_tech_glasgowneuro_ECGrrDetector_Fir_filter(JNIEnv *env,
                                                        jclass clazz,
                                                        jlong instance,
                                                        jdouble value) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return 0;
    return fir->filter(value);
}


void Java_tech_glasgowneuro_ECGrrDetector_Fir_releaseInstance(JNIEnv *env,
                                                              jclass clazz,
                                                              jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == NULL) return;
    delete fir;
}


}