/*
 *
 *  ZDCChatUIController.h
 *  ZDCChat
 *
 *  Created by Zendesk on 27/01/2015.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import <Foundation/Foundation.h>


/**
 * Enum defining the primary chat UI states.
 */
typedef NS_ENUM(NSUInteger, ZDCChatUIState) {

    /// The initial full screen loader.
    ZDCChatUIStateLoading               = 0,

    /// Full screen 'No connection' screen.
    ZDCChatUIStateNoConnection          = 1,

    /// Full screen 'Could not connect'.
    ZDCChatUIStateCouldNotConnect       = 2,

    /// Full screen 'No agents available' screen.
    ZDCChatUIStateNoAgents              = 3,

    /// Offline message form.
    ZDCChatUIStateOfflineForm           = 4,

    /// Pre-chat form.
    ZDCChatUIStatePreChatForm           = 5,

    /// Chat screen.
    ZDCChatUIStateChat                  = 6,

    /// Chat screen, timed out.
    ZDCChatUIStateChatTimedOut          = 7
};


/**
 * Chat UI delegate for handling/presenting status messages and presenting/dismissing the UI.
 * The ZDCChatUIController should also provide the controls for minimising and ending a chat.
 */
@protocol ZDCChatUIController <NSObject>


#pragma mark actions


/**
 * Show the chat UI.
 * @param navController the UINavigationController from which to present the UI,
 if nil the top view controller will be used
 */
- (void) presentIn:(UINavigationController*)navController;

/**
 * Dismiss the chat UI.
 */
- (void) dismiss;

/**
 * Set the enabled state of the offline message send button, used during offline message submission.
 * @param enabled BOOL value to set
 */
- (void) enableOfflineMessageSendButton:(BOOL)enabled;


#pragma mark state updates


/**
 * Notification that the chat has changed state.
 * @param state
 */
- (void) stateTransitionTo:(ZDCChatUIState)state;


#pragma mark connection state


/**
 * Show the 'No connection' toast if the reachability toast is not already active.
 */
- (void) showConnectionToast;

/**
 * Notify the visitor that the chat session is reconnecting.
 */
- (void) showReconnectingToast;

/**
 * Dismiss the toast if present.
 */
- (void) dismissToast;


@end

