/*
 *
 *  ZDCChatDataNode.h
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
#import "ZDCChatDataSource.h"


/**
 * DataNode representation of the chat data.
 */
@interface ZDCChatDataNode : NSObject <ZDCChatDataSource>


+ (BOOL) isNonEmptyString:(id)object;


@end

