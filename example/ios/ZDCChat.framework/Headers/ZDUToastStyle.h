/*
 *
 *  ZDUToastStyle.h
 *  ZDCChat
 *
 *  Created by Zendesk on 13/05/2014.
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


/**
 * Toast types providing specific styling as defined in ZDCToastStyle.
 * @since 0.1
 */
typedef NS_ENUM(NSUInteger, ZDUToastUIType) {
    ZDUToastUITypeInfo,
    ZDUToastUITypeOK,
    ZDUToastUITypeWarning,
    ZDUToastUITypeError,
    ZDUToastUIType_count
};


#pragma mark -


/**
 * Toast styling options.
 * @since 0.1
 */
typedef NS_ENUM(NSUInteger, ZDUToastUIStyle) {
    ZDUToastUIStyleBackgroundColor,
    ZDUToastUIStyleBorderColor,
    ZDUToastUIStyleFontColor,
    ZDUToastUIStyleButtonBorderColor,
    ZDUToastUIStyleButtonBackgroundColor,
    ZDUToastUIStyleButtonFontColor,
    ZDUToastUIStyleButtonFontName,
    ZDUToastUIStyleButtonFontSize,
    ZDUToastUIStyleFontName,
    ZDUToastUIStyleFontSize,
    ZDUToastUIStyleIconName, // v0.2
    ZDUToastUIStyle_count
};


#pragma mark -


/**
 * Singleton class holding the styling details for toast messages.
 * @since 0.1
 */
@interface ZDUToastStyle : NSObject


/**
 * Set the style value for the specified type.
 * @param value this should be: UIColor for 'Color' styles, NSString for 'Name' styles and NSNumber for 'Size' styles
 * @param type ZDCToastUIType defining the type to be styled
 * @param style ZDCToastUIStyle defining the style to be set
 * @since 0.1
 */
+ (void) setValue:(id)value forType:(ZDUToastUIType)type andStyle:(ZDUToastUIStyle)style;

/**
 * Get the requested style value for the type.
 * @param type ZDCToastUIType defining the style to be retrieved
 * @param style ZDCToastUIStyle the style to be retrieved
 * @since 0.1
 */
+ (id) getValueForType:(ZDUToastUIType)type andStyle:(ZDUToastUIStyle)style;


@end

