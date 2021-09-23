#include <jni.h>
#include <string>

#include <cstring>
#include <cstdlib>
#include <cassert>
#include <stdexcept>

#include "../../../../../Fir1.h"

extern "C" {

jlong
Java_uk_me_berndporr_firj_Fir1_getInstance(JNIEnv *env,
                                           jclass,
                                           jdoubleArray coeffArray) {

    double *coeffValues = env->GetDoubleArrayElements(coeffArray, 0);
    auto nTaps = (unsigned) env->GetArrayLength(coeffArray);

    Fir1 *fir = new Fir1(coeffValues, nTaps);

    env->ReleaseDoubleArrayElements(coeffArray, coeffValues, 0);

    return (jlong) fir;
}


jlong
Java_uk_me_berndporr_firj_Fir1_getInstanceLMS(JNIEnv *env,
                                              jclass,
                                              jint nTaps) {

    Fir1 *fir = new Fir1((unsigned)nTaps);
    return (jlong) fir;
}


jint Java_uk_me_berndporr_firj_Fir1_getTaps(JNIEnv *,
                                            jclass,
                                            jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == nullptr) return 0;
    return (jint)(fir->getTaps());
}


jdouble
Java_uk_me_berndporr_firj_Fir1_filter(JNIEnv *,
                                      jclass,
                                      jlong instance,
                                      jdouble value) {
    Fir1 *fir = (Fir1 *) instance;
    if (fir == nullptr) return 0;
    return fir->filter(value);
}


void
Java_uk_me_berndporr_firj_Fir1_lmsUpdate(JNIEnv *,
                                         jclass,
                                         jlong instance,
                                         jdouble error) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->lms_update(error);
}


void
Java_uk_me_berndporr_firj_Fir1_setLearningRate(JNIEnv *,
                                               jclass,
                                               jlong instance,
                                               jdouble mu) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->setLearningRate(mu);
}


jdouble
Java_uk_me_berndporr_firj_Fir1_getTapInputPower(JNIEnv *,
                                                jclass,
                                                jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    return fir->getTapInputPower();
}


jlong Java_uk_me_berndporr_firj_Fir1_releaseInstance(JNIEnv *,
                                                    jclass,
                                                    jlong instance) {
    Fir1 *fir = (Fir1 *) instance;
    delete fir;
    return (jlong)nullptr;
}

jdoubleArray Java_uk_me_berndporr_firj_Fir1_getCoeff(JNIEnv * env, jclass, jlong instance, jint n) {
    Fir1 *fir = (Fir1 *) instance;
    jdoubleArray doubleArray = env->NewDoubleArray(n);
    jdouble *doubleValues = env->GetDoubleArrayElements(doubleArray, 0);
    try {
        fir->getCoeff(doubleValues, (unsigned) n);
    } catch (std::out_of_range&e) {
        jclass Exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(Exception,e.what());
    }
    env->ReleaseDoubleArrayElements(doubleArray, doubleValues, 0);
    return doubleArray;
}


}
