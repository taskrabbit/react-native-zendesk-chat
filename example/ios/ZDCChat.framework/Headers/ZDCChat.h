/*
 *
 *  ZDCChat.h
 *  ZDCChat
 *
 *  Created by Zendesk on 22/04/2014.
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
#import "ZDCAgentChatCell.h"
#import "ZDCAgentTypingCell.h"
#import "ZDCChatAgent.h"
#import "ZDCChatAvatar.h"
#import "ZDCChatCell.h"
#import "ZDCChatIO.h"
#import "ZDCChatConstants.h"
#import "ZDCChatDataNode.h"
#import "ZDCChatDataSource.h"
#import "ZDCChatEvent.h"
#import "ZDCChatOverlay.h"
#import "ZDCChatProfile.h"
#import "ZDCChatSession.h"
#import "ZDCChatTimedOutCell.h"
#import "ZDCChatUI.h"
#import "ZDCChatView.h"
#import "ZDCChatViewController.h"
#import "ZDCConfig.h"
#import "ZDCDeviceInfo.h"
#import "ZDCVisitorChatCell.h"
#import "ZDCJSWidgetIO.h"
#import "ZDCJoinLeaveCell.h"
#import "ZDCKeychainWrapper.h"
#import "ZDCLoadingView.h"
#import "ZDCLog.h"
#import "ZDCPreChatData.h"
#import "ZDCPreChatFormView.h"
#import "ZDCReachability.h"
#import "ZDCSessionConfig.h"
#import "ZDCSessionStateManager.h"
#import "ZDCTextEntryView.h"
#import "ZDCVisitorInfo.h"
#import "ZDCVisitorActionDelegate.h"
#import "ZDUUtil.h"
#import "ZDCFormCell.h"
#import "ZDCFormCellDepartment.h"
#import "ZDCFormCellMessage.h"
#import "ZDCFormCellSingleLine.h"
#import "ZDCJSONEncoder.h"
#import "ZDCSystemTriggerCell.h"
#import "ZDCOfflineMessageHandler.h"
#import "ZDCBundleUtils.h"
#import "ZDCChatUpload.h"
#import "ZDCAgentAttachmentCell.h"
#import "ZDCImageViewer.h"
#import "ZDCVisitorAttachmentCell.h"
#import "ZDCWebViewer.h"
#import "ZDCRatingCell.h"
#import "ZDCRatingCommentEditor.h"
#import "ZDCAccountOfflineCell.h"
#import "ZDCMobileProvisionAnalyzer.h"


/**
 * Defaults config block.
 * @param defaults the chat defaults to field requirements, department and tags
 */
typedef void (^ZDCChatConfigBlock) (ZDCConfig *defaults);

/**
 * Visitor config block.
 * @param visitor the visitor info to be updated
 */
typedef void (^ZDCVisitorConfigBlock) (ZDCVisitorInfo *visitor);

/**
 * Session config block.
 * @param info the session info object which can be used to set pre-chat data requirements and session metadata
 */
typedef void (^ZDCSessionConfigBlock) (ZDCSessionConfig *config);


#pragma mark -


/**
 * The core of the Chat SDK, all objects related to chat can be accessed
 * from here either directly or indirectly.
 */
@interface ZDCChat : NSObject


/**
 * The chat session.
 */
@property (nonatomic, strong) id<ZDCChatSession> session;

/**
 * The chat overlay used when chat is minimised.
 */
@property (nonatomic, strong) id<ZDCChatOverlayDelegate> overlay;

/**
 * The view controller for the chat UI.
 */
@property (nonatomic, strong) ZDCChatViewController *chatViewController;

/**
 * Timeout applied on initial chat startup; if the session does not achieve a connection in this 
 * time then the connection attempt is considered to have failed (default 30 seconds).
 */
@property (nonatomic, assign) NSTimeInterval connectionTimeout;

/**
 * Timeout applied when reconnecting to an existing active chat, if the session does not achieve a 
 * connection in this time then the connection attempt is considered to have failed and the user is 
 * asked if they want to continue or not (default 120 seconds).
 */
@property (nonatomic, assign) NSTimeInterval reconnectionTimeout;

/**
 * This property allows interception of the offline message handling process. If set then the action 
 * block will be invoked when there are no agents online, the user is offered the option of sending 
 * an offline message, and taps the button to send a message.
 */
@property (nonatomic, strong) ZDCOfflineMessageHandler *offlineMessageHandler;

/*
 * Defines whether an available chat session should be resumed on launch.
 */
@property (nonatomic, assign) BOOL shouldResumeOnLaunch;

/**
 * Sets the parameter by the same name on the chat view controller when it is pushed onto an existing view controller.
 */
@property (nonatomic, assign) BOOL hidesBottomBarWhenPushed;


/**
 * Singleton instance of the ZDCChat component.
 */
+ (instancetype) instance;

/**
 * Configure the Chat SDK.
 * @param config block in which the global settings and pre-chat data requirements are configured
 */
+ (void) configure:(ZDCChatConfigBlock)config;

/**
 * Update the visitor data.
 * @param visitorConfig visitor config block
 */
+ (void) updateVisitor:(ZDCVisitorConfigBlock)visitorConfig;

/**
 * Show the chat UI and begin connecting to the chat server.
 * This method will present the chat UI in a new modal.
 * @param sessionConfig block in which the session config may be used to override the 
 *        defaults for this session only, leave nil to use the default config
 */
+ (void) startChat:(ZDCSessionConfigBlock)sessionConfig;

/**
 * Push the chat UI on to the supplied nav controller and begin connecting to the chat server.
 * @param navController the navigation controller in which to push the chat UI
 * @param configOverride block in which the session config is updated as desired for this session, leave nil to use the default config
 */
+ (void) startChatIn:(UINavigationController*)navController withConfig:(ZDCSessionConfigBlock)configOverride;

/**
 * End the chat session and dismiss the UI.
 */
+ (void) endChat;

/**
 * Minise the chat window.
 */
+ (void) minimiseChat;


@end

