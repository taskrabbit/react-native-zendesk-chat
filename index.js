import { NativeModules, NativeEventEmitter } from "react-native";

/**
 * TypeScript Documentation for this Module describes the available methods & parameters
 *
 * @see { ./RNZendeskSDKMessaging.d.ts }
 */
export const RNZendeskSDKMessagingModule = NativeModules.RNZendeskSDKMessagingModule;
export const RNZendeskSDKMessagingEventEmitter = new NativeEventEmitter(RNZendeskSDKMessagingModule);
