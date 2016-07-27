/*
 *
 *  ZDCFormCellDepartment.h
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
 * Utility for drawing a simple arrow on screen.
 */
@interface ZDCTriangleView : UIView


/**
 * Color for interior of the arrow.
 */
@property (nonatomic, strong) UIColor *color;


@end


#pragma mark -


/**
 * Cell for presenting/interacting with the pre-chat form department field.
 */
@interface ZDCFormCellDepartment : ZDCFormCell <UIActionSheetDelegate>


/**
 * The button for responding to user taps and providing the control background.
 */
@property (nonatomic, strong) UIButton *departmentButton;

/**
 * The department label and placeholder.
 */
@property (nonatomic, strong) UILabel *departmentLabel;

/**
 * The combo-box down arrow.
 */
@property (nonatomic, strong) ZDCTriangleView *icon;

/**
 * The action sheet diaplaying the department list.
 */
@property (nonatomic, strong) UIActionSheet *actionSheet;


@end

