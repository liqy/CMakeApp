package com.liqy.cmakeapp;

/**
 *
 *
 * 静态注册就是根据方法名，将Java方法和JNI方法建立关联，但是它有一些缺点： 格式为Java_包名_类名_方法名
      1.JNI层的方法名称过长。
      2.声明Native方法的类需要用javah生成头文件。
      3.初次调用JIN方法时需要建立关联，影响效率。
 * 动态注册
 *
 *
 * Created by liqy on 2018/2/9.
 */

public class Jni {
    /**
     *
     *
     *
     *
     * TODO 声明原生方法
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public static native String stringToJNI();


}
