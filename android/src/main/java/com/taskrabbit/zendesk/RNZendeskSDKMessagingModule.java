package com.taskrabbit.zendesk;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.WritableArray;
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
import zendesk.messaging.android.internal.messagingscreen.MessagingActivity;

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

		this.applicationContext.registerActivityLifecycleCallbacks(new RNZendeskActivityTracker());
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
					WritableMap userMap = Arguments.createMap();
					userMap.putString("id", user.getId());
					userMap.putString("externalId", user.getExternalId());

					promise.resolve(userMap);
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
					promise.resolve(true);
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
		Activity activity = this.reactContext.getCurrentActivity();
		if (activity != null) {
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Zendesk.getInstance().getMessaging().showMessaging(activity);
				}
			});
		}
	}

	@ReactMethod
	public void hideMessaging() {
		Activity activity = RNZendeskActivityTracker.getCurrentActivity();
		if (activity instanceof MessagingActivity) {
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					activity.finish();
				}
			});
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
					WritableMap eventMap = Arguments.createMap();
					if (zendeskEvent instanceof ZendeskEvent.UnreadMessageCountChanged) {
						eventMap.putInt("unreadCount", ((ZendeskEvent.UnreadMessageCountChanged) zendeskEvent).getCurrentUnreadCount());
						sendEvent(reactContext, "ZDKZendeskEventUnreadMessageCountChanged", eventMap);
					} else if (zendeskEvent instanceof ZendeskEvent.AuthenticationFailed) {
						eventMap.putString("error", zendeskEvent.toString());
						sendEvent(reactContext, "ZDKZendeskEventAuthenticationFailed", eventMap);
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationAdded) {
						eventMap.putString("conversationId", ((ZendeskEvent.ConversationAdded) zendeskEvent).getConversationId());
						sendEvent(reactContext, "ZDKZendeskEventConversationAdded", eventMap);
					} else if (zendeskEvent instanceof ZendeskEvent.ConnectionStatusChanged) {
						eventMap.putString("connectionStatus",((ZendeskEvent.ConnectionStatusChanged) zendeskEvent).getConnectionStatus().toString());
						sendEvent(reactContext, "ZDKZendeskEventConnectionStatusChanged", eventMap);
					} else if (zendeskEvent instanceof ZendeskEvent.SendMessageFailed) {
						eventMap.putString("error", zendeskEvent.toString());
						sendEvent(reactContext, "ZDKZendeskEventSendMessageFailed", eventMap );
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationOpened) {
						eventMap.putString("id", ((ZendeskEvent.ConversationOpened) zendeskEvent).getId());
						eventMap.putString("timestamp",String.valueOf(((ZendeskEvent.ConversationOpened) zendeskEvent).getTimestamp()));
						eventMap.putString("conversationId",((ZendeskEvent.ConversationOpened) zendeskEvent).getConversationId());
						sendEvent(reactContext, "ZDKZendeskEventConversationOpened", eventMap );
					} else if (zendeskEvent instanceof ZendeskEvent.ConversationStarted) {
						eventMap.putString("id", ((ZendeskEvent.ConversationStarted) zendeskEvent).getId());
						eventMap.putString("timestamp",String.valueOf(((ZendeskEvent.ConversationStarted) zendeskEvent).getTimestamp()));
						eventMap.putString("conversationId",((ZendeskEvent.ConversationStarted) zendeskEvent).getConversationId());
						sendEvent(reactContext, "ZDKZendeskEventConversationStarted", eventMap );
					} else if (zendeskEvent instanceof ZendeskEvent.MessagesShown) {
						eventMap.putString("id", ((ZendeskEvent.MessagesShown) zendeskEvent).getId());
						eventMap.putString("timestamp",String.valueOf(((ZendeskEvent.MessagesShown) zendeskEvent).getTimestamp()));
						eventMap.putString("conversationId",((ZendeskEvent.MessagesShown) zendeskEvent).getConversationId());
						WritableArray messageArray = Arguments.createArray();
						((ZendeskEvent.MessagesShown) zendeskEvent).getMessages().forEach(message -> {
							WritableMap messageMap = Arguments.createMap();
							messageMap.putString("id", message.getId());
							messageMap.putString("role", message.getRole().toString());
							messageMap.putString("timestamp", String.valueOf(message.getTimestamp()));
							messageArray.pushMap(messageMap);
						});
						eventMap.putArray("messages", messageArray);
						sendEvent(reactContext, "ZDKZendeskEventMessagesShown", eventMap );
					} else if (zendeskEvent instanceof ZendeskEvent.FieldValidationFailed) {
						eventMap.putString("error", zendeskEvent.toString());
						sendEvent(reactContext, "ZDKZendeskEventFieldValidationFailed", eventMap );
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
