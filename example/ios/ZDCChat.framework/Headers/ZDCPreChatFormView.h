/*
 *
 *  ZDCChatFormView.h
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
#import "ZDCVisitorActionDelegate.h"
#import "ZDUUtil.h"
#import "ZDCFormCell.h"
#import "ZDCPreChatData.h"


extern NSString * const ZDC_FORMCELL_SINGLELINE;
extern NSString * const ZDC_FORMCELL_DEPARTMENT;
extern NSString * const ZDC_FORMCELL_MESSAGE;


/**
 * Pre chat form view.
 */
@interface ZDCPreChatFormView : UIView <UITextViewDelegate, UITableViewDataSource, UITableViewDelegate, ZDCFormCellDelegate>

/**
 * Chat action delegate.
 */
@property (nonatomic, weak, readonly) id<ZDCVisitorActionDelegate> chatController;


/**
 * The UITableView presenting the form fields.
 */
@property (nonatomic, strong) UITableView *formTable;

/**
 * The current value of the name field.
 */
@property (nonatomic, strong) NSString *nameText;

/**
 * The current value of the email field.
 */
@property (nonatomic, strong) NSString *emailText;

/**
 * The current value of the phone field.
 */
@property (nonatomic, strong) NSString *phoneText;

/**
 * The current value of the message field.
 */
@property (nonatomic, strong) NSString *messageText;

/**
 * The current value of the department field.
 */
@property (nonatomic, strong) NSString *selectedDepartment;

/**
 * Background color for this view.
 */
@property (nonatomic, strong) UIColor *formBackgroundColor UI_APPEARANCE_SELECTOR;


/**
 * Create a new instance.
 * @param frame the frame of the view
 * @param controller the delegate which handles visitor actions within the chat view
 * @return the new instance
 */
- (instancetype) initWithFrame:(CGRect)frame withController:(id<ZDCVisitorActionDelegate>)controller;

/**
 * Sets up the pre-chat form with the required fields and department data, should be invoked just 
 * before presenting the form to ensure everything is up to date.
 */
- (void) prepareForm;

/**
 * Check if the form has had all required fields completed.
 * @return YES if all fields have been completed as per the active form configuration
 */
- (BOOL) formComplete;

/**
 * Check the completion and validity of the specified data. Verifies whether the type is required, complete and valid.
 * @param the data type to be checked
 * @param currentValue the value to be checked
 * @param rows the rows being presented for entry
 * @param requirement the requirement for the data
 * @return the status of that type
 */
+ (ZDCFormDataStatus) fieldValid:(ZDCFormCellType)type
                           value:(NSString*)currentValue
                        formRows:(NSArray*)rows
                     requirement:(ZDCPreChatDataRequirement)requirement;

/**
 * Register a class (instance of ZDCFormCell) for use in creating and sizing chat cells.
 * Reuse Ids are defined at the top of this header and have the prefix 'ZDC_FORMCELL_'.
 * @param class the class to be registered
 * @param identifier the reuse identifier for which to register the class
 */
- (void)registerClass:(Class)cellClass forCellReuseIdentifier:(NSString *)identifier;


@end

