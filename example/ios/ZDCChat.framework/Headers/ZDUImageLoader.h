/*
 *
 *  ZDUImageLoader.h
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


/**
 * Protocol defining the callback used when an image is ready.
 */
@protocol ZDUImageRequestDelegate <NSObject>

/**
 * Notify that an image has been retrieved, either from the cache or by download.
 */
- (void) imageDownloaded:(UIImage*)img;

@end


#pragma mark -


/**
 * Defines an image request.
 */
@interface ZDUImageRequest : NSObject

/**
 * Ref to the requester of the image
 */
@property (nonatomic, weak) id<ZDUImageRequestDelegate> requester;

/**
 * Image URL.
 */
@property (nonatomic, strong) NSString *url;

@end


#pragma mark -


/**
 * Downloads and caches images in memory.
 */
@interface ZDUImageLoader : NSObject

/**
 * The image cache.
 */
@property (nonatomic, strong) NSMutableDictionary *cache;

/**
 * Cache list for controlling FIFO.
 */
@property (nonatomic, strong) NSMutableArray *list;

/**
 * List of images currently being downloaded.
 */
@property (nonatomic, strong) NSMutableDictionary *downloading;

/**
 * Active download operations.
 */
@property (nonatomic, strong) NSOperationQueue *queue;


/**
 * Request the image for the provided URL. The delegates imageDownloaded: method will be invoked
 * as soon as the image is available (potentially during the invocation of this method).
 * @param url the image URL
 * @param requester the class requesting the image
 */
- (void) getImageAtURL:(NSString*)url forRequester:(id<ZDUImageRequestDelegate>)requester;

/**
 * Invoke if an image download is no longer required by a requester.
 * @param url the image URL for which to cancel the request
 * @param requester the requester for which to cancel the request
 */
- (void) cancelImageRequest:(NSString*)url from:(id)requester;

/**
 * Cancel all downloads and empty the cache.
 */
- (void) empty;


@end

