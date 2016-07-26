package com.example;

import android.os.Bundle;

import com.facebook.react.ReactActivity;

import com.zopim.android.sdk.api.ZopimChat;

public class MainActivity extends ReactActivity {

    /**
     * Returns the name of the main component registered from JavaScript.
     * This is used to schedule rendering of the component.
     */
    @Override
    protected String getMainComponentName() {
        return "example";
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Init ZopimChat
        ZopimChat.init("3q3y4vnmd334dHpK6EvVALjPtSLWzNcb");
    }
}
