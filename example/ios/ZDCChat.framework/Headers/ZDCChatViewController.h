/*
 *
 *  ZDChatViewController.h
 *  ZDCChat
 *
 *  Created by Zendesk on 24/09/2014.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import "ZDUViewController.h"
#import "ZDCLoadingView.h"
#import "ZDCPreChatFormView.h"
#import "ZDCChatView.h"
#import "ZDCChatUI.h"


/**
 * View controller containing the complete chat UI.
 */
@interface ZDCChatViewController : ZDUViewController <ZDCChatUIController, ZDCInsetProvider>


/**
 * The chat UI including loading screen and pre-chat form.
 */
@property (nonatomic, strong) ZDCChatUI *chatUI;


@end

