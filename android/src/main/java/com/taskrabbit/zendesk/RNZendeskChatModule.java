package com.taskrabbit.zendesk;

import android.app.Activity;
import android.content.Intent;
import com.facebook.react.bridge.*;
import com.zopim.android.sdk.api.ZopimChat;
import com.zopim.android.sdk.model.VisitorInfo;
import com.zopim.android.sdk.prechat.ZopimChatActivity;

public class RNZendeskChatModule extends ReactContextBaseJavaModule {
    private ReactContext mReactContext;
    private Activity mActivity;

    public RNZendeskChatModule(ReactApplicationContext reactContext, Activity activity) {
        super(reactContext);

        mActivity = activity;
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
    public void startChat(ReadableMap options) {
        setVisitorInfo(options);
        mActivity.startActivity(new Intent(mReactContext, ZopimChatActivity.class));
    }
}
