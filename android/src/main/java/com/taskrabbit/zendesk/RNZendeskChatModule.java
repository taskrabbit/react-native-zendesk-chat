package com.taskrabbit.zendesk;

import android.app.Activity;
import android.content.pm.ApplicationInfo;
import android.util.Log;

import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;
import com.facebook.react.bridge.WritableNativeMap;

import zendesk.chat.Account;
import zendesk.chat.AccountStatus;
import zendesk.chat.Chat;
import zendesk.chat.ChatConfiguration;
import zendesk.chat.ChatEngine;
import zendesk.chat.ChatSessionStatus;
import zendesk.chat.ChatState;
import zendesk.chat.ObservationScope;
import zendesk.chat.Observer;
import zendesk.chat.ProfileProvider;
import zendesk.chat.PreChatFormFieldStatus;
import zendesk.chat.PushNotificationsProvider;
import zendesk.chat.VisitorInfo;
import zendesk.messaging.MessagingActivity;
import zendesk.messaging.MessagingConfiguration;
import com.zendesk.service.ErrorResponse;
import com.zendesk.service.ZendeskCallback;

import java.lang.String;
import java.util.ArrayList;

public class RNZendeskChatModule extends ReactContextBaseJavaModule {
    private static final String TAG = "[RNZendeskChatModule]";

    private ArrayList<String> currentUserTags = new ArrayList();

    private ReadableMap pendingVisitorInfo = null;
    private ObservationScope observationScope = null;

    // private class Converters {
    public static ArrayList<String> getArrayListOfStrings(ReadableMap options, String key, String functionHint) {
        ArrayList<String> result = new ArrayList();

        if (!options.hasKey(key)) {
            return result;
        }
        if (options.getType(key) != ReadableType.Array) {
            Log.e(RNZendeskChatModule.TAG, "wrong type for key '" + key + "' when processing " + functionHint
                    + ", expected an Array of Strings.");
            return result;
        }
        ReadableArray arr = options.getArray(key);
        for (int i = 0; i < arr.size(); i++) {
            if (arr.isNull(i)) {
                continue;
            }
            if (arr.getType(i) != ReadableType.String) {
                Log.e(RNZendeskChatModule.TAG, "wrong type for key '" + key + "[" + i + "]' when processing "
                        + functionHint + ", expected entry to be a String.");
            }
            result.add(arr.getString(i));
        }
        return result;
    }

