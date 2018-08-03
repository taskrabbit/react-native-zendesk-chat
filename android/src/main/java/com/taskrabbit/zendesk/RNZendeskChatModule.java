package com.taskrabbit.zendesk;

import android.app.Activity;
import android.content.Intent;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.zopim.android.sdk.api.ZopimChat;
import com.zopim.android.sdk.model.VisitorInfo;
import com.zopim.android.sdk.prechat.ZopimChatActivity;
import com.zopim.android.sdk.prechat.PreChatForm;


import java.lang.String;

public class RNZendeskChatModule extends ReactContextBaseJavaModule {
    private ReactContext mReactContext;

    public RNZendeskChatModule(ReactApplicationContext reactContext) {
        super(reactContext);
        mReactContext = reactContext;
    }

    @Override
    public String getName() {
        return "RNZendeskChatModule";
    }

    @ReactMethod
    public void setVisitorInfo(ReadableMap options) {
        VisitorInfo.Builder builder = new VisitorInfo.Builder();

        if (options.hasKey("name")) {
            builder.name(options.getString("name"));
        }
        if (options.hasKey("email")) {
            builder.email(options.getString("email"));
        }
        if (options.hasKey("phone")) {
            builder.phoneNumber(options.getString("phone"));
        }
        VisitorInfo visitorData = builder.build();
        ZopimChat.setVisitorInfo(visitorData);
    }

    @ReactMethod
    public void preChatConfig(ReadableMap options) {
       PreChatForm defaultPreChat = new PreChatForm.Builder()
                .name(PreChatForm.Field.REQUIRED_EDITABLE)
                .email(PreChatForm.Field.REQUIRED_EDITABLE)
                .build();

        ZopimChat.init("5sfLCtINlkDxY4CaDK2L2Fw4gABcpI67")
        .preChatForm(defaultPreChat)
        .build();
    }

    @ReactMethod
    public void init(String key) {
        ZopimChat.init(key);
    }

    @ReactMethod
    public void startChat(ReadableMap options) {
        setVisitorInfo(options);
        Activity activity = getCurrentActivity();
        if (activity != null) {
            activity.startActivity(new Intent(mReactContext, ZopimChatActivity.class));
        }
    }

     @ReactMethod
    public void startVisitorChat(ReadableMap options) {
        preChatConfig(options);
        Activity activity = getCurrentActivity();
        if (activity != null) {
            activity.startActivity(new Intent(mReactContext, ZopimChatActivity.class));
        }
    }
}
