/*
 *
 *  ZDCJSWidgetIO.h
 *  ZDCChat
 *
 *  Created by Zendesk on 21/10/2014.
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
#import "ZDCReachability.h"


@interface ZDCJSWidgetIO : NSObject <ZDCChatIO>


extern NSString * const ZDC_API_ERROR_DOMAIN;


/**
 * Reachbility instance used by chat.
 */
@property (nonatomic, strong) ZDCReachability *reachability;


/**
 * New instance.
 * @param delegate the io delegate to which messages are passed
 * @param reachability reachability instance
 */
- (instancetype) initWithDelegate:(id<ZDCWebIODelegate>)delegate andReachability:(ZDCReachability*)reachability;


@end

