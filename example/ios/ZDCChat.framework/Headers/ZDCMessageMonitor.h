/*
 *
 *  ZDCMessageMonitor.h
 *  ZDCChat
 *
 *  Created by Zendesk on 26/02/2015.
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
#import "ZDCChatEvent.h"
#import "ZDCVisitorChatCell.h"
#import "ZDCAgentOptionsCell.h"
#import "ZDCVisitorActionDelegate.h"


/**
 * Tracks all visitor messages for timeouts and handles resend timeouts/actions.
 */
@interface ZDCMessageMonitor : NSObject <ZDCChatCellActionDelegate>


/**
 * The current chat message list.
 */
@property (nonatomic, strong, readonly) NSArray *messages;

/**
 * Option view cache.
 */
@property (nonatomic, strong, readonly) NSMutableArray *optionViews;

/**
 * Cache for string sizes.
 */
@property (nonatomic, strong, readonly) NSMutableDictionary *sizeCache;

/**
 * The table presenting the chat messages.
 */
@property (nonatomic, strong) UITableView *table;

/**
 * Reference to the visitor action delegate.
 */
@property (nonatomic, weak) id<ZDCVisitorActionDelegate> actionDelegate;

/**
 * Map of timers currently waiting for message verification.
 */
@property (nonatomic, strong) NSMutableDictionary *timers;


/**
 * New instance.
 * @param table the table displaying the chat messages
 * @return the instance
 */
- (instancetype) initWithTable:(UITableView*)table;

/**
 * Notify the monitor that the messages have been updated.
 * @param sortedMessages the new message list
 */
- (void) messagesUpdated:(NSArray*)sortedMessages;

/**
 * Handle a resend request, updating the UI and sending the request to the chat session.
 * @param event the chat event to be resent
 */
- (void) resendMessage:(ZDCChatEvent*)event;

/**
 * The UI is being closed, stop monitoring timeouts.
 */
- (void) stopMonitoring;


@end

