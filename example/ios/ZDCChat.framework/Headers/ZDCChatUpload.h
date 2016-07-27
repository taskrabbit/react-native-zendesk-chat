/*
 *
 *  ZDCFileUpload.h
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
#import "ZDCChatIO.h"
#import "ZDCHttpUploadRequest.h"
#import "ZDCChatFile.h"


/**
 * Upload delegate for listening to upload updates.
 */
@protocol ZDCUploadDelegate <NSObject>


/**
 * Notify of a new progress update.
 * @param progress the new progress value
 */
- (void) progressUpdate:(float)progress;


@end


#pragma mark -


/**
 * A file uploaded in the active session.
 */
@interface ZDCChatUpload : ZDCChatFile <ZDCProgressMonitor>


/**
 * File extension, e.g. '.png'.
 */
@property (nonatomic, strong) NSString *fileExtension;

/**
 * File size in bytes.
 */
@property (nonatomic, strong) NSNumber *fileSize;

/**
 * Upload URL, setting this to a valid URL from empty will begin the upload.
 */
@property (nonatomic, strong) NSString *uploadURL;

/**
 * Current progress (0 - 1 proportion).
 */
@property (nonatomic, assign) float progress;

/**
 * Chat IO for sending the requests.
 */
@property (nonatomic, weak) id<ZDCChatIO> chatIO;

/**
 * Progress listener for upload progress
 */
@property (nonatomic, weak) id<ZDCUploadDelegate> progressListener;


/**
 * New file upload instance. The filename may be updated to ensure it is unique for this session.
 * @param chatIO chat IO class for requesting the upload URL
 * @param data the file data, either this or the path are required
 * @param path the file path, either this or the data are required
 * @param fileName the file name sent to the server, must include an extention matching the file type
 * @param fileSize the size of the file in bytes
 */
- (instancetype) initWithIO:(id<ZDCChatIO>)chatIO
                   fileData:(NSData*)data
                   filePath:(NSString*)path
                      image:(UIImage*)image
                   fileName:(NSString*)filename
                andFileSize:(long long)fileSize;

/**
 * Resend the file to the server.
 */
- (void) resend;

/**
 * Check if the supplied details are sufficient and correctly fortmatted for sending an upload.
 * @param data the file data, either this or the path are required
 * @param path the file path, either this or the data are required
 * @param fileName the file name sent to the server, must include an extention matching the file type
 * @param fileSize the size of the file in bytes
 * @return YES if valid
 */
+ (BOOL) validUpload:(NSData*)data
            filePath:(NSString*)path
               image:(UIImage*)image
            fileName:(NSString*)filename
         andFileSize:(long long)fileSize;




@end

