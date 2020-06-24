declare module "react-native-zendesk-chat" {
	interface VisitorInfoOptions {
		name?: string;
		email?: string;
		phone?: string;

		/** only implemented on iOS */
		shouldPersist?: boolean;
	}
	interface StartChatOptions_iOS extends VisitorInfoOptions {
		department?: string;
		tags?: string[];

		// Flags to disable some fields collected by default.
		emailNotRequired?: boolean;
		phoneNotRequired?: boolean;
		departmentNotRequired?: boolean;
		messageNotRequired?: boolean;
	}
	type StartChatOptions_Android = VisitorInfoOptions;
	type StartChatOptions = StartChatOptions_iOS & StartChatOptions_Android;

	class RNZendeskChatModuleImpl {
		init: (zendeskAccountKey: string) => void;

		setVisitorInfo: (options: VisitorInfoOptions) => void;

		startChat: (options: StartChatOptions) => void;
	}

	const RNZendeskChatModule: RNZendeskChatModuleImpl;

	export default RNZendeskChatModule;
}
