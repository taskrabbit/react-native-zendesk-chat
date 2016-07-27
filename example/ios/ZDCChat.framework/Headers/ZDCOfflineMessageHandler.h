/*
 *
 *  ZDCOfflineMessageHandler.h
 *  ZDCChat
 *
 *  Created by Zendesk on 06/03/2015.
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
 * Offline message handler block.
 * @param chatViewController reference to the chat view controller
 */
typedef void (^ZDCOfflineMessageAction) (UIViewController *chatViewController);


/**
 * Class defining an override of the default offline message handling.
 */
@interface ZDCOfflineMessageHandler : NSObject


/**
 * When there are no agents online the visitor is presented with an error/info screen with the default 
 * title 'No agents available' ("ios.ZDCChat.noAgentsTitle"). This string defines the message body 
 * which is presented below that title and above the message creation button. If this is left nil 
 * then the default string ("ios.ZDCChat.noAgentsMessage") will be used.
 */
@property (nonatomic, strong) NSString *noAgentsMessage;

/**
 * When there are no agents online the visitor is presented with an error/info screen with the default
 * title 'No agents available' ("ios.ZDCChat.noAgentsTitle"). This string button text for the message 
 * creation button. If this is left nil then the default string ("ios.ZDCChat.noAgentsButton") will be used.
 */
@property (nonatomic, strong) NSString *noAgentsButtonText;

/**
 * This block should contain the action to be taken (UI to be presented) for handling the offline 
 * message process.
 */
@property (nonatomic, copy) ZDCOfflineMessageAction action;


/**
 * Create a new offline message override with the defined parameters.
 * @param noAgentsMessage the message body on the 'No agents available' screen
 * @param noAgentsButtonText button text on the 'No agents available' screen
 * @param action block executed when the user taps the button on the 'No agents available' screen
 */
+ (instancetype) offlineHandlerWithMessage:(NSString*)noAgentsMessage
                                buttonText:(NSString*)noAgentsButtonText
                                 andAction:(ZDCOfflineMessageAction)action;


@end
