/*
 *
 *  ZDChatAgentChatCell.h
 *  ZDCChat
 *
 *  Created by Zendesk on 24/09/2014.
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
#import "ZDCVisitorChatCell.h"
#import "ZDCChatAvatar.h"


/**
 * Cell for presenting an agent chat message.
 */
@interface ZDCAgentChatCell : ZDCVisitorChatCell

/**
 * The author label, only shown if this is the first message by that author.
 */
@property (nonatomic, strong) UILabel *author;

/**
 * The avatar image. Use the ZDCChatAvatar.defaultAvatar appearance attribute to set a default.
 */
@property (nonatomic, strong) ZDCChatAvatar *avatar;


#pragma mark appearance


/**
 * Height (and width) of the avatar image.
 */
@property (nonatomic, strong) NSNumber *avatarHeight UI_APPEARANCE_SELECTOR;

/**
 * Avatar inset from left of cell.
 */
@property (nonatomic, strong) NSNumber *avatarLeftInset UI_APPEARANCE_SELECTOR;

/**
 * Font of the author label.
 */
@property (nonatomic, strong) UIFont *authorFont UI_APPEARANCE_SELECTOR;

/**
 * Text color of the author label.
 */
@property (nonatomic, strong) UIColor *authorColor UI_APPEARANCE_SELECTOR;

/**
 * Total height provided for the author label, the label will sit at the bottom of this space
 * with the top starting from the bottom edge of the chat bubble and is followed by the 
 * configued bottom inset of the bubble.
 */
@property (nonatomic, strong) NSNumber *authorHeight UI_APPEARANCE_SELECTOR;


@end

