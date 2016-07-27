/*
 *
 *  ZDCHttpRequest.h
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


@class ZDCHttpRequest;


extern NSString *const ZDC_HTTP_METHOD_GET;
extern NSString *const ZDC_HTTP_METHOD_DELETE;
extern NSString *const ZDC_HTTP_METHOD_POST;
extern NSString *const ZDC_HTTP_METHOD_PUT;

extern NSString *const ZDC_HTTP_HEADER_CONTENT_TYPE;
extern NSString *const ZDC_HTTP_HEADER_ACCEPT_TYPE;
extern NSString *const ZDC_HTTP_HEADER_USER_AGENT;

extern NSString *const ZDC_HTTP_ERROR_DOMAIN;
extern NSString *const ZDC_HTTP_ERROR_KEY;


typedef enum _ZDCHTTPMethodEnum {
    ZDCHTTPMethodGET          = 0,
    ZDCHTTPMethodPUT          = 1,
    ZDCHTTPMethodPOST         = 2,
    ZDCHTTPMethodDELETE       = 3
} ZDCHTTPMethod;

/**
 *  Error codes.
 */
typedef NS_ENUM(NSInteger, ZDCHTTPError) {

    /**
     *  The file upload requests exceed the server limits.
     */
    ZDCHTTPErrorNoConnection,

    /**
     * The request was challenged for auth that it doesn't have.
     */
    ZDCHTTPErrorUserAuthenticationRequired = NSURLErrorUserAuthenticationRequired
};


/**
 * Block for invocation on completion of a request, either successfully or with error(s).
 * @param request the request that was completed.
 */
typedef void (^ZDCHTTPCompleted) (ZDCHttpRequest *request);


#pragma mark -


/**
 * Progress monitoring protocol for downloda/uploads.
 */
@protocol ZDCProgressMonitor <NSObject>


@optional
/**
 * Sets the current progress of a download/upload.
 * @param progress the current progress
 */
- (void) setProgress:(float)progress;


@end


#pragma mark -


/**
 * This class stores relevant information on the response to an HTTP request.
 */
@interface ZDCHTTPResponse : NSObject


/// Weak reference to the request; handling of the response is performed within the context
/// of the request so this should always be a vaild pointer for the duration of such handling
@property(nonatomic, unsafe_unretained) ZDCHttpRequest *request;

/// The response bytes
@property(nonatomic, strong) NSMutableData *bodyData;

/// The response as a string
@property(nonatomic, strong) NSString *bodyString;

/// The HTTP response headers
@property(nonatomic, strong) NSDictionary *headers;

/// The HTTP response code
@property(nonatomic, assign) NSInteger statusCode;

/// The error if the request was not successful
@property(nonatomic, strong) NSError *error;

/// The content length reported in the HTTP headers
@property(nonatomic, assign) NSInteger contentLength;

/// The content type of the response
@property(nonatomic, strong) NSString *contentType;


/**
 * Convert the body data to a string.
 * @return the response data formated as a string
 */
- (NSString*) getResponseAsString;

/**
 * Reset the response to initial state.
 */
- (void) reset;


@end


#pragma mark -


/**
 * Wrapper around NSUrlConnection providing simple convenience mechanisms.
 */
@interface ZDCHttpRequest : NSObject <NSURLConnectionDataDelegate> {

    @protected
    NSURLConnection *con;
    ZDCHTTPCompleted success;
    ZDCHTTPCompleted error;
    NSTimer *progressTimer;
    long bytesReceived;
    long totalBytesToWrite;
    long bytesWritten;
}


/// Url of the request.
@property(nonatomic, strong) NSString *urlString;

/// HTTP method
@property(nonatomic, assign) ZDCHTTPMethod method;

/// The request body, e.g. if making a JSON POST request
@property(nonatomic, strong) NSString *body;

/// The request body data, e.g. if sending binary data
@property(nonatomic, strong) NSData *bodyData;

/// HTTP request content type - setting this adds the header to the additionalHeaders dictionary
@property(nonatomic, strong) NSString *reqContentType;

/// HTTP request accept type - setting this adds the header to the additionalHeaders dictionary
@property(nonatomic, strong) NSString *reqAcceptType;

/// All headers to add to the request
@property(nonatomic, strong) NSMutableDictionary *additionalHeaders;

/// The response object containing relevant details of the final state of the request
@property(nonatomic, strong) ZDCHTTPResponse *response;

/// Cancelled status
@property(nonatomic, readonly) BOOL cancelled;

/// Download progress monitor, set this to be notified of download progress
@property(nonatomic, weak) id<ZDCProgressMonitor>downloadProgressMonitor;

/// Upload progress monitor, set this to be notified of upload progress
@property(nonatomic, weak) id<ZDCProgressMonitor>uploadProgressMonitor;


/**
 * Execute this request.
 *
 * @param success the block to be executed on success
 * @param error the block to be executed on error
 */
- (void) execute:(ZDCHTTPCompleted)success error:(ZDCHTTPCompleted)error;

/**
 * Set the user agent to be used when making requests, the same user agent is used for all requests.
 * @param userAgent the user agent
 */
+ (void) setUserAgent:(NSString*)userAgent;

/**
 * Cancel the NSUrlConnection and mark the request as cancelled, none of the completion blocks will be invoked.
 */
- (void) cancel;


@end

