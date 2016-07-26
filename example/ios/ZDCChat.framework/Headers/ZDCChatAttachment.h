/*
 *
 *  ZDCChatAttachment.h
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
#import "ZDCChatFile.h"


/**
 * Chat event attachment details.
 */
@interface ZDCChatAttachment : ZDCChatFile

/**
 * The file URL.
 */
@property (nonatomic, strong) NSString *url;

/**
 * The thumbnail URL.
 */
@property (nonatomic, strong) NSString *thumbnailURL;

/**
 * Size of this attachment.
 */
@property (nonatomic, strong) NSNumber *fileSize;


/**
 * Request download of this image, ignoreed if download is already in progress.
 */
- (void) download;


@end

