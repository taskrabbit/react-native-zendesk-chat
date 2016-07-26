/*
 *
 *  ZDCAgentOptionsCell.m
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

#import "ZDCAgentChatCell.h"

/**
 * View foer presenting a shortcut option.
 */
@interface ZDCOptionView : UIView

/**
 * The index of this option.
 */
@property (nonatomic, assign) NSInteger optionIndex;

/**
 * If this option is presented as selected.
 */
@property (nonatomic, assign) BOOL selected;

/**
 * The radio button view.
 */
@property (nonatomic, strong) UIView *radio;

/**
 * The option text view.
 */
@property (nonatomic, strong) UILabel *optionText;

/**
 * Bubble insets.
 */
@property (nonatomic, assign) UIEdgeInsets optionBubbleInsets;

/*
 * Text insets.
 */
@property (nonatomic, assign) UIEdgeInsets optionTextInsets;


/**
 * Create a new option view with the option text provided.
 * @param frame the initial frame for the view
 * @param option the option text
 * @return the new instance
 */
- (instancetype) initWithFrame:(CGRect)frame andOption:(NSString*)option;


@end


#pragma mark -


@interface ZDCAgentOptionsCell : ZDCAgentChatCell


/**
 * Array of views which present an option list.
 */
@property (nonatomic, strong) NSMutableArray *options;


@end

