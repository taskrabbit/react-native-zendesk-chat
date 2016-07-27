/*
 *
 *  ZDCChatUIController.h
 *  ZDCChat
 *
 *  Created by Zendesk on 29/10/2014.
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
#import "ZDCChatEvent.h"


/**
 * Protocol for handling visitor actions on the individual chat UI sections.
 */
@protocol ZDCVisitorActionDelegate <NSObject>


/**
 * Visitor has triggered submission of the pre-chat form.
 */
- (void) submitForm;

/**
 * Visitor has triggered sending of the current typed message.
 */
- (void) sendMessage;

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

/**
 * Edit the chat rating comment.
 * @param ratingEvent the chat log event for the rating
 */
- (void) editRatingComment:(ZDCChatEvent*)ratingEvent;

/**
 * Update the chat rating comment.
 */
- (void) updateChatRatingComment:(NSString*)newComment;


@end

