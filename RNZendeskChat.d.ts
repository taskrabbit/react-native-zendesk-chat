declare module "react-native-zendesk-chat" {
	interface VisitorInfoOptions {
		name?: string;
		email?: string;
		phone?: string;
	}

	interface MessagingOptionsCommon {
		/** Set this to set the bot's displayName */
		botName?: string;
	}
	interface MessagingOptions_iOS extends MessagingOptionsCommon {
		/** Will be loaded using [UIImage imageWithName:…] ) */
		botAvatarName?: string;
		/** Will be loaded using [UIImage imageWithData:[NSData dataWithContentsOfUrl:…]] */
		botAvatarUrl?: string;
	}
	interface MessagingOptions_Android extends MessagingOptionsCommon {
		/** Will be loaded from your native asset resources */
		botAvatarDrawableId?: number;
	}

	/** Current default is "optional" */
	type PreChatFormFieldOptionVisibility = "hidden" | "optional" | "required";

	interface StartChatOptions extends VisitorInfoOptions {
		department?: string;
		tags?: string[];

		behaviorFlags?: {
			/**
			 * if omitted, the form is enabled
			 *
			 * @warning Android: If you enable preChat form with `required` or `optional` for keys
			 * 	Then any visitor info you provide statically as VisitorInfoOptions will be ignored.
			 * 	This is documented upstream here: https://support.zendesk.com/hc/en-us/articles/360055343673
			 */
			showPreChatForm?: boolean;
			/** if omitted, the prompt is enabled */
			showChatTranscriptPrompt?: boolean;
			/** if omitted, the form is enabled */
			showOfflineForm?: boolean;
			/** if omitted, the agent availability message is enabled */
			showAgentAvailability?: boolean;
		};

		/**
		 * If omitted, the preChatForm will be left as default in Zendesk, be explicit if you want control.
		 *
		 * @warning Android: If you provide the preChat form with `required` or `optional` for keys
		 * 	Then any visitor info you provide statically as VisitorInfoOptions will be ignored.
		 * 	This is documented upstream here: https://support.zendesk.com/hc/en-us/articles/360055343673
		 */
		preChatFormOptions?: {
			/** Should we ask the user for a contact email? */
			email?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user their name? */
			name?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user for their phone number? */
			phone?: PreChatFormFieldOptionVisibility;
			/** Should we ask the user which department? */
			department?: PreChatFormFieldOptionVisibility;
		};

		/**
		 * JWT Authentication options. All values must be present to enable JWT authentication
		 *
		 * For details see: https://developer.zendesk.com/documentation/classic-web-widget-sdks/chat-sdk-v2/working-with-the-chat-sdk/enabling-authenticated-users-with-the-chat-sdk-/#creating-a-jwt-token
		 */
		authenticationOptions?:
			| {
					/**
					 * The endpoint on your server to send the JWT request to.
					 *
					 * The Request looks as follows:
					 *
					 * ```shell
					 * curl --request POST --url <tokenEndpoint> --header 'Content-Type application/json' --data '{ "externalId": <externalId> }'
					 * ```
					 *
					 * Your endpoint is expected to return a JSON response with the shape:
					 *
					 * ```JSON
					 * { "jwt": "-the-jwt-" }
					 * ```
					 */
					tokenEndpoint: string | undefiend;

					/**
					 * The identifier sent as part of the JWT request used to identify the user
					 * on your server.
					 */
					externalId: string | undefined;

					/**
					 * Headers to be passed along with any HTTP request made
					 * to the endpoint above.
					 */
					headers?: Record<string, string>;
			  }
			| {
					/**
					 * A prefetched JWT for the current session
					 */
					jwt: string;
			  };

		/**
		 * Configure the Chat-Bot (if any)
		 */
		messagingOptions?: MessagingOptions_iOS & MessagingOptions_Android;

		/**
		 * If not provided, this will be "Close" -- not localized!
		 *
		 * -- iOS Only (Android: shows just a Back Button)
		 */
		localizedDismissButtonTitle?: string;
	}

	class RNZendeskChatModuleImpl {
		/**
		 * Must be called before calling startChat/setVisitorInfo
		 * - (Advanced users may configure this natively instead of calling this from JS)
		 */
		init: (zendeskAccountKey: string, appId?: string) => void;

		/**
		 * Presents the Zendesk Chat User Interface
		 */
		startChat: (options: StartChatOptions) => void;
		/**
		 * Backwards Compatibility!
		 * - You can pass all these parameters to RNZendeskChatModule.startChat
		 * - So you should probably prefer that method
		 */
		setVisitorInfo: (options: VisitorInfoOptions) => void;

		/**
		 * Configure the token to start receiving Push Notifications
		 */
		registerPushToken: (token: string) => void;

		/**
		 * Check if there are available agents
		 */
		areAgentsOnline: () => Promise<Boolean>;
	}

	const RNZendeskChatModule: RNZendeskChatModuleImpl;

	export default RNZendeskChatModule;
}
