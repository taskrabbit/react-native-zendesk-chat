import { NativeModules, Platform } from "react-native";

const RNZendeskChatModule = NativeModules.RNZendeskChatModule;

Platform.select({
	default: () => {
		return;
	},
	android: () => {
		// react-native android doesn't support Java method overloading
		// So this code implements the init method but makes sure to call
		//  the right Java Code making sure there's a value for each parameter
		// Reference: https://github.com/facebook/react-native/blob/07d090dbc6c46b8f3760dbd25dbe0540c18cb3f3/ReactAndroid/src/main/java/com/facebook/react/bridge/JavaModuleWrapper.java#L85-L86
		RNZendeskChatModule.init = (key, appId) => {
			return RNZendeskChatModule._initWith2Args(key, appId || null);
		};
	},
})();

/**
 * TypeScript Documentation for this Module describes the available methods & parameters
 *
 * @see { ./RNZendeskChat.d.ts }
 */
export default RNZendeskChatModule;
