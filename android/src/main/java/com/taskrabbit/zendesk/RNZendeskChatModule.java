package com.taskrabbit.zendesk;

import android.app.Activity;
import android.util.Log;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;
import com.facebook.react.bridge.WritableNativeMap;
import zendesk.chat.Chat;
import zendesk.chat.ChatConfiguration;
import zendesk.chat.ProfileProvider;
import zendesk.chat.PreChatFormFieldStatus;
import zendesk.chat.ChatEngine;
import zendesk.chat.VisitorInfo;
import zendesk.messaging.MessagingActivity;
import zendesk.messaging.MessagingConfiguration;

import java.lang.String;
import java.util.ArrayList;

public class RNZendeskChatModule extends ReactContextBaseJavaModule {
    private static final String TAG = "[RNZendeskChatModule]";

    private ArrayList<String> currentUserTags = new ArrayList();

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
        VisitorInfo.Builder builder = VisitorInfo.builder();

        String name = getStringOrNull(options, "name", "visitorInfo");
        if (name != null) {
            builder = builder.withName(name);
        }
        String email = getStringOrNull(options, "email", "visitorInfo");
        if (email != null) {
            builder = builder.withEmail(email);
        }
        String phone = getStringOrNull(options, "phone", "visitorInfo");
        if (phone != null) {
            builder = builder.withPhoneNumber(phone);
        }

        VisitorInfo visitorData = builder.build();

        if (Chat.INSTANCE.providers() == null) {
            Log.e(TAG,
                    "Zendesk Internals are undefined -- did you forget to call RNZendeskModule.init(<account_key>)?");
            return;
        }
        Chat.INSTANCE.providers().profileProvider().setVisitorInfo(visitorData, null);
    }

    @ReactMethod
    public void init(String key) {
        Chat.INSTANCE.init(mReactContext, key);
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
        setVisitorInfo(options);

        ReadableMap flagHash = RNZendeskChatModule.getReadableMap(options, "behaviorFlags", "startChat");
        boolean showPreChatForm = getBooleanOrDefault(flagHash, "showPreChatForm", "startChat(behaviorFlags)", true);

        ChatConfiguration.Builder chatBuilder = loadBehaviorFlags(ChatConfiguration.builder(), flagHash);
        if (showPreChatForm) {
            chatBuilder = loadPreChatFormConfiguration(chatBuilder,
                    getReadableMap(options, "preChatFormOptions", "startChat"));
        }
        ChatConfiguration chatConfig = chatBuilder.build();

        String department = RNZendeskChatModule.getStringOrNull(options, "department", "startChat");
        if (department != null) {
            Chat.INSTANCE.providers().chatProvider().setDepartment(department, null);
        }

        loadTags(options);

        MessagingConfiguration.Builder messagingBuilder = loadBotSettings(
                getReadableMap(options, "messagingOptions", "startChat"), MessagingActivity.builder());

        Activity activity = getCurrentActivity();
        if (activity != null) {
            messagingBuilder.withEngines(ChatEngine.engine()).show(activity, chatConfig);
        } else {
            Log.e(TAG, "Could not load getCurrentActivity -- no UI can be displayed without it.");
        }
    }
}
