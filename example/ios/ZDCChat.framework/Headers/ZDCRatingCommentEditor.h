/*
 *
 *  ZDCRatingCommentEditor.h
 *  ZDCChat
 *
 *  Created by Zendesk on 05/11/2014.
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
#import "ZDCVisitorActionDelegate.h"
#import "ZDUTextView.h"


/**
 * Full pane chat rating comment editor.
 */
@interface ZDCRatingCommentEditor : ZDUViewController <UITextViewDelegate>


/**
 * Action delegate.
 */
@property (nonatomic, weak) id<ZDCVisitorActionDelegate>delegate;

/**
 * Text entry view.
 */
@property (nonatomic, strong) ZDUTextView *textView;


/**
 * New instance.
 * @param initialText the text to pre-populate in the text view
 * @param delegate action delegate
 * @return the instance
 */
- (instancetype) initWithText:(NSString*)initialText andDelegate:(id<ZDCVisitorActionDelegate>)delegate;


@end

