/*
 *
 *  ZDCAgentAttachmentCell.h
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


@interface ZDCAgentAttachmentCell : ZDCAgentChatCell


/**
 * The image view for the attachment.
 */
@property (nonatomic, strong) UIImageView *attachmentImage;

/**
 * Progress indicator for downloads.
 */
@property (nonatomic, strong) UIActivityIndicatorView *spinner;

/**
 * Label that displays the file name on non-image attachments.
 */
@property (nonatomic, strong) UILabel *filenameLabel;

/**
 * The style for the activity indicator (UIActivityIndicatorViewStyle).
 */
@property (nonatomic, strong) NSNumber *activityIndicatorViewStyle UI_APPEARANCE_SELECTOR;


@end

