/*
 *
 *  ZDCFormCellMessage.h
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
 * Cell for presenting the pre-chat form message editor.
 */
@interface ZDCFormCellMessage : ZDCFormCell <UITextViewDelegate>


/**
 * The text field providing text entry.
 */
@property (nonatomic, strong) ZDUTextView *textView;


@end

