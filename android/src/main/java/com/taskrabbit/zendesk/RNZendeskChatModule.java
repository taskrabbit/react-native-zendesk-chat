package com.taskrabbit.zendesk;

import android.app.Activity;
import android.content.Intent;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.zopim.android.sdk.api.ZopimChat;
import com.zopim.android.sdk.prechat.PreChatForm;
import com.zopim.android.sdk.model.VisitorInfo;
import com.zopim.android.sdk.prechat.ZopimChatActivity;

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
        if (options.getType(key) != ReadableArray) {
            Log.e(RNZendeskChatModule.TAG, "wrong type for key '" + key + "' when processing " + functionHint
                    + ", expected an Array of Strings.");
            return result;
        }
        ReadableArray arr = options.getArray(key);
        for (int i = 0; i < arr.size(); i++) {
            if (arr.isNull(i)) {
                continue;
            }
            if (arr.getType() != String) {
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
        if (options.getType(key) != String) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected a String.");
            return null;
        }
        return options.getString(key);
    }

    public static boolean getBooleanOrDefault(ReadableMap options, String key, String functionHint,
            boolean defaultValue) {
        if (!options.hasKey(key)) {
            return defaultValue;
        }
        if (options.getType(key) != Boolean) {
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
        if (options.getType(key) != String) {
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
            return new ReadableMap();
        }
        if (options.getType(key) != ReadableMap) {
            Log.e(RNZendeskChatModule.TAG,
                    "wrong type for key '" + key + "' when processing " + functionHint + ", expected a config hash.");
            return new ReadableMap();
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
        VisitorInfo.Builder builder = new VisitorInfo.Builder();

        String name = getStringOrNull(options, "name", "visitorInfo");
        if (name != null) {
            builder = builder.withName(name);
        }
        String email = getStringOrNull(options, "email", "visitorInfo");
        if (email != null) {
            builder = builder.withEmail(name);
        }
        String phone = getStringOrNull(options, "phone", "visitorInfo");
        if (phone != null) {
            builder = builder.withPhoneNumber(phone);
        }

        VisitorInfo visitorData = builder.build();

        Chat.INSTANCE.providers().profileProvider().setVisitorInfo(visitorData);
    }

    @ReactMethod
    public void init(String key) {
        Chat.INSTANCE.init(mReactContext, key);
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
        PreChatFormFieldStatus defaultValue = preChatFormFieldStatus.OPTIONAL;
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

        ChatProfileProvider profileProvider = Chat.INSTANCE.providers().profileProvider();
        ArrayList<String> activeTags = currentUserTags.clone();

        ArrayList<String> allProvidedTags = RNZendeskChatModule.getArrayListOfStrings(options, "tags", "startChat");
        ArrayList<String> newlyIntroducedTags = allProvidedTags.clone();

        newlyIntroducedTags.remove(activeTags); // Now just includes tags to add
        currentUserTags.removeAll(allProvidedTags); // Now just includes tags to delete

        if (!currentUserTags.isEmpty()) {
            profileProvider.removeVisitorTags(currentUserTags);
        }
        if (!newlyIntroducedTags.isEmpty()) {
            profileProvider.addVisitorTags(newlyIntroducedTags);
        }

        currentUserTags = allProvidedTags;
    }

    private Object loadBotSettings(ReadableMap options, Object builder) {
        return builder;
    }

    @ReactMethod
    public void startChat(ReadableMap options) {
        setVisitorInfo(options);

        ReadableMap flagHash = RNZendeskChatModule.getReadableMap(options, "behaviorFlags", "startChat");
        boolean showPreChatForm = getBooleanOrDefault(flagHash, "showPreChatForm", "startChat(behaviorFlags)", true);

        ChatConfiguration.Builder chatBuilder = loadBehaviorFlags(ChatConfiguration.builder(), flagHash);
        if (showPreChatForm) {
            chatBuilder = loadPreChatFormConfiguration(chatBuilder,
                    getReadableMap(options, "preChatFormOptions", "startChat"));
        }
        ChatConfiguration = chatBuilder.build();

        String department = RNZendeskChatModule.getStringOrNull(options, "department", "startChat");
        if (department) {
            Chat.INSTANCE.providers().chatProvider().setDepartment(department, null);
        }

        loadTags(options);

        Object messagingBuilder = loadBotSettings(getReadableMap(options, "messagingOptions", "startChat"),
                MessagingActivity.builder());

        Activity activity = getCurrentActivity();
        if (activity != null) {
            messagingBuilder.withEngines(ChatEngine.engine()).show(view.getContext());
        }
    }
}
