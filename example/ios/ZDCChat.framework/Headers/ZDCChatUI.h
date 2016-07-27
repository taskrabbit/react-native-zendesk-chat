/*
 *
 *  ZDCChatController.h
 *  ZDCChat
 *
 *  Created by Zendesk on 05/11/2014.
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
#import "ZDCLoadingView.h"
#import "ZDCPreChatFormView.h"
#import "ZDCChatView.h"
#import "ZDCVisitorActionDelegate.h"
#import "ZDCReachability.h"
#import "ZDCLoadingErrorView.h"
#import "ZDCChatUIController.h"
#import "ZDCOfflineMessageView.h"

typedef NS_ENUM(NSUInteger, ZDCChatBackgroundAnchor) {

    /// Anchor the chat background to to top of the visible area
    ZDCChatBackgroundAnchorCenter           = 0,

    /// Anchor the chat background to the center of the visible area
    ZDCChatBackgroundAnchorTop              = 1,
};


@protocol ZDCInsetProvider <NSObject>

- (id<UILayoutSupport>) topLayoutGuide;

- (id<UILayoutSupport>) bottomLayoutGuide;

@end


/**
 * The principle chat UI component that contains all functional aspects of the chat UI.
 */
@interface ZDCChatUI : UIView <ZDCVisitorActionDelegate>

/**
 * Background image view.
 */
@property (nonatomic, strong) UIImageView *backgroundImageView;

/**
 * The full screen loading view using during initial connection.
 */
@property (nonatomic, strong) ZDCLoadingView *loadingView;

/**
 * The full screen loading error view used if a connection cannot be established or there are no agents available.
 */
@property (nonatomic, strong) ZDCLoadingErrorView *loadingErrorView;

/**
 * The pre-chat form UI, only presented if the pre-chat form has been set and there are uncompleted fields.
 */
@property (nonatomic, strong) ZDCPreChatFormView *formView;

/**
 * The chat UI, contains the chat table and text entry area.
 */
@property (nonatomic, strong) ZDCChatView *chatView;

/**
 * The built in offline message form.
 */
@property (nonatomic, strong) ZDCOfflineMessageView *offlineForm;

/**
 * Delegate for actions to be taken by the container/controller.
 */
@property (nonatomic, weak) id<ZDCChatUIController> delegate;

/**
 * The current UI state.
 */
@property (nonatomic, assign) ZDCChatUIState state;

/**
 * The inset provider for layout out the chat UI (probably the parent view controller).
 */
@property (nonatomic, weak) id<ZDCInsetProvider> insetProvider;

/**
 * Image for the button shown in the navigation bar for ending a chat.
 */
@property (nonatomic, strong) NSString *endChatButtonImage UI_APPEARANCE_SELECTOR;

/**
 * Image for the button shown in the navigation bar for cancelling a chat connection attempt.
 */
@property (nonatomic, strong) NSString *cancelChatButtonImage UI_APPEARANCE_SELECTOR;

/**
 * Image for the button shown in the navigation bar for minimizing a chat.
 */
@property (nonatomic, strong) NSString *backChatButtonImage UI_APPEARANCE_SELECTOR;

/**
 * The name of the image to be used in the background of the chat views.
 */
@property (nonatomic, strong) UIColor *chatBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * The name of the image to be used in the background of the chat views.
 */
@property (nonatomic, strong) NSString *chatBackgroundImage UI_APPEARANCE_SELECTOR;

/**
 * Number representation of ZDCChatBackgroundAnchor, defines the anchor point for the background image.
 */
@property (nonatomic, strong) NSNumber *chatBackgroundAnchor UI_APPEARANCE_SELECTOR;


/**
 * Initialise with the provided delegate.
 * @param frame the initial view frame
 * @param the delegate
 * @return instance
 */
- (instancetype) initWithFrame:(CGRect)frame andDelegate:(id<ZDCChatUIController>)delegate;


/**
 * Populate data and start the chat UI listening for events.
 */
- (void) activate;

/**
 * Minimise the chat UI, dismiss the keyboard and present the chat overlay.
 */
- (void) minimise;

/**
 * Remove all event observers and dismiss the keyboard.
 */
- (void) end;

/**
 * Show the built in offline form.
 */
- (void) showOfflineForm;

/**
 * Submit the offline message form.
 */
- (void) sendOfflineMessage;


@end

