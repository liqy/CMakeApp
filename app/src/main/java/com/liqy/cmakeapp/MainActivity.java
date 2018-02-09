package com.liqy.cmakeapp;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    // TODO 使用之前加载，在哪里使用，就在哪里加载 加载native-lib，不加lib前缀
    static {
        System.loadLibrary("native-lib");//TODO 名称加载的时候注意：不哟啊带lib
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        Jni jni = new Jni();

        //TODO 调用和普通Java方法一样
        tv.setText(jni.stringFromJNI() +"\n"+ Jni.stringToJNI());
    }


}
