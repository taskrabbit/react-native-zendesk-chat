declare module "react-native-zendesk-chat" {
	import {  NativeEventEmitter } from "react-native";

	export type User = {
		id: string;
		externalId: string;
	}

	export interface RNZendeskSDKMessaging {
		/**
		 * Must be called before calling loginUser/showMessaging/startObservingEvents
		 */
		initialize: (channelKey: string) => Promise<true>;

		/**
		 * Login user with ZendDesk
		 */
		loginUser: (jwt: string) => Promise<User>;

		/**
		 * Login user with ZendDesk
		 */
		logoutUser: () => Promise<true>;

		/**
		 * Presents the Zendesk Chat User Interface
		 */
		showMessaging: () => void;

		/**
		 * Dismiss the Zendesk Chat User Interface
		 */
		hideMessaging: () => void;

		/**
		 * Get unread message count
		 */
		getUnreadMessageCount: () => Promise<number>;

		/**
		 * Send page view event
		 */
		sendPageViewEvent: (pageTitle: string, withUrl: string) => Promise<true>;

		/**
		 * Start observing ZenDesk events. Needs to called before subscribing to events from JS
		 */
		startObservingEvents: () => void;

		/**
		 * Stop observing ZenDesk events.
		 */
		stopObservingEvents: () => void

		/**
		 * Invalidate
		 */
		invalidate: (clearStorage: boolean) => () => void;

		/**
		 * setLoggable
		 */
		setLoggable: (enable: boolean, level: number) => () => void;
	}

	export const RNZendeskSDKMessagingModule: RNZendeskSDKMessaging;
	export const RNZendeskSDKMessagingEventEmitter: NativeEventEmitter;
}
