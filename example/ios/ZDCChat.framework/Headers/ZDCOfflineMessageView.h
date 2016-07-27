/*
 *
 *  ZDCOfflineMessageView.h
 *  ZDCChat
 *
 *  Created by Zendesk on 13/03/2015.
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
#import "ZDCFormCell.h"
#import "ZDCVisitorActionDelegate.h"


@interface ZDCOfflineMessageView : UIView <UITableViewDelegate, UITableViewDataSource, ZDCFormCellDelegate, UITextViewDelegate>


/**
 * The UITableView presenting the form fields.
 */
@property (nonatomic, strong) UITableView *formTable;

/**
 * Semi-transparent overlay applied while the offline message is being sent.
 */
@property (nonatomic, strong) UIView *submittingOverlay;

/**
 * Submitting spinner.
 */
@property (nonatomic, strong) UIActivityIndicatorView *submittingSpinner;

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
 * @param message any message that the user had already entered into the pre-chat form
 * @return the new instance
 */
- (instancetype) initWithFrame:(CGRect)frame
                withController:(id<ZDCVisitorActionDelegate>)controller
                    andMessage:(NSString*)message;

/**
 * Check if the form fields have been completed.
 * @return YES if all fields have been completed
 */
- (BOOL) formComplete;

/**
 * Animate to the 'submitting' state.
 */
- (void) animateToSubmitting;

/**
 * Animate back from the submitting state.
 */
- (void) animateFromSubmitting;


@end

