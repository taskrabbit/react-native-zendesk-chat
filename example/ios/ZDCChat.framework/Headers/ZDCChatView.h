/*
 *
 *  ZDCChatView.h
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


#import <UIKit/UIKit.h>
#import "ZDCTextEntryView.h"
#import "ZDCVisitorActionDelegate.h"
#import "ZDUImageLoader.h"
#import "ZDCMessageMonitor.h"


// reuse strings for chat cells
extern NSString * const ZDC_CHATCELL_AGENT;
extern NSString * const ZDC_CHATCELL_AGENT_ATTACH;
extern NSString * const ZDC_CHATCELL_VISITOR;
extern NSString * const ZDC_CHATCELL_VISITOR_ATTACH;
extern NSString * const ZDC_CHATCELL_JOINLEAVE;
extern NSString * const ZDC_CHATCELL_TIMEOUT;
extern NSString * const ZDC_CHATCELL_TYPING;
extern NSString * const ZDC_CHATCELL_SYSTEM_TRIGGER;
extern NSString * const ZDC_CHATCELL_RATING;
extern NSString * const ZDC_CHATCELL_OPTIONS;
extern NSString * const ZDC_CHATCELL_OFFLINE;


/**
 * Chat view containing the chat table view and the test entry area.
 */
@interface ZDCChatView : UIView <UITableViewDataSource, UITableViewDelegate, UITextViewDelegate, ZDCTextEntryViewDelegate, UIActionSheetDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIPopoverControllerDelegate>

/**
 * The visitor action delegate.
 */
@property (nonatomic, weak, readonly) id<ZDCVisitorActionDelegate> chatController;

/**
 * The table presenting the chat entries.
 */
@property (nonatomic, strong, readonly) UITableView *table;

/**
 * The text entry area.
 */
@property (nonatomic, strong, readonly) ZDCTextEntryView *textEntryView;

/**
 * Set the timeout out status.
 */
@property (nonatomic, assign) BOOL timedOut;

/**
 * Monitors the messages and moves them to unsent state if they remain unverified for more than 5 seconds.
 */
@property (nonatomic, strong) ZDCMessageMonitor *messageMonitor;

/**
 * Background color for this view.
 */
@property (nonatomic, strong) UIColor *chatBackgroundColor UI_APPEARANCE_SELECTOR;


/**
 * Create a new chat view.
 * @param frame the frame of the view
 * @param controller the delegate which handles visitor actions within the chat view
 * @return the new instance
 */
- (instancetype) initWithFrame:(CGRect)frame withController:(id<ZDCVisitorActionDelegate>)controller;

/**
 * Populate data and start the chat view listening for events.
 */
- (void) activate;

/**
 * Register a class (instance of ZDCChatCell) for use in creating and sizing chat cells.
 * Reuse Ids are defined at the top of this header and have the prefix 'ZDC_CHATCELL_'.
 * @param class the class to be registered
 * @param identifier the reuse identifier for which to register the class
 */
- (void)registerClass:(Class)cellClass forCellReuseIdentifier:(NSString *)identifier;

/**
 * Scroll the last cell in the table to be visible.
 * @param animated YES to animate
 */
- (void) scrollToLast:(BOOL)animated;

/**
 * Clear the text entry area.
 */
- (void) clearTextEntry;

/**
 * Reload the table with the latest chat events.
 */
- (void) reload;


@end

