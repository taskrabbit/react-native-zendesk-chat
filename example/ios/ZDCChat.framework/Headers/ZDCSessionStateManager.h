/*
 *
 *  ZDCSessionStateManager.h
 *  ZDCChat
 *
 *  Created by Zendesk on 13/11/2014.
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
#import "ZDCChatDataSource.h"
#import "ZDCPreChatData.h"


typedef NS_ENUM(NSUInteger, ZDCChatSessionStatus) {

    /// There is no active chat session
    ZDCChatSessionStatusInactive          = 0,

    /// A session has been started but no messages have been sent
    ZDCChatSessionStatusConnected         = 1,

    /// A session has been started and a message has been sent by the visitor
    ZDCChatSessionStatusChatting          = 2,

    /// The active session has timed out and should be ended
    ZDCChatSessionStatusTimedOut          = 3
};


/**
 * A chat session will only attempt to reconnect if all of the following conditions are met:
 *
 * <li>a session was in progress</li>
 * <li>at least one message has been sent by the visitor</li>
 * <li>no more than 'timeout' seconds have elapsed since the last visitor message was sent</li>
 */
@interface ZDCSessionStateManager : NSObject


#pragma mark session state

/**
 * Session status.
 */
@property (nonatomic, assign, readonly) ZDCChatSessionStatus status;

/**
 * The machine Id allows the session to reconnect to an in-progress chat.
 */
@property (nonatomic, strong, readonly) NSString *machineId;

/**
 * Timestamp of the last message sent by the visitor that was confirmed received by the server.
 */
@property (nonatomic, assign, readonly) NSTimeInterval lastVisitorMessage;

/**
 * Pending messages that have not yet been confirmed by the server.
 */
@property (nonatomic, strong, readonly) NSMutableArray *pendingMessages;

/**
 * The difference between the device clock and the server clock for the active chat session.
 * Add this to any event timestamp to obtain a time that can be compared to device time.
 */
@property (nonatomic, assign) NSTimeInterval clockSkew;

/**
 * Is file sending enabled. If enabled the user will be able to send images as attachments.
 */
@property (nonatomic, assign, readonly) BOOL fileSendingEnabled;


#pragma mark event observers


/**
 * Listen for timeout
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forTimeoutEvents:(SEL)selector;

/**
 * Remove timeout observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForTimeoutEvents:(id)target;


@end

