/*
 *
 *  ZDCDeviceInfo.h
 *  ZDCChat
 *
 *  Created by Zendesk on 11/04/2014.
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
#import <UIKit/UIKit.h>


/**
 * Helper class for retrieving device information.
 */
@interface ZDCDeviceInfo : NSObject


/**
 * Get a String of the device type, e.g. 'iPad 3 (WiFi)'
 * @return the device type if recognised, the base OS device type string if not recognised.
 */
+ (NSString *) deviceType;

/**
 * Get the total device memory.
 * @return the device memory in GB
 */
+ (double) totalDeviceMemory;

/**
 * Get the free disk space of the device.
 * @return the free disk space of the device in GB
 */
+ (double) freeDiskspace;

/**
 * Get the total disk space of the device.
 * @return the total disk space of the device in GB
 */
+ (double) totalDiskspace;

/**
 * The current battery level of the device.
 * @return the current battery level of the device as a percentage
 */
+ (CGFloat) batteryLevel;

/**
 * The current region setting of the device.
 * @return the current region
 */
+ (NSString*) region;

/**
 * The current language of the device
 * @return the language
 */
+ (NSString*) language;

/**
 * Get the app version.
 * @return the app version as reported by CFBundleShortVersionString
 */
+ (NSString*) appVersion;

/**
 * Get the app build number
 * @return get the app build number as reported by CFBundleVersion
 */
+ (NSString*) appBuildNumber;

/**
 * Get the application name.
 * @return the app name as reported by CFBundleName
 */
+ (NSString*) appName;


@end

