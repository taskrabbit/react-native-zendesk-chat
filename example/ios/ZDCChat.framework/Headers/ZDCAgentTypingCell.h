/*
 *
 *  ZDCAgentTypingCell.h
 *  ZDCChat
 *
 *  Created by Zendesk on 01/12/2014.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import "ZDCChatCell.h"
#import "ZDCChatAvatar.h"


/**
 * Animated typing indicator dots.
 */
@interface ZDCTypingDots : UIView


/**
 * Standard dot color.
 */
@property (nonatomic, strong) UIColor *dotColor;

/**
 * Highlighted dot color.
 */
@property (nonatomic, strong) UIColor *dotHighlightColor;

/**
 * YES if currently animating.
 */
@property (nonatomic, assign, readonly) BOOL animating;


/**
 * New instance with specified height.
 * @param height the dot height.
 */
- (instancetype) initWithHeight:(float)height;

/**
 * Start dot animation;
 */
- (void) startAnimating;

/**
 * Stop dot animation
 */
- (void) stopAnimating;


@end


#pragma mark -


/**
 * Cell for notifying that an agent is typing.
 */
@interface ZDCAgentTypingCell : ZDCChatCell


/**
 * Agent(s) typing label.
 */
@property (nonatomic, strong) ZDCTypingDots *dots;

/**
 * The avatar image. Use the ZDCChatAvatar.defaultAvatar appearance attribute to set a default.
 */
@property (nonatomic, strong) ZDCChatAvatar *avatar;


@end

