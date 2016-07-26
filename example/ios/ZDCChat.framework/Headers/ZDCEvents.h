/*
 *
 *  ZDCEvents.h
 *  ZDCChat
 *
 *  Created by Zendesk on 20/09/2014.
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
 * Event tracking class for storing the event, URL and creation timestamp.
 */
@interface ZDCEventEntry : NSObject


@property (nonatomic, strong) NSString * event;
@property (nonatomic, strong) NSString *url;
@property (nonatomic, assign) long timestamp;


@end


#pragma mark -


/**
 * Event/breadcrumb tracking class; you can add events, notify events have been synchronized with
 * the server and notify that a new session has been started.
 */
@interface ZDCEvents : NSObject


/**
 * New instance.
 * @param maxSIze the maximum capacity of the events list
 */
- (instancetype) initWithMaxSize:(int)maxSize;

/**
 * Add an event to the tracked list.
 *
 * @param event the event string to be added
 * @return the created event entry
 */
- (ZDCEventEntry*) trackEvent:(NSString*)event;

/**
 * Add an event to the tracked list.
 *
 * @param event the event string to be added
 * @param url the app URL corresponding to this event
 * @return the created event entry
 */
// Reserved for future use.
//- (ZDCEventEntry*) trackEvent:(NSString*)event withURL:(NSString*)url;

/**
 * Get all outstanding events which are waiting to be sent to the server.
 *
 * @return the checked out list of events
 */
- (NSArray*) getEvents;

/**
 * Once a list of events have been successfully sent to the server invoke this method with the
 * list that was sent to flag the entries as sent.
 *
 * @param events the list of sent events
 */
- (void) notifyEventsSent:(NSArray*)events;

/**
 * Notify that the provided event has been successfully sent to the server. This should be
 * invoked after a single events has been tracked and added while a chat is active and it was
 * immediately sent to the server.
 *
 * @param event the event that was sent.
 */
- (void) notifyEventSent:(ZDCEventEntry*)event;

/**
 * Notify that a new chat session has been started, this resets all events as unsent.
 */
- (void) notifyNewChatSession;



@end

