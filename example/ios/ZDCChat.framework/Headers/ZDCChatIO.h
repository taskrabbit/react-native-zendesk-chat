/*
 *
 *  ZDChatIO.h
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


#import <Foundation/Foundation.h>
#import "ZDCChatProfile.h"
#import "ZDCReachability.h"
#import "ZDCEvents.h"


@class ZDCVisitorInfo;


/**
 * Chat connection status.
 */
typedef NS_ENUM(NSUInteger, ZDCConnectionStatus) {
    
    /// Chat connection has not been started.
    ZDCConnectionStatusUninitialized     = 0,
    
    /// Chat is currently establishing a connection.
    ZDCConnectionStatusConnecting        = 1,
    
    /// Chat is connected.
    ZDCConnectionStatusConnected         = 2,
    
    /// Chat connection has been closed.
    ZDCConnectionStatusClosed            = 3,
    
    /// Chat connection lost.
    ZDCConnectionStatusDisconnected      = 4,
    
    /// Device has no internet connection.
    ZDCConnectionStatusNoConnection      = 5
};

/**
 * Chat ratings.
 */
typedef NS_ENUM(NSUInteger, ZDCChatRating) {

    /// Not yet rated.
    ZDCChatRatingUnrated    = 0,

    /// No rating.
    ZDCChatRatingNone       = 1,

    /// Good chat rating.
    ZDCChatRatingGood       = 2,

    /// Bad chat rating.
    ZDCChatRatingBad        = 3
};


/**
 * Protocol for receiving Zopim WebIO messages.
 */
@protocol ZDCWebIODelegate


/**
 * Invoked on WebIO message receipt.
 * @param msg the WebIO message to be processed
 */
- (void) webIOMessageReceived:(NSString*)msg;


@end


#pragma mark -


/**
 * Base communications protocol for Zopim chat.
 */
@protocol ZDCChatIO <NSObject>


/**
 * Initialise with delegate for receiving WebIO messages.
 * @param delegate the WebIO delegate
 * @param reachability reachability instance to be used
 */
- (instancetype) initWithDelegate:(id<ZDCWebIODelegate>)delegate andReachability:(ZDCReachability*)reachability;

/**
 * Initiate a connection to the server.
 * @param accountKey account to connect to
 * @param machineId used when reconnecting to a session
 * @param visitorPathOne this string will be placed in the first line of the visitor path
 * @param visitorPathTwo this string will be placed in the second line of the visitor path
 * @param timoutInterval this timout interval used in the chat session
 */
- (void) connectToAccount:(NSString*)accountKey
                machineId:(NSString*)machineId
           visitorPathOne:(NSString*)visitorPathOne
           visitorPathTwo:(NSString*)visitorPathTwo
           timoutInterval:(NSTimeInterval)timoutInterval;

/**
 * Disconnect from the server.
 */
- (void) disconnect;

/**
 * Get the current connection status.
 * @return current connection status
 */
- (ZDCConnectionStatus) connectionStatus;

/**
 * Set the session language.
 * @param identifier 2 letter language code (+ zh_CN, zh_TW and pt_BR)
 * @see https://zopim.zendesk.com/entries/23042000-Supported-Languages-on-the-Chat-Widget
 */
- (void) setLanguage:(NSString*)identifier;

/**
 * Request an email of the transcript.
 * @param email the visitors email address
 */
- (void) emailTranscript:(NSString*)email;

/**
 * Notify the server that the visitor is typing (or not).
 * @param typing YES if the visitor is typing
 */
- (void) notifyTyping:(BOOL)typing;

/**
 * Send a chat message to the server.
 * @param msg the chat message
 * @param profile the visitors profile
 */
- (void) sendChatMessage:(NSString*)msg profile:(ZDCChatProfile*)profile;

/**
 * Resend a chat message that previously failed to send.
 * @param msg the message to be resent
 * @param eventId the original event id
 */
- (void) resendChatMessage:(NSString*)msg eventId:(NSString*)eventId;

/**
 * Submit the visitor name to the server.
 * @param name the visitor name
 */
- (void) sendVisitorName:(NSString*)name;

/**
 * Submit the visitor email to the server.
 * @param name the visitor email
 */
- (void) sendVisitorEmail:(NSString*)email;

/**
 * Submit the visitor phone to the server.
 * @param name the visitor phone
 */
- (void) sendVisitorPhone:(NSString*)phone;

/**
 * Submit the department to the server.
 * @param department the selected/set department
 */
- (void) sendDepartment:(NSString*)department;

/**
 * Submit the tags to the server.
 * @param tags tags to be set on this session
 */
- (void) sendTags:(NSArray*)tags;

/**
 * Send a chat rating.
 * @param rating the selected rating
 */
- (void) sendChatRating:(ZDCChatRating)rating;

/**
 * Send a chat rating comment.
 * @param comment the rating comment
 */
- (void) sendChatRatingComment:(NSString*)comment;

/**
 * Request the upload URL for a file upload.
 * @param fileName the name of the file to be uploaded
 * @param fileExtension the file extension e.g. ".jpg"
 * @param fileSize the size of the file
 */
- (void) uploadURL:(NSString*)fileName extension:(NSString*)fileExtension size:(NSNumber*)fileSize;

/**
 * End the current chat.
 */
- (void) endChat;

/**
 * Send an offline message.
 * @param message the message to send
 * @param name the visitors name
 * @Param email the visitors email address
 */
- (void) sendOfflineMessage:(NSString*)message withName:(NSString*)name andEmail:(NSString*)email;

/**
 * Sends the array of events/breadcrumbs.
 * @param events an array of ZDCEventEntry objects
 */
- (void) sendEvents:(NSArray*)events;


#pragma mark event observers


/**
 * Listen for connection events.
 * @param target the listener to add
 * @param selector the selector to be invoked on the target
 */
- (void) addObserver:(id)target forConnectionEvents:(SEL)selector;

/**
 * Remove connection observers for the target.
 * @param target the listener to remove
 */
- (void) removeObserverForConnectionEvents:(id)target;


@end

