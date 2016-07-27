/*
 *
 *  ZDCChatLoadingView.h
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


/**
 * Chat loading view.
 */
@interface ZDCLoadingView : UIView


/**
 * The loading spinner.
 */
@property (nonatomic, strong) UIActivityIndicatorView *spinner;

/**
 * Label shown below the loading spinner.
 */
@property (nonatomic, strong) UILabel *loadingLabel;

/**
 * Font to be used by the loading label.
 */
@property (nonatomic, strong) UIFont *loadingLabelFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the text for the loading label.
 */
@property (nonatomic, strong) UIColor *loadingLabelTextColor UI_APPEARANCE_SELECTOR;

/**
 * Background color for this view.
 */
@property (nonatomic, strong) UIColor *loadingBackgroundColor UI_APPEARANCE_SELECTOR;


/**
 * Show the loading view and start the spinner.
 */
- (void) show;

/**
 * Hide the loading view and stop the spinner.
 */
- (void) hide;


@end

