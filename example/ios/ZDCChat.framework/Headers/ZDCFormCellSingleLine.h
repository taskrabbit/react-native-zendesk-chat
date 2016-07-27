/*
 *
 *  ZDCFormCellSingleLine.h
 *  ZDCChat
 *
 *  Created by Zendesk on 29/01/2015.
 *
 *  Copyright (c) 2015 Zendesk. All rights reserved.
 *
 *  By downloading or using the Zopim Chat SDK, You agree to the Zendesk Terms
 *  of Service https://www.zendesk.com/company/terms and Application Developer and API License
 *  Agreement https://www.zendesk.com/company/application-developer-and-api-license-agreement and
 *  acknowledge that such terms govern Your use of and access to the Chat SDK.
 *
 */


#import "ZDCFormCell.h"


/**
 * Single line text entry cell for pre chat form fields which presents rows for name,
 * email and phone.
 */
@interface ZDCFormCellSingleLine : ZDCFormCell <UITextFieldDelegate>


/**
 * The text field providing text entry.
 */
@property (nonatomic, strong) UITextField *textField;


@end

