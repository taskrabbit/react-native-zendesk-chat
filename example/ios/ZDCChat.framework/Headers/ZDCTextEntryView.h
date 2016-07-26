/*
 *
 *  ZDCTextEntryView.h
 *  ZDCChat
 *
 *  Created by Zendesk on 19/06/2014.
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
#import "ZDUTextView.h"


extern CGFloat const ZDC_TEXTENTRY_MINIMUM_HEIGHT;


@protocol ZDCTextEntryViewDelegate <NSObject>


/**
 * Text entry button pressed.
 */
- (void) sendButtonPressed;


/**
 * Attachment button pressed.
 */
- (void) attachButtonPressed;


@end


#pragma mark -


/**
 * Text entry text view and send button.
 */
@interface ZDCTextEntryView : UIView


/**
 * Text entry delegate
 */
@property (nonatomic, weak) id<ZDCTextEntryViewDelegate> delegate;


/**
 * The top border line of the component.
 */
@property (nonatomic, strong) UIView *topBorder;

/**
 * The rounded corner background to the text input field.
 */
@property (nonatomic, strong) UIView *textViewBackground;

/**
 * The text entry field.
 */
@property (nonatomic, strong) ZDUTextView *textView;

/**
 * Button for adding attachments.
 */
@property (nonatomic, strong) UIButton *attachButton;

/**
 * The send button.
 */
@property (nonatomic, strong) UIButton *sendButton;

/**
 * The send button image.
 */
@property (nonatomic, strong) NSString *sendButtonImage UI_APPEARANCE_SELECTOR;

/**
 * The attachments button image.
 */
@property (nonatomic, strong) NSString *attachButtonImage UI_APPEARANCE_SELECTOR;

/**
 * Color of border line at top of text entry area.
 */
@property (nonatomic, strong) UIColor *topBorderColor UI_APPEARANCE_SELECTOR;

/**
 * Font for the text entry view and it's placeholder.
 */
@property (nonatomic, strong) UIFont *textEntryFont UI_APPEARANCE_SELECTOR;

/**
 * Color of the text entry text.
 */
@property (nonatomic, strong) UIColor *textEntryColor UI_APPEARANCE_SELECTOR;

/**
 * Text entry box background color.
 */
@property (nonatomic, strong) UIColor *textEntryBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * Text entry box border color.
 */
@property (nonatomic, strong) UIColor *textEntryBorderColor UI_APPEARANCE_SELECTOR;

/**
 * Text entry area background color.
 */
@property (nonatomic, strong) UIColor *areaBackgroundColor UI_APPEARANCE_SELECTOR;


/**
 * Init with provided frame and request.
 *
 * @param frame the frame in which to render the UI
 * @param request the request object this comment is for
 * @return the instance
 */
- (instancetype) initWithFrame:(CGRect)frame;

/**
 * Returns the height that would be necessary to render the complete text of 
 * the text entry view given the current width of the component.
 *
 * @return the preferred height of the component
 */
- (CGFloat) preferredHeight;


@end

