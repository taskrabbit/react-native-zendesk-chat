declare module "react-native-zendesk-chat" {
	interface VisitorInfoOptions {
		name?: string;
		email?: string;
		phone?: string;
	}

	interface MessagingOptions_iOS {
		/** Set this to set the bot's displayName */
		botName?: string;
		/** Will be loaded using [UIImage imageWithName:…] ) */
		botImageName?: string;
		/** Will be loaded using [UIImage imageWithUrl:…] */
		botImageUrl?: string;
	}

	const enum PreChatFormFieldOptionVisibility {
		hidden = "hidden",
		optional = "optional",
		required = "required",
	}

	interface StartChatOptions extends VisitorInfoOptions {
		department?: string;
		tags?: string[];

		behaviorFlags?: {
			/** if omitted, the form is enabled */
			showPreChatForm?: boolean;
			/** if omitted, the prompt is enabled */
			showChatTranscriptPrompt?: boolean;
			/** if omitted, the form is enabled */
			showOfflineForm?: boolean;
			/** if omitted, the agent availability message is enabled */
			showAgentAvailability?: boolean;
		};

		/** If omitted, the preChatForm will be left as default in Zendesk */
		preChatFormOptions?: {
			/** Should we ask the user for a contact email? */
			email?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user their name? */
			name?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user for their phone number? */
			phoneNumber?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user which department? */
			department?: PreChatFormFieldOptionVisibility;
		};

		/**
		 * Configure the Chat-Bot (if any)
		 */
		messagingOptions?: MessagingOptions_iOS;

		/**
		 * If not provided, this will be "Close" -- not localized!
		 */
		localizedDismissButtonTitle?: string;
	}

	class RNZendeskChatModuleImpl {
		init: (zendeskAccountKey: string) => void;

		startChat: (options: StartChatOptions) => void;
		/**
		 * Backwards Compatibility!
		 * - You can pass all these parameters to RNZendeskChatModule.startChat
		 * - So you should probably prefer that method
		 */
		setVisitorInfo: (options: VisitorInfoOptions) => void;
	}

	const RNZendeskChatModule: RNZendeskChatModuleImpl;

	export default RNZendeskChatModule;
}
