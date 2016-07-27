/*
 *
 *  ZDCLoadingErrorView.h
 *  ZDCChat
 *
 *  Created by Zendesk on 26/01/2015.
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
#import "ZDCChatUIController.h"


@interface ZDCLoadingErrorView : UIView


/**
 * Error icon.
 */
@property (nonatomic, strong) UIImageView *icon;

/**
 * Error title.
 */
@property (nonatomic, strong) UILabel *title;

/**
 * Error message.
 */
@property (nonatomic, strong) UILabel *message;

/**
 * Button that will take the user to the offline message form.
 */
@property (nonatomic, strong) UIButton *offlineMessageButton;

/**
 * Delegate for opening the offline message form.
 */
@property (nonatomic, assign) id<ZDCChatUIController> delegate;

/**
 * Error icon image name.
 */
@property (nonatomic, strong) NSString *iconImage UI_APPEARANCE_SELECTOR;

/**
 * Font for the title label.
 */
@property (nonatomic, strong) UIFont *titleFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the title label text.
 */
@property (nonatomic, strong) UIColor *titleColor UI_APPEARANCE_SELECTOR;

/**
 * Font for the message label.
 */
@property (nonatomic, strong) UIFont *messageFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the message label text.
 */
@property (nonatomic, strong) UIColor *messageColor UI_APPEARANCE_SELECTOR;

/**
 * Font for the offline message button.
 */
@property (nonatomic, strong) UIFont *buttonFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the text for the offline message button.
 */
@property (nonatomic, strong) UIColor *buttonTitleColor UI_APPEARANCE_SELECTOR;

/**
 * Background color for the offline message button.
 */
@property (nonatomic, strong) UIColor *buttonBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * Button image for the offline message button.
 */
@property (nonatomic, strong) NSString *buttonImage UI_APPEARANCE_SELECTOR;

/**
 * Background color for this view.
 */
@property (nonatomic, strong) UIColor *errorBackgroundColor UI_APPEARANCE_SELECTOR;


/**
 * New instance for notifying the user that there is no internet connection.
 * @param frame the frame for the view
 */
- (instancetype) initNoConnectionWithFrame:(CGRect)frame;

/**
 * New instance for notifying the user there are no agents available for chat.
 * @param frame the frame for the view
 * @param delegate for opening the offline message form
 */
- (instancetype) initNoAgentsWithFrame:(CGRect)frame andDelegate:(id<ZDCChatUIController>)delegate;

/**
 * New instance for notifying the user a chat could not be established.
 * @param frame the frame for the view
 * @param delegate for opening the offline message form
 */
- (instancetype) initCantConnectWithFrame:(CGRect)frame andDelegate:(id<ZDCChatUIController>)delegate;


@end

