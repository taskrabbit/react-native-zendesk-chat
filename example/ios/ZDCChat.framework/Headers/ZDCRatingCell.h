/*
 *
 *  ZDCRatingCell.h
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


#import "ZDCVisitorChatCell.h"

/**
 * Chat rating cell.
 */
@interface ZDCRatingCell : ZDCVisitorChatCell


/**
 * Title label for the cell.
 */
@property (nonatomic, strong) UILabel *titleLabel;

/**
 * Button for sendiung a bad chat rating.
 */
@property (nonatomic, strong) UIButton *badRatingButton;

/**
 * Button for sendiung a good chat rating.
 */
@property (nonatomic, strong) UIButton *goodRatingButton;

/**
 * Button for leaving/editing a rating comment.
 */
@property (nonatomic, strong) UIButton *commentButton;

/**
 * Title text colour.
 */
@property (nonatomic, strong) UIColor *titleColor UI_APPEARANCE_SELECTOR;

/**
 * Title font.
 */
@property (nonatomic, strong) UIFont *titleFont UI_APPEARANCE_SELECTOR;

/**
 * Vertical space from the top of the cell to the rating title.
 */
@property (nonatomic, strong) NSNumber *cellToTitleMargin UI_APPEARANCE_SELECTOR;

/**
 * Vertical space between the rating title and the rating buttons.
 */
@property (nonatomic, strong) NSNumber *titleToButtonsMargin UI_APPEARANCE_SELECTOR;

/**
 * Vertical space between the rating buttons and the rating comment. Also used as the lower cell
 * margin if there is no comment or comment button yet.
 */
@property (nonatomic, strong) NSNumber *ratingButtonToCommentMargin UI_APPEARANCE_SELECTOR;

/**
 * Height of the leave/edit comment button.
 */
@property (nonatomic, strong) NSNumber *editCommentButtonHeight UI_APPEARANCE_SELECTOR;

/**
 * Height and width of the rating buttons.
 */
@property (nonatomic, strong) NSNumber *ratingButtonSize UI_APPEARANCE_SELECTOR;


@end

