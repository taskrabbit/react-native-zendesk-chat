/*
 *
 *  ZDCChatDataSource.h
 *  ZDCChat
 *
 *  Created by Zendesk on 28/10/2014.
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
#import "ZDCChatProfile.h"
#import "ZDCChatEvent.h"
#import "ZDCChatAgent.h"


/**
 * Protocol defining a chat data source. Messages received from the server
 * must be passed to the updateWithMessage:preNotification: method to update 
 * the data source. Observer methods should be used to register listeners for
 * chat events.
 */
@protocol ZDCChatDataSource <NSObject>


/**
 * Get the machine Id.
 * @return the machine id if set
 */
- (NSString*) machineId;

/**
 * Wipe all data from this session.
 */
- (void) endSession;


#pragma mark data


/**
 * Get the vistors profile from the data node.
 * @return the profile node
 */
- (ZDCChatProfile*) profile;

/**
 * Get the last visitor message sent.
 * @return the last visitor message if any
 */
- (ZDCChatEvent*) lastVisitorMessage;

/**
 * Get the last chat message sent by either the visitor or an agent
 * @return the last chat message if any
 */
- (ZDCChatEvent*) lastChatMessage;

/**
 * Get the agent message count for this session.
 * @return the number of agent messages received
 */
- (NSInteger) agentMessageCount;

/**
 * Get the log of the current chat.
 * @return an ordered array of ZDCChatEvent objects
 */
- (NSMutableArray*) livechatLog;

/**
 * Get the department list for this account.
 * @return the list of department names as NSString objects, if any
 */
- (NSMutableArray*) departments;

/**
 * Get list of agents on this conversation.
 * @return the dictionary of agents with nickname as key.
 */
- (NSDictionary*) agents;

/**
 * Get the agent record for the specified nickname.
 * @param nickname the agent to be found.
 */
- (ZDCChatAgent*) agentForNickname:(NSString*)nickname;

/**
 * Get the agent name for the specified nickname.
 * @param nickname the agent to be found.
 */
- (NSString*) agentNameForNickname:(NSString*)nickname;

/**
 * Check if the account is online and available for chat.
 * @return YES if the account is online.
 */
- (BOOL) accountOnline;

/**
 * Check if there is an offline message still pending.
 * @return YES if the message has not yet been confirmed
 */
- (BOOL) offlineMessagePending;

/**
 * Set the current chat rating.
 * @param rating the selected rating
 */
- (void) setChatRating:(ZDCChatRating)rating;

/**
 *  Check if file sending is enabled
 *  @return Yes if file sending is enabled
*/
- (BOOL) fileSendingEnabled;


#pragma mark server input


/**
 * Process server message.
 * @param message the received message
 * @param preNotification block for any pre-processing required
 */
- (void) updateWithMessage:(NSString*)message preNotification:(void (^)(NSString *, NSDictionary *))preNotification;

/**
 * Add a new file upload to the datasource.
 * @param fileUpload
 */
- (void) addFileUpload:(ZDCChatUpload*)fileUpload;


#pragma mark event observers


/**
 * Listen for chat events.
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forChatLogEvents:(SEL)selector;

/**
 * Remove chat observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForChatLogEvents:(id)target;

/**
 * Listen for agent events. Agent events include agent details and agent typing status.
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forAgentEvents:(SEL)selector;

/**
 * Remove typing observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForAgentEvents:(id)target;

/**
 * Listen for upload events, any listener must also remove themselves before deallocation.
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forUploadEvents:(SEL)selector;

/**
 * Remove upload observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForUploadEvents:(id)target;

/**
 * Listen for account events, any listener must also remove themselves before deallocation.
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forAccountEvents:(SEL)selector;

/**
 * Remove account observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForAccountEvents:(id)target;


@end

