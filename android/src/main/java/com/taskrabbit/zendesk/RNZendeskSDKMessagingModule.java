package com.taskrabbit.zendesk;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;

import java.lang.String;

import zendesk.android.Zendesk;
import zendesk.messaging.android.DefaultMessagingFactory;

public class RNZendeskSDKMessagingModule extends ReactContextBaseJavaModule {
		private static final String TAG = "[RNZendeskSDKMessagingModule]";
		private Application applicationContext;
		private ReactContext reactContext;

    public RNZendeskSDKMessagingModule(ReactApplicationContext reactContext) {
			super(reactContext);
			this.reactContext = reactContext;
			this.applicationContext = (Application) reactContext.getApplicationContext();
    }

    @Override
    public String getName() {
			return "RNZendeskSDKMessagingModule";
    }

    @ReactMethod
    public void initialize(String channelKey, Promise promise) {
			Zendesk.initialize(
				this.applicationContext,
				channelKey,
				zendesk -> {
					Log.i(TAG, "Initialization successful");
					promise.resolve(true);
				},
				error -> {
					Log.e(TAG, "Messaging failed to initialize", error);
					promise.reject("INIT_ERROR", error.getLocalizedMessage(), error);
				},
				new DefaultMessagingFactory());
    }

	@ReactMethod
	public void showMessaging() {
		Zendesk.getInstance().getMessaging().showMessaging(reactContext);
	}

	@ReactMethod
	public void hideMessaging() {
		Activity activity = reactContext.getCurrentActivity();
		if (activity != null) {
			String activityName = activity.getClass().getName();
			if (activityName.equals("zendesk.messaging.android.Messaging")) {
				activity.finish();
			}
		}
	}

	@ReactMethod
	public void getUnreadMessageCount(Promise promise) {
		promise.resolve(Zendesk.getInstance().getMessaging().getUnreadMessageCount());
	}
}
