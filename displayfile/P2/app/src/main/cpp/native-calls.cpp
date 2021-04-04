#include <jni.h>
#include <string>
#include "read_file.h"

extern "C"
JNIEXPORT jstring

JNICALL
Java_edu_ufl_cise_os_p2_P2Activity_stringFromJNI(
        JNIEnv *env,
        jobject, jstring path) {


    const char *filename = env->GetStringUTFChars(path, NULL);

    const char *f = read_file(filename);

    if (f != nullptr) {

        return env->NewStringUTF(f);
    }

        else {
            return env->NewStringUTF("Error opening file!");
        }

    }

