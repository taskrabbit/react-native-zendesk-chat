/*
 *
 *  ZDUTextView.h
 *  ZDCChat
 *
 *  Created by Zendesk on 28/04/2014.
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
#import "ZDUActivityViewDelegate.h"


/**
 * A UITextView with a placeholder that is shown when there is no text in the text
 * view. Retains all the functionality of a normal UITextView. Setting the font
 * on the text view sets the font on the placeholder. The placeholder text color
 * is set with the placeholderTextColor property.
 */
@interface ZDUTextView : UIView <UITextViewDelegate>


/**
 * The textview being presented.
 */
@property (nonatomic, strong) UITextView *textview;

/**
 * The placeholder text that is shown when there is no text in the text view.
 */
@property (nonatomic, retain) NSString *placeholderText;

/**
 * The color of the placeholder that is shown when there is no text in the text view.
 */
@property (nonatomic, retain) UIColor *placeholderTextColor;

/**
 * Set the text view delegate.
 */
@property (nonatomic, weak) id<UITextViewDelegate> delegate;


/**
 * Init method for ZDRMATextView.
 *
 * @param frame The frame for the text view
 * @param placeholderText The text for the placeholder
 * @return An initialized ZDRMATextView object or nil if the object couldn't be created.
 *
 */
- (instancetype) initWithFrame:(CGRect)frame andPlaceholder:(NSString*)placeholderText;

/**
 * Set the font for both the text view and the placeholder.
 * @param font the font to set
 */
- (void) setFont:(UIFont*)font;

/**
 * Set the test of the text view.
 * @param the new text
 */
- (void) setText:(NSString *)text;

/**
 * Set the content insets to Zero alignment.
 * @param testView the text view to update
 */
+ (void) setZeroInsets:(UITextView*)textView;


@end

