/*
 *
 *  ZDCFormCell.h
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


#import <UIKit/UIKit.h>
#import "ZDUUtil.h"


extern const float ZDC_DEFAULT_FORM_CELL_HEIGHT;


typedef NS_ENUM(NSUInteger, ZDCFormCellType) {
    
    /// Form cell for name
    ZDCFormCellTypeName         = 0,
    
    /// Form cell for email
    ZDCFormCellTypeEmail        = 1,
    
    /// Form cell for phone
    ZDCFormCellTypePhone        = 2,
    
    /// Form cell for department
    ZDCFormCellTypeDepartment   = 3,
    
    /// Form cell for message
    ZDCFormCellTypeMessage      = 4
};


typedef NS_ENUM(NSUInteger, ZDCFormDataStatus) {

    /// The data has been completed
    ZDCFormDataOk               = 0,

    /// The data has not been entered
    ZDCFormDataIncomplete       = 1,

    /// The data is invalid
    ZDCFormDataInvalid          = 2
};


#pragma mark -


/**
 * Pre chat form cell delegate notifying receiver of user events.
 */
@protocol ZDCFormCellDelegate <NSObject>


/**
 * Notify of a change in the value/text for the form field.
 * @param value the new value for the form field
 * @param type identifies which for field the new value applies to
 */
- (void) updatedValue:(NSString*)value forType:(ZDCFormCellType)type;

/**
 * The user has just activated ths control in this cell, request focus for this cell.
 * @param type identifies the field to scroll to
 */
- (void) scrollToType:(ZDCFormCellType)type;

/**
 * The user has hit the 'next' key, request that focus is trensfered to the next field.
 * @param currentType the field type from which focus is being transfered
 */
- (void) goToNextType:(ZDCFormCellType)currentType;


@end


#pragma mark -


/**
 * Super class for pre-chat form field cells, if you would like to register your own cells for 
 * displaying form fields then the cells should extend this class.
 */
@interface ZDCFormCell : UITableViewCell


/**
 * Defines which form field is being displayed by this cell.
 */
@property (nonatomic, assign) ZDCFormCellType type;

/**
 * Reference to the form cell delegate.
 */
@property (nonatomic, weak) id<ZDCFormCellDelegate> delegate;

/**
 * The background for the text field; rounded corners and 1px border.
 */
@property (nonatomic, strong) UIView *textFrame;

/**
 * Insets for the text view background/frame.
 */
@property (nonatomic, strong) NSValue *textFrameInsets UI_APPEARANCE_SELECTOR;

/**
 * Insets for the text view within the background.
 */
@property (nonatomic, strong) NSValue *textInsets UI_APPEARANCE_SELECTOR;

/**
 * Border color for the text view frame.
 */
@property (nonatomic, strong) UIColor *textFrameBorderColor UI_APPEARANCE_SELECTOR;

/**
 * Border color for the text view frame when highlighted as invalid/imcomplete.
 */
@property (nonatomic, strong) UIColor *textFrameErrorBorderColor UI_APPEARANCE_SELECTOR;

/**
 * Background color for the text view frame.
 */
@property (nonatomic, strong) UIColor *textFrameBackgroundColor UI_APPEARANCE_SELECTOR;

/**
 * Corner radius for text view frame.
 */
@property (nonatomic, strong) NSNumber *textFrameCornerRadius UI_APPEARANCE_SELECTOR;

/**
 * Font for the text entry field.
 */
@property (nonatomic, strong) UIFont *textFont UI_APPEARANCE_SELECTOR;

/**
 * Text color.
 */
@property (nonatomic, strong) UIColor *textColor UI_APPEARANCE_SELECTOR;


/**
 * Prepare for use with the current text for the cell.
 * @param text the form cell text
 * @param type the ZDCFormCellType type
 * @param delegate the form cell delegate
 * @param highlight if YES then border is changed to error highlight color
 */
- (void) prepareWithText:(NSString*)text
                 forType:(ZDCFormCellType)type
            withDelegate:(id<ZDCFormCellDelegate>)delegate
          highlightError:(BOOL)highlight;

/**
 * Get the cell height.
 * @param text the text being displayed by this cell
 * @param width the table/cell width
 * @return the calculated height, if not overridden this method defaults to 44.0
 */
- (CGFloat) heightForText:(NSString*)text givenWidth:(CGFloat)width;

/**
 * Get the appearance value for a given selector, returning the default if not set.
 * @param sel the appearance selector to be used
 * @param defaultVal the default value returned if the appearance has not been set
 * @return the apperance value if set, else the default value
 */
- (id) appearance:(SEL)sel def:(id)defaultVal;

/**
 * Set the appearance properties with either specified values or defaults.
 */
- (void) setupAppearance;

- (void) setupTextFrame;


@end

