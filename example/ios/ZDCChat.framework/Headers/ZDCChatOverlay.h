/*
 *
 *  ZDCChatOverlay.h
 *  ZDCChat
 *
 *  Created by Zendesk on 23/10/2014.
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
 * Enum defining initial overlay placement.
 */
typedef NS_ENUM(NSUInteger, ZDCOverlayAlignment) {

    /// Overlay initial placed as the bottom left of the screen within the insets.
    ZDCOverlayAlignmentBottomLeft       = 0,

    /// Overlay initial placed as the top left of the screen within the insets.
    ZDCOverlayAlignmentTopLeft          = 1,

    /// Overlay initial placed as the top right of the screen within the insets.
    ZDCOverlayAlignmentTopRight         = 2,

    /// Overlay initial placed as the bottom right of the screen within the insets.
    ZDCOverlayAlignmentBottomRight      = 3
};


/**
 * Protocol defining SDK interaction with the overlay.
 */
@protocol ZDCChatOverlayDelegate <NSObject>


/**
 * Show the overlay if it is not already active.
 */
- (void) show;

/**
 * Remove the overlay at the end of a chat.
 */
- (void) hide;

/**
 * Remove the overlay at the end of a chat.
 */
- (void) remove;

/**
 * Check if the overlay is currently active/visible.
 * @return YES if the overlay is active
 */
- (BOOL) active;

/**
 * Activate a chat with transition from the chat overlay.
 */
- (void) activate;

/**
 * Defines whether the widget will be shown, set to NO if you do not want the chat overlay/widget to be presented.
 */
- (void) setEnabled:(BOOL)enabled;


@end


#pragma mark -


/**
 * The chat overlay/button displayed when a chat is minimised.
 */
@interface ZDCChatOverlay : UIView <UIGestureRecognizerDelegate, ZDCChatOverlayDelegate>


/**
 * Defines whether the widget will be shown, set to NO if you do not want the chat overlay/widget to be presented.
 */
@property (nonatomic, assign) BOOL enabled;

#pragma mark appearance

/**
 * Margins applied to the chat overlay icon; the overlay will not move outside of these insets.
 * UIEdgeInsets as an NSValue ([NSValue valueWithUIEdgeInsets:edgeInsets]).
 */
@property (nonatomic, strong) NSValue *insets UI_APPEARANCE_SELECTOR;

/**
 * Default starting position for the overlay will be at the edge of the insets aligned in the corner 
 * specified here as @(ZDCOverlayAlignment...).
 */
@property (nonatomic, strong) NSNumber *alignment UI_APPEARANCE_SELECTOR;

/**
 * Font the the unread message count in the overlay.
 */
@property (nonatomic, strong) UIFont *messageCountFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the text of the unread message count in the overlay.
 */
@property (nonatomic, strong) UIColor *messageCountColor UI_APPEARANCE_SELECTOR;

/**
 * The typing indicator is 3 animated 'dots', this is the diameter for the dots.
 */
@property (nonatomic, strong) NSNumber *typingIndicatorDiameter UI_APPEARANCE_SELECTOR;

/**
 * The typing indicator is 3 animated 'dots', this is the standard color for the dots.
 */
@property (nonatomic, strong) UIColor *typingIndicatorColor UI_APPEARANCE_SELECTOR;

/**
 * The typing indicator is 3 animated 'dots', this is the highlighted color for the dots.
 */
@property (nonatomic, strong) UIColor *typingIndicatorHighlightColor UI_APPEARANCE_SELECTOR;

/**
 *  The image for the chat overlay icon.
 */
@property (nonatomic, strong) UIImage *overlayBackgroundImage UI_APPEARANCE_SELECTOR;

/**
 *  The tint of the image for the chat overlay icon
 */
@property (nonatomic, strong) UIColor *overlayTintColor UI_APPEARANCE_SELECTOR;

@end

