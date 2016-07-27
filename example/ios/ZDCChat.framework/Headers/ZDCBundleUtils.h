/*
 *
 *  ZDKBundleUtils.m
 *  ZDCChat
 *
 *  Created by Zendesk on 06/03/2015.
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


@interface ZDCBundleUtils : NSObject


/**
 * Gets the framework resource bundle.
 * @return The frameworks resource NSBundle or nil if the SDK bundle was not found.
 */
+ (NSBundle *) frameworkResourceBundle;

/**
 * Gets the framework strings bundle.
 * @return The frameworks strings NSBundle or nil if the SDK bundle was not found.
 */
+ (NSBundle *) frameworkStringsBundle;

/**
 * Get the path for a resource in the SDK bundle.
 * @param name The resource name.
 * @param extension The file extension.
 * @return The path for the css file, or nil if file was not found.
 */
+ (NSString *) pathForFrameworkResource:(NSString *)name ofType:(NSString *)extension;

/**
 *  The name of the frameworks strings table
 *  @return The string table name.
 */
+ (NSString *) stringsTableName;

/**
 *  Returns an image resource from ZDChat bundle.
 *  @param name the name of the image.
 *  @param extension the extension of the image.
 *  @return An image, or nil if the image was not found.
 */
+ (UIImage *) imageNamed:(NSString *)name ofType:(NSString *)extension;

/**
 *  Returns a png image resource from ZDChat bundle.
 *  @param name the name of the image.
 *  @return An image, or nil if the image was not found.
 */
+ (UIImage*) imageNamed:(NSString*)imageName;


@end


CG_INLINE NSString*
ZDCLocalizedString(NSString *key, NSString *comment)
{
    return NSLocalizedStringFromTableInBundle(key, [ZDCBundleUtils stringsTableName], [ZDCBundleUtils frameworkStringsBundle],  nil);
}
