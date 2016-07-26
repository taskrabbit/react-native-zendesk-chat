/*
 *
 *  ZDCConfig.h
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
#import "ZDCPreChatData.h"
#import "ZDCSessionConfig.h"


/**
 * The default/global settings for chats started by the SDK.
 */
@interface ZDCConfig : ZDCSessionConfig


/**
 * The Zopim account key (must be set before a chat can be started).
 */
@property (nonatomic, strong) NSString *accountKey;


#pragma mark visitor metadata

/**
 * This string will be placed in the first line of the visitor path and is equivalent to the 'referrer'.
 * Defaults to the form: "{app_name}, v{app_version}({build_number})"
 * Must be set before a connection is created if a custom string is required.
 */
@property (nonatomic, strong) NSString *visitorPathOne;

/**
 * This string will be placed in the second line of the visitor path and is equivalent to the 'title'.
 * Defaults to the form: "{app_name}"
 * Must be set before a connection is created if a custom string is required.
 */
@property (nonatomic, strong) NSString *visitorPathTwo;


@end

