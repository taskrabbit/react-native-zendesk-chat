/*
 *
 *  ZDCChatAlertHelper.h
 *  ZDCChat
 *
 *  Created by Zendesk on 08/12/2015.
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
@class ZDCChatUI;


@protocol ZDCChatAlertHelperDelegate <NSObject>

- (BOOL)isValidChatSessionWithoutErrors;
- (BOOL)isSendingChatTranscriptEnabled;
- (BOOL)isChatLogEmpty;

- (void)disableChatEntryTextView;

- (NSString*)storedEmailTranscriptDestination;
- (void)sendTranscriptToEmail:(NSString*)email;

- (void)endChat;

@end

@interface ZDCChatAlertHelper : NSObject

- (instancetype)initWithDelegate:(id<ZDCChatAlertHelperDelegate>)delegate;
- (BOOL)shouldShowEndChatEmail;
- (void)showEndChatAlert;

@end
