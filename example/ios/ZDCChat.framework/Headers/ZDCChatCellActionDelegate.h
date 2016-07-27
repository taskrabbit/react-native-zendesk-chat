/*
 *
 *  ZDCChatCellActionDelegate.h
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

#import <Foundation/Foundation.h>


@class  ZDCOptionView;


/**
 * Delegate handling chat cell actions.
 */
@protocol ZDCChatCellActionDelegate <NSObject>


#pragma mark resends

/*
 * Check if the provided event has timed out and is not in the middle of a resend.
 * @param event the event to be evaluated
 * @return YES if the event should be presented as unsent
 */
- (BOOL) eventHasTimedOut:(ZDCChatEvent*)event;

/*
 * Request that a message is resent.
 * @param event the event for the message to resend
 */
- (void) resendMessage:(ZDCChatEvent*)event;


#pragma mark files


/**
 * Notify that a file has been updated.
 * @param event the event for updated file
 */
- (void) fileUpdated:(ZDCChatEvent*)event;

/**
 * View the image from an attachment.
 * @param the image to view
 * @param imageView the source UIImageView that contains the image
 */
- (void) viewAttachmentImage:(UIImage*)image fromView:(UIImageView*)imageView;

/**
 * View the non-image attachment document in a web view.
 */
- (void) viewDocumentForEvent:(ZDCChatEvent*)event;


#pragma mark options lists


/**
 * Notify that an option has been selected.
 * @param event the event for which an option was selected
 * @param index the index of the selected
 */
- (void) optionSelected:(ZDCChatEvent*)event;

/**
 * Get an option view from the queue, creating new object as necessary.
 * @param option the option string
 * @param index the option index
 * @param radioRadius the radius of the radio button
 * @param borderColor the border color for the option bubble and radio button
 * @param font the option text font
 * @param textColor the option text color
 * @param bubbleCornerRadius the option bubble corner radius
 * @param backgroundColor the bubble background color
 * @return the option view
 */
- (ZDCOptionView*) dequeueOptionView:(NSString*)option
                             atIndex:(NSInteger)index
                         radioRadius:(CGFloat)radioRadius
                         borderColor:(UIColor*)borderColor
                                font:(UIFont*)font
                           textColor:(UIColor*)textColor
                  bubbleCornerRadius:(CGFloat)bubbleCornerRadius
                     backgroundColor:(UIColor*)backgroundColor;

/**
 * Return an optin view to the queue;
 */
- (void) requeueOptionView:(ZDCOptionView*)optionView;


#pragma mark ratings


/**
 * Edit the chat rating comment.
 * @param ratingEvent the chat log event for the rating
 */
- (void) editRatingComment:(ZDCChatEvent*)ratingEvent;

/**
 * Set a new chat rating.
 * @param ratingEvent the chat log event for the rating
 * @param rating the new rating
 */
- (void) setChatRating:(ZDCChatEvent*)ratingEvent to:(ZDCChatRating)newRating;


#pragma mark size caching

/**
 * String size cache.
 * @param string the string to be sized
 * @param font presentation font
 * @param width the available text width
 * @return the calculated size
 */
- (CGFloat) sizeOfString:(NSString*)string usingFont:(UIFont*)font forWidth:(CGFloat)width;


@end

