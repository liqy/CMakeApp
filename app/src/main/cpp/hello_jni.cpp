#include <jni.h>
#include <string>
#include <android/log.h>

/*打印日志的TAG*/
static const char *kTAG = "hello-jniCallback";

/* 动态注册 Java中的对应类名 注意斜杠的方向*/
const char *ClassName = "com/liqy/cmakeapp/Jni";


/*打印日志的宏变量*/
#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "hello-cdep::", __VA_ARGS__))
#define LOGW(...) \
  ((void)__android_log_print(ANDROID_LOG_WARN, kTAG, __VA_ARGS__))
#define LOGE(...) \
  ((void)__android_log_print(ANDROID_LOG_ERROR, kTAG, __VA_ARGS__))

extern "C" {

    JNIEXPORT jstring

    JNICALL
    fromJNI(
            JNIEnv *env,
            jobject /* this 方法为 成员方法时，此处为jobject*/) {
        std::string hello = " 动态 Hello from C++ 成员方法";
        LOGI("打印日志");
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT jstring /* 返回类型*/

    JNICALL
    stringToJNI(  /* 方法名称要 Java_+包名+类名+方法名 */
            JNIEnv *env, /* JNI的上下文环境 */
            jclass /* this 指针 当方法为 static 静态方法时，此处为 jclass*/) {
        std::string hello = " 动态 Hello from C++ 静态方法";
        return env->NewStringUTF(hello.c_str());
    }

    //region 动态注册方法
    /**
     * 声明需要动态注册的方法
     * typedef struct {
     * const char* name;//Java方法的名字
     * const char* signature;//Java方法的签名信息
     * void*       fnPtr;//JNI中对应的方法指针
    } JNINativeMethod;
     */
    static JNINativeMethod gMethods[] = {
            {"stringFromJNI", "()Ljava/lang/String;",(void *)fromJNI},//对应java中的public native String stringFromJNI();
            {"stringToJNI", "()Ljava/lang/String;",(void *)stringToJNI}//对应java中的public static native String stringToJNI()
    };

    /****
     * 注册方法
     */
    static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                                     int numMethods) {
        jclass clazz;
        clazz = env->FindClass(className);
        if (clazz == NULL) {
            return JNI_FALSE;
        }
        if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
            return JNI_FALSE;
        }
        return JNI_TRUE;
    }

    /****
     * 注册类
     */
    static int registerNatives(JNIEnv *env) {
        return registerNativeMethods(env, ClassName, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
    }
    // endregion

    //region  初始化默认函数
    /****
     * 默认函数
     * 在调用 System.loadLibrary 时会调用，不需要手动调用
     */
    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
        JNIEnv *env = NULL;
        jint result = -1;

        if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
            return -1;
        }
        if (!registerNatives(env)) {//注册
            return -1;
        }
        //成功
        result = JNI_VERSION_1_4;
        return result;
    }
}