/*
 *
 *  ZDCChatProfile.h
 *  ZDCChat
 *
 *  Created by Zendesk on 29/10/2014.
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
 * Profile record for a visitor in a chat.
 */
@interface ZDCChatProfile : NSObject

/**
 * The session id for the current chat.
 */
@property (nonatomic, strong) NSString *sessionId;

/**
 * The machine Id for the current session.
 */
@property (nonatomic, strong) NSString *machineId;

/**
 * The visitor nickname.
 */
@property (nonatomic, strong) NSString *nickname;

/**
 * The visitor email.
 */
@property (nonatomic, strong) NSString *email;

/**
 * The visitor display name.
 */
@property (nonatomic, strong) NSString *displayName;


@end

