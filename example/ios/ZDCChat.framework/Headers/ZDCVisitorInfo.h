/*
 *
 *  ZDCVisitorInfo.h
 *  ZDCChat
 *
 *  Created by Zendesk on 27/11/2014.
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
#import "ZDCChatIO.h"


/**
 * The visitor details currently known by the Chat SDK.
 */
@interface ZDCVisitorInfo : NSObject


/**
 * The visitors name to be submitted prior to the chat starting.
 */
@property (nonatomic, strong) NSString *name;

/**
 * The visitors email to be submitted prior to the chat starting.
 */
@property (nonatomic, strong) NSString *email;

/**
 * The visitors phone to be submitted prior to the chat starting.
 */
@property (nonatomic, strong) NSString *phone;

/**
 * Specifies whether visitor data should be persisted for use when starting 
 * future chat sessions. If switched off then persisted data will immediately be wiped.
 */
@property (nonatomic, assign) BOOL shouldPersist;


/**
 * New instance initialised with the provided chat IO.
 * @param chatIO the chat IO for sending updates
 */
- (instancetype) initWithIO:(id<ZDCChatIO>)chatIO;


@end

