/*
 *
 *  ZDCHttpUploadRequest.h
 *  ZDCChat
 *
 *  Created by Zendesk on 21/10/2014.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import "ZDCHttpRequest.h"


/**
 Simple request wrapper to upload a single file.
 */
@interface ZDCHttpUploadRequest : ZDCHttpRequest {
    
    NSString *fileURL;
    NSData *fileData;
    NSString *filename;
    NSString *fileContentType;
    BOOL fileWritten;
}

/**
 * Initialize the request.
 * @param url the url for the upload
 * @param filename the file to be uploaded
 * @param contentType the content type
 */
- (id) initWithFileURL:(NSString*)url filename:(NSString*)filename contentType:(NSString*)contentType;

/**
 * Initialize the request.
 * @param data the url for the upload
 * @param filename the file to be uploaded
 * @param contentType the content type
 */
- (id) initWithFileData:(NSData*)data
               filename:(NSString*)theFilename
            contentType:(NSString*)contentType;


@end