    public static String getStringOrNull(ReadableMap options, String key, String functionHint) {
        if (!options.hasKey(key)) {
            return null;
        }
        if (options.getType(key) != ReadableType.String) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected a String.");
            return null;
        }
        return options.getString(key);
    }

    public static int getIntOrDefault(ReadableMap options, String key, String functionHint, int defaultValue) {
        if (!options.hasKey(key)) {
            return defaultValue;
        }
        if (options.getType(key) != ReadableType.String) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected an Integer.");
            return defaultValue;
        }
        return options.getInt(key);
    }

    public static boolean getBooleanOrDefault(ReadableMap options, String key, String functionHint,
            boolean defaultValue) {
        if (!options.hasKey(key)) {
            return defaultValue;
        }
        if (options.getType(key) != ReadableType.Boolean) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected a Boolean.");
            return defaultValue;
        }
        return options.getBoolean(key);
    }

    public static PreChatFormFieldStatus getFieldStatusOrDefault(ReadableMap options, String key,
            PreChatFormFieldStatus defaultValue) {
        if (!options.hasKey(key)) {
            return defaultValue;
        }
        if (options.getType(key) != ReadableType.String) {
            Log.e(RNZendeskChatModule.TAG, "wrong type for key '" + key
                    + "' when processing startChat(preChatFormOptions), expected one of ('required' | 'optional' | 'hidden').");
            return defaultValue;
        }
        switch (options.getString(key)) {
            case "required":
                return PreChatFormFieldStatus.REQUIRED;
            case "optional":
                return PreChatFormFieldStatus.OPTIONAL;
            case "hidden":
                return PreChatFormFieldStatus.HIDDEN;
            default:
                Log.e(RNZendeskChatModule.TAG, "wrong type for key '" + key
                        + "' when processing startChat(preChatFormOptions), expected one of ('required' | 'optional' | 'hidden').");
                return defaultValue;
        }
    }

    public static ReadableMap getReadableMap(ReadableMap options, String key, String functionHint) {
        if (!options.hasKey(key)) {
            return new WritableNativeMap();
        }
        if (options.getType(key) != ReadableType.Map) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected a config hash.");
            return new WritableNativeMap();
        }
        return options.getMap(key);
    }

    private void selectVisitorInfoFieldIfPreChatFormHidden(String key, WritableNativeMap output, ReadableMap input, ReadableMap shouldInclude) {
        if ((!input.hasKey(key) || input.getType(key) != ReadableType.String)
            || (shouldInclude.hasKey(key) && shouldInclude.getType(key) == ReadableType.String && !"hidden".equals(shouldInclude.getString(key))) ) {
            return;
        }

        String value = input.getString(key);
        if (((mReactContext.getApplicationInfo().flags
            & ApplicationInfo.FLAG_DEBUGGABLE) == 0)) {
            // We don't want other Apps to monitor our app's production logs for this debug information.
            // If you patch the app to enable it yourself, that's your choice!
            value = "<stripped>";
        }

        Log.d(TAG, "selectVisitorInfo to set later " + key + " '" + value + "'");
        output.putString(key, input.getString(key));
    }
    // }

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
        _setVisitorInfo(options);
    }
    private boolean _setVisitorInfo(ReadableMap options) {
        boolean anyValuesWereSet = false;
        VisitorInfo.Builder builder = VisitorInfo.builder();

        String name = getStringOrNull(options, "name", "visitorInfo");
        if (name != null) {
            builder = builder.withName(name);
            anyValuesWereSet = true;
        }
        String email = getStringOrNull(options, "email", "visitorInfo");
        if (email != null) {
            builder = builder.withEmail(email);
            anyValuesWereSet = true;
        }
        String phone = getStringOrNull(options, "phone", "visitorInfo");
        if (phone != null) {
            builder = builder.withPhoneNumber(phone);
            anyValuesWereSet = true;
        }

        VisitorInfo visitorInfo = builder.build();

        if (Chat.INSTANCE.providers() == null) {
            Log.e(TAG,
                    "Zendesk Internals are undefined -- did you forget to call RNZendeskModule.init(<account_key>)?");
            return false;
        }

        Chat.INSTANCE.providers().profileProvider().setVisitorInfo(visitorInfo, null);

        return anyValuesWereSet;
    }

    // Unfortunately, react-native: android doesn't support the following
    // - Java's Method Overloading
    // - automatically providing null to undefined parameters (like iOS)
    //
    // As a result, we need to guarantee this is always called with 2 parameters from JS
    //
    // This method has been renamed to make that clear, and index.js is adding the
    //  correct interface for init() at runtime
    @ReactMethod
    public void _initWith2Args(String key, String appId) {
        if (appId != null) {
            Chat.INSTANCE.init(mReactContext, key, appId);
        } else {
            Chat.INSTANCE.init(mReactContext, key);
        }
        Log.d(TAG, "Chat.INSTANCE was properly initialized from JS.");
    }

    private ChatConfiguration.Builder loadBehaviorFlags(ChatConfiguration.Builder b, ReadableMap options) {
        boolean defaultValue = true;
        String logHint = "startChat(behaviorFlags)";

        return b.withPreChatFormEnabled(getBooleanOrDefault(options, "showPreChatForm", logHint, defaultValue))
                .withTranscriptEnabled(getBooleanOrDefault(options, "showChatTranscriptPrompt", logHint, defaultValue))
                .withOfflineFormEnabled(getBooleanOrDefault(options, "showOfflineForm", logHint, defaultValue))
                .withAgentAvailabilityEnabled(
                        getBooleanOrDefault(options, "showAgentAvailability", logHint, defaultValue));
    }

    private ChatConfiguration.Builder loadPreChatFormConfiguration(ChatConfiguration.Builder b, ReadableMap options) {
        PreChatFormFieldStatus defaultValue = PreChatFormFieldStatus.OPTIONAL;
        return b.withNameFieldStatus(getFieldStatusOrDefault(options, "name", defaultValue))
                .withEmailFieldStatus(getFieldStatusOrDefault(options, "email", defaultValue))
                .withPhoneFieldStatus(getFieldStatusOrDefault(options, "phone", defaultValue))
                .withDepartmentFieldStatus(getFieldStatusOrDefault(options, "department", defaultValue));
    }
    // Produces a ReadableMap suitable for passing to setVisitorInfo that only has the fields that won't be asked by the preChatForm
    private ReadableMap hiddenVisitorInfoData(ReadableMap allVisitorInfo, ReadableMap preChatFormOptions) {
        WritableNativeMap output = new WritableNativeMap();
        selectVisitorInfoFieldIfPreChatFormHidden("email", output, allVisitorInfo, preChatFormOptions);
        selectVisitorInfoFieldIfPreChatFormHidden("name", output, allVisitorInfo, preChatFormOptions);
        selectVisitorInfoFieldIfPreChatFormHidden("phone", output, allVisitorInfo, preChatFormOptions);
        return output;
    }

    private void loadTags(ReadableMap options) {
        // ZendeskChat Android treats the tags persistently, so you have to add/remove
        // as things change -- aka doing a diff :-(
        // ZendeskChat iOS just lets you override the full array so this isn't
        // necessary on that side.
        if (Chat.INSTANCE.providers() == null) {
            Log.e(TAG,
                    "Zendesk Internals are undefined -- did you forget to call RNZendeskModule.init(<account_key>)?");
            return;
        }

        ProfileProvider profileProvider = Chat.INSTANCE.providers().profileProvider();
        ArrayList<String> activeTags = (ArrayList<String>) currentUserTags.clone();

        ArrayList<String> allProvidedTags = RNZendeskChatModule.getArrayListOfStrings(options, "tags", "startChat");
        ArrayList<String> newlyIntroducedTags = (ArrayList<String>) allProvidedTags.clone();

        newlyIntroducedTags.remove(activeTags); // Now just includes tags to add
        currentUserTags.removeAll(allProvidedTags); // Now just includes tags to delete

        if (!currentUserTags.isEmpty()) {
            profileProvider.removeVisitorTags(currentUserTags, null);
        }
        if (!newlyIntroducedTags.isEmpty()) {
            profileProvider.addVisitorTags(newlyIntroducedTags, null);
        }

        currentUserTags = allProvidedTags;
    }

    private MessagingConfiguration.Builder loadBotSettings(ReadableMap options,
            MessagingConfiguration.Builder builder) {
        if (options == null) {
            return builder;
        }
        String botName = getStringOrNull(options, "botName", "loadBotSettings");
        if (botName != null) {
            builder = builder.withBotLabelString(botName);
        }
        int avatarDrawable = getIntOrDefault(options, "botAvatarDrawableId", "loadBotSettings", -1);
        if (avatarDrawable != -1) {
            builder = builder.withBotAvatarDrawable(avatarDrawable);
        }

        return builder;
    }

    @ReactMethod
    public void startChat(ReadableMap options) {
        if (Chat.INSTANCE.providers() == null) {
            Log.e(TAG,
                    "Zendesk Internals are undefined -- did you forget to call RNZendeskModule.init(<account_key>)?");
            return;
        }
        pendingVisitorInfo = null;
        boolean didSetVisitorInfo = _setVisitorInfo(options);

        ReadableMap flagHash = RNZendeskChatModule.getReadableMap(options, "behaviorFlags", "startChat");

        boolean showPreChatForm = getBooleanOrDefault(flagHash, "showPreChatForm", "startChat(behaviorFlags)", true);
        boolean needsToSetVisitorInfoAfterChatStart = showPreChatForm && didSetVisitorInfo;

        ChatConfiguration.Builder chatBuilder = loadBehaviorFlags(ChatConfiguration.builder(), flagHash);
        if (showPreChatForm) {
            ReadableMap preChatFormOptions = getReadableMap(options, "preChatFormOptions", "startChat");
            chatBuilder = loadPreChatFormConfiguration(chatBuilder, preChatFormOptions);
            pendingVisitorInfo = hiddenVisitorInfoData(options, preChatFormOptions);
        }
        ChatConfiguration chatConfig = chatBuilder.build();

        String department = RNZendeskChatModule.getStringOrNull(options, "department", "startChat");
        if (department != null) {
            Chat.INSTANCE.providers().chatProvider().setDepartment(department, null);
        }

        loadTags(options);

        MessagingConfiguration.Builder messagingBuilder = loadBotSettings(
                getReadableMap(options, "messagingOptions", "startChat"), MessagingActivity.builder());

        if (needsToSetVisitorInfoAfterChatStart) {
            setupChatStartObserverToSetVisitorInfo();
        }

        Activity activity = getCurrentActivity();
        if (activity != null) {
            messagingBuilder.withEngines(ChatEngine.engine()).show(activity, chatConfig);
        } else {
            Log.e(TAG, "Could not load getCurrentActivity -- no UI can be displayed without it.");
        }
    }

    @ReactMethod
    public void registerPushToken(String token) {
        PushNotificationsProvider pushProvider = Chat.INSTANCE.providers().pushNotificationsProvider();

        if (pushProvider != null) {
            pushProvider.registerPushToken(token);
        }
    }

    // https://support.zendesk.com/hc/en-us/articles/360055343673
    public void setupChatStartObserverToSetVisitorInfo(){
        // Create a temporary observation scope until the chat is started.
        observationScope = new ObservationScope();
        Chat.INSTANCE.providers().chatProvider().observeChatState(observationScope, new Observer<ChatState>() {
            @Override
            public void update(ChatState chatState) {
                ChatSessionStatus chatStatus = chatState.getChatSessionStatus();
                // Status achieved after the PreChatForm is completed
                if (chatStatus == ChatSessionStatus.STARTED) {
                    observationScope.cancel(); // Once the chat is started disable the observation
                    observationScope = null; // Clean things up to avoid confusion.
                    if (pendingVisitorInfo == null) { return; }

                    // Update the information MID chat here. All info but Department can be updated
                    // Add here the code to set the selected visitor info *after* the preChatForm is complete
                    _setVisitorInfo(pendingVisitorInfo);
                    pendingVisitorInfo = null;

                    Log.d(TAG, "Set the VisitorInfo after chat start");
                } else {
                    // There are few other statuses that you can observe but they are unused in this example
                    Log.d(TAG, "[observerSetup] - ChatSessionUpdate -> (unused) status : " + chatStatus.toString());
                }
            }
        });
    }

    @ReactMethod
    public void areAgentsOnline(final Promise promise) {
        Chat.INSTANCE.providers().accountProvider().getAccount(new ZendeskCallback<Account>() {
            @Override
            public void onSuccess(Account account) {
                AccountStatus status = account.getStatus();

                switch (status) {
                    case ONLINE:
                        promise.resolve(true);
                        break;

                    default:
                        promise.resolve(false);
                        break;
                }
            }

            @Override
            public void onError(ErrorResponse errorResponse) {
                promise.reject("no-available-zendesk-account", "DevError: Not connected to Zendesk or network issue");
            }
        });
    }
}
