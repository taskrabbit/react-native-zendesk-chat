/*
 *
 *  ZDCSystemTriggerCell.h
 *  ZDCChat
 *
 *  Created by Zendesk on 05/02/2015.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import <UIKit/UIKit.h>
#import "ZDCChatCell.h"


@interface ZDCSystemTriggerCell : ZDCChatCell


/**
 * Label displaying the chat message.
 */
@property (nonatomic, strong) UILabel *chatMessage;

/**
 * Insets of the text within the chat bubble.
 */
@property (nonatomic, strong) NSValue *textInsets UI_APPEARANCE_SELECTOR;

/**
 * Label text colour.
 */
@property (nonatomic, strong) UIColor *textColor UI_APPEARANCE_SELECTOR;

/**
 * Label font.
 */
@property (nonatomic, strong) UIFont *textFont UI_APPEARANCE_SELECTOR;


@end

