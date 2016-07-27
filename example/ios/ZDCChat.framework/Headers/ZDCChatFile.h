/*
 *
 *  ZDCChatFile.h
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


/**
 * File transfer status.
 */
typedef NS_ENUM(NSUInteger, ZDCFileTransferStatus) {

    /// File transfer has not yet started.
    ZDCFileTransferStatusPending          = 0,

    /// File is currently transfering.
    ZDCFileTransferStatusTransfering        = 1,

    /// File transfer has completed.
    ZDCFileTransferStatusComplete         = 2,

    /// An error has occured transfering the file.
    ZDCFileTransferStatusError            = 3
};


/**
 * File upload error types.
 */
typedef NS_ENUM(NSUInteger, ZDCTransferError) {

    /// No error.
    ZDCTransferErrorNone                = 0,

    /// The file type is not accepted.
    ZDCTransferErrorType                = 1,

    /// The file is too large.
    ZDCTransferErrorSize                = 2,

    /// The SDK could not access the file on the path provided.
    ZDCTransferErrorAccess              = 3,

    /// The upload request was invalid.
    ZDCTransferErrorInvalid             = 4,

    /// The communication failed.
    ZDCTransferErrorFailed              = 5,
    
    /// File sending is disabled
    ZDCTransferFileSendingDisabled      = 6,

    /// Unknown error.
    ZDCTransferErrorUnknown             = 1000
};


@interface ZDCChatFile : NSObject


/**
 * Filename.
 */
@property (nonatomic, strong) NSString *fileName;

/**
 * Mime type of this attachment.
 */
@property (nonatomic, strong) NSString *mimeType;

/**
 * File data.
 */
@property (nonatomic, strong) NSData *data;

/**
 * Local file system path if referencing a file.
 */
@property (nonatomic, strong) NSString *path;

/**
 * The image representing this file.
 */
@property (nonatomic, strong) UIImage *image;

/**
 * Status of the transfer pending/uploading/complete/error.
 */
@property (nonatomic, assign) ZDCFileTransferStatus status;

/**
 * Error type, setting the error type will send a notification (ZDC_CHAT_INVALID_UPLOAD) of the error.
 */
@property (nonatomic, assign) ZDCTransferError errorType;


/**
 * Get the extension from the file name.
 * @param the file name
 * @return the file extension or nil if one cannot be extracted
 */
+ (NSString*) derivefileExtension:(NSString*)fileName;

/**
 * Get the mime type for the supplied details. The file signature will be used if possible, otherwise
 * simply the extension is used. Only currently recognises PNG, JPG, PDF and TXT.
 * @param data the file data if available
 * @param the file extentsion if available
 * @return the mime type, or nil if nothing is recognised
 */
+ (NSString *) mimeTypeForData:(NSData*)data andFileExtension:(NSString*)fileExtension;

/**
 * Check if this attachment is an image that can be displayed directly.
 * @return YES if the attachment is an image
 */
- (BOOL) isPresentableImage;


@end

