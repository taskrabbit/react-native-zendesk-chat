package com.taskrabbit.zendesk;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;

import java.lang.String;


import kotlin.Unit;
import zendesk.android.FailureCallback;
import zendesk.android.SuccessCallback;
import zendesk.android.Zendesk;
import zendesk.android.ZendeskUser;
import zendesk.android.events.ZendeskEvent;
import zendesk.android.events.ZendeskEventListener;
import zendesk.messaging.android.DefaultMessagingFactory;
import zendesk.logger.Logger;

public class RNZendeskSDKMessagingModule extends ReactContextBaseJavaModule {
	private static final String TAG = "[RNZendeskSDKMessagingModule]";
	private Application applicationContext;
	private ReactContext reactContext;
	private ZendeskEventListener zendeskEventListener;

	private void sendEvent(ReactContext reactContext,
												 String eventName,
												 Object params) {
		reactContext
			.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
			.emit(eventName, params);
	}

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
	public void loginUser(String jwt, Promise promise) {
		Zendesk.getInstance().loginUser(jwt,
			new SuccessCallback<ZendeskUser>() {
				@Override
				public void onSuccess(ZendeskUser user) {
					promise.resolve(user);
				}},
			new FailureCallback<Throwable>() {
				@Override
				public void onFailure(@NonNull Throwable error) {
					promise.reject("LOGIN_ERROR", error.getLocalizedMessage(), error);
				}
		});
	}

	@ReactMethod
	public void logoutUser(Promise promise) {
		Zendesk.getInstance().logoutUser(
			new SuccessCallback<Unit>() {
				@Override
				public void onSuccess(Unit value) {
					promise.resolve(value);
				}},
			new FailureCallback<Throwable>() {
				@Override
				public void onFailure(@NonNull Throwable error) {
					promise.reject("LOGOUT_ERROR", error.getLocalizedMessage(), error);
				}
			});
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

	@ReactMethod
	public void startObservingEvents() {
		if (this.zendeskEventListener != null) {
			return;
		}

		this.zendeskEventListener = new ZendeskEventListener() {
				@Override
				public void onEvent(@NonNull ZendeskEvent zendeskEvent) {
					if (zendeskEvent instanceof ZendeskEvent.UnreadMessageCountChanged) {
						 sendEvent(reactContext, "ZDKZendeskEventUnreadMessageCountChanged",zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.AuthenticationFailed) {
						sendEvent(reactContext, "ZDKZendeskEventAuthenticationFailed", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationAdded) {
						sendEvent(reactContext, "ZDKZendeskEventConversationAdded", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.ConnectionStatusChanged) {
						sendEvent(reactContext, "ZDKZendeskEventConnectionStatusChanged", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.SendMessageFailed) {
						sendEvent(reactContext, "ZDKZendeskEventSendMessageFailed", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationOpened) {
						sendEvent(reactContext, "ZDKZendeskEventConversationOpened", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationStarted) {
						sendEvent(reactContext, "ZDKZendeskEventConversationStarted",zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.MessagesShown) {
						sendEvent(reactContext, "ZDKZendeskEventMessagesShown", zendeskEvent );
					} else if (zendeskEvent instanceof ZendeskEvent.FieldValidationFailed) {
						sendEvent(reactContext, "ZDKZendeskEventFieldValidationFailed", zendeskEvent );
					}
				}
		};

		Zendesk.getInstance().addEventListener(this.zendeskEventListener);
	}

	@ReactMethod
	public void stopObservingEvents() {
		if (this.zendeskEventListener != null) {
			Zendesk.getInstance().removeEventListener(this.zendeskEventListener);
		}
	}

	@ReactMethod
	public void setLoggable(Boolean enable, Integer logLevel) {
		Logger.setLoggable(enable);
	}
}
