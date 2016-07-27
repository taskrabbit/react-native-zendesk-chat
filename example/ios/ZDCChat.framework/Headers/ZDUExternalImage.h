/*
 *
 *  ZDUExternalImage.h
 *  ZDCChat
 *
 *  Created by Zendesk on 01/12/2014.
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
#import "ZDUImageLoader.h"


/**
 * Present an image with a remote source.
 */
@interface ZDUExternalImage : UIImageView <ZDUImageRequestDelegate>

/**
 * Shared image loader.
 */
@property (nonatomic, strong) ZDUImageLoader *loader;

/**
 * Image URL.
 */
@property (nonatomic, strong) NSString *url;


/**
 * Create a new instance.
 * @param loader the shared image loader
 * @return instance
 */
- (instancetype) initWithLoader:(ZDUImageLoader*)loader;

/**
 * Present the image clipped to a circle. this method actually sets the corner radius 
 * as this produces a better result the drawing a mask by hand.
 */
- (void) maskWithCircle;


@end

