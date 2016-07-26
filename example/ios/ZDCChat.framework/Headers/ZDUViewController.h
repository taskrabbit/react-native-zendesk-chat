/*
 *
 *  ZDUViewController.h
 *  ZDCChat
 *
 *  Created by Zendesk on 29/04/2014.
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
#import "ZDUToastView.h"


/**
 * Base view controller class used by ZD components containing frequently used methods.
 */
@interface ZDUViewController : UIViewController

/**
 * Current keyboard height.
 */
@property (nonatomic, assign) CGFloat keyboardHeight;

/** 
 * Requires existence of navigation controller in parent view controller.
 */
@property (nonatomic, assign) BOOL requiresNavBar;

/**
 * The content view for this view controller. Any subviews should be added this.
 *
 * All subclasses should use this view as a base for their view hierarchy.
 */
@property (nonatomic, strong) UIView *contentView;

/**
 * A toast for notifying visitors of events/statuses.
 */
@property (nonatomic, strong) ZDUToastView *toastView;

/**
 * The height of the currently displayed toast.
 */
@property (nonatomic, assign) CGFloat toastHeight;


#pragma mark keyboard event handling


/**
 * Register the view controler to be notified of keyboard show/hide events.
 * Override keyboardWillBeShown: and keyboardWillBeHidden: to handle the events
 */
- (void) registerForKeyboardNotifications;

/**
 * Called when the keyboard was shown, invoke [super keyboardDidShow:] to
 * update the size of the contentView.
 * @param aNotification the notification
 */
- (void) keyboardDidShow:(NSNotification*)aNotification;

/**
 * Called when the keyboard is about to be hidden, invoke [super keyboardWillHide:] to
 * update the size of the contentView.
 * @param aNotification the notification
 */
- (void) keyboardWillHide:(NSNotification*)aNotification;


#pragma mark toasts


/**
 * Present a new toast message if it is not already being show (equality depends on Id, type and message).
 * @param the message to show
 * @param animate if YES animate the toast in
 */
- (void) presentPersistentToast:(NSString*)message
                           type:(ZDUToastUIType)type
                        animate:(BOOL)animate;

/**
 * Dismiss the active toast.
 */
- (void) dismissActiveToast:(BOOL)animated;


#pragma mark offsets


/**
 * Top offset for IOS7+ transparent status and nav bars
 */
- (CGFloat) topViewOffset;

/**
 * Bottom offset for IOS7+ transparent toolbars
 */
- (CGFloat) bottomViewOffset;


#pragma mark - view controller utils


/**
 * Invoked if the view is about to be removed.
 */
- (void) viewWillBeDismissed;

/**
 * Get the top view controller from thw app window.
 *
 * @return the top view controller for the app.
 */
+ (UIViewController*) topViewController;

/**
 * Get the top view controller from root controller provided.
 *
 * @param the root view controller from which to start looking
 * @return the top view controller
 */
+ (UIViewController*) topViewControllerWithRootViewController:(UIViewController*)rootViewController;

/**
 * Present the view controller. If the current top view controller 
 * is or has a navigation controller then the view will be pushed on 
 * to that controller, otherwise a new navigation controller will be
 * pushed (vertical transition).
 */
+ (void) presentViewController:(UIViewController*)viewController requiresNavController:(BOOL)requiresNav;


@end

