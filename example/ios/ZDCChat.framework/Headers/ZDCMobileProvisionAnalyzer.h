/*
 *
 *  ZDCMobileProvisionAnalyzer.h
 *  ZDCChat
 *
 *  Created by Zendesk on 22/04/2014.
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


@interface ZDCMobileProvisionAnalyzer : NSObject

/**
 * Check if this installation is a production or development version of the App.
 * @return 'p' if production, 'd' if dev
 */
+ (NSString*) getEnvironment;


@end

