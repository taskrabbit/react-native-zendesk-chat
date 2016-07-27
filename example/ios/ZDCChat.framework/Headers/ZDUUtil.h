/*
 *
 *  ZDU.h
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


#import <UIKit/UIKit.h>
#import "ZDUImageLoader.h"
#import "ZDUExternalImage.h"
#import "ZDUActivityViewDelegate.h"
#import "ZDCActivityView.h"
#import "ZDUTextView.h"
#import "ZDUToastStyle.h"
#import "ZDUToastView.h"
#import "ZDUViewController.h"
#import "ZDUTextView.h"


/**
 * Check if the device is in landscape orientation.
 */
CG_INLINE BOOL
ZDCUIIsLandscape()
{
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    return UIInterfaceOrientationIsLandscape(orientation);
}


/**
 * Returns the full screen frame with no attempt to account for the status bar.
 */
CG_INLINE CGRect
ZDCUIScreenFrame()
{
    CGSize screenSize = [[UIScreen mainScreen] bounds].size;
    
    CGFloat width = screenSize.width;
    CGFloat height = screenSize.height;

    if (ZDCUIIsLandscape() && width < height) {
            
        width = height;
        height = screenSize.width;
    }
    
    return CGRectMake(0, 0, width, height);
}





/**
 Convenience method for executing a block on the UI queue after a set delay
 @param block the block to be executed
 */
static inline void
zdc_on_main_thread_after(dispatch_block_t block, float delay)
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [NSThread sleepForTimeInterval:delay];
        dispatch_async(dispatch_get_main_queue(), block);
    });
}


/**
 * UI helpers and utils.
 */
@interface ZDUUtil : NSObject


/**
 * Get the appearance value for a given selector, returning the default if not set.
 * @param sel the appearance selector to be used
 * @param defaultVal the default value returned if the appearance has not been set
 * @param view the view for which to request the appearance
 * @return the apperance value if set, else the default value
 */
+ (id) appearance:(SEL)sel def:(id)defaultVal forView:(UIView*)view;

/**
 * Get the appearance value for a given selector, returning nil if not set.
 * @param sel the appearance selector to be used
 * @param view the view for which to request the appearance
 * @return the apperance value if set, else nil
 */
+ (id) appearance:(SEL)sel forView:(UIView*)view;

/**
 * Get the appearence value for the selector, returning the default if not set.
 * @param sel the appearance selector to be used
 * @param defaultVal the default value returned if the appearance has not been set
 * @param clazz the class for which to request the appearance
 * @return the apperance value if set, else the default value
 */
+ (id) appearance:(SEL)sel def:(id)defaultVal forClass:(Class)clazz;

/**
 * Get the height of one screen pixel.
 * @return 1 for non retina, 0.5 for retina
 */
+ (CGFloat) onePixel;

/**
 * isNewVersion checks to see if the majorVersionNumber is greater than or equal to the current device version
 * @param majorVersionNumber is a single integer, eg: 7
 */
+ (BOOL) isVersionOrNewer:(NSNumber*)majorVersionNumber;

/**
 * isVersionOrOlder checks to see if the majorVersionNumber is less than or equal to the current device version
 * @param majorVersionNumber is a single integer, eg: 7
 */
+ (BOOL) isVersionOrOlder:(NSNumber*)majorVersionNumber;

/**
 * isSameVersion checks to see if the majorVersionNumber is the same as the current device version
 * @param majorVersionNumber is a single integer, eg: 7
 */
+ (BOOL) isSameVersion:(NSNumber*)majorVersionNumber;

/**
 * Running on iPad?
 * @return YES if running device is an iPad.
 */
+ (BOOL) isiPad;

/**
 * Running on iPhone?
 * @return YES is running device is an iPhone.
 */
+ (BOOL) isiPhone;

/**
 * Very basic regex email check, does NOT validate length.
 * @param emailString the email to be checked
 * @return YES if email appears valid
 */
+ (BOOL) emailValid:(NSString*)emailString;

/*
 * Physically transform an image to match its imageRotation property.
 * @param image Image to rotate.
 * @return Correctly rotated image.
 */
+ (UIImage *)fixOrientationOfImage:(UIImage*)image;

/**
 * Get a darker copy of the supplied color.
 * @param c the orifinal color
 * @param diff the amount to darken by (0 .. 1.0)
 * @return the darker color
 */
+ (UIColor *)darkerColorForColor:(UIColor *)c by:(float)diff;

/**
 * Version safe navigation bar background color.
 */
+ (UIColor*) navBarTintColor;

/**
 * Version safe navigation bar item color.
 */
+ (UIColor*) navTintColor;


@end


/**
 * Get the origin of the supplied view in the window.
 */
CG_INLINE CGPoint
ZDCUIOriginInWindow(UIView *view)
{
    UIView *superView = view;

    do {
        superView = superView.superview;
    } while (superView.superview);

    CGPoint point = [view convertPoint:view.bounds.origin toView:superView];

    if ([ZDUUtil isVersionOrNewer:@(8)]) {
        return point;
    }

    CGRect screenBounds = [UIScreen mainScreen].bounds;

    switch ([[UIApplication sharedApplication] statusBarOrientation]) {

        case UIInterfaceOrientationPortraitUpsideDown: {
            return CGPointMake(screenBounds.size.width - point.x, screenBounds.size.height - point.y);
        }
        case UIInterfaceOrientationLandscapeLeft: {
            return CGPointMake(screenBounds.size.height - point.y, point.x);
        }
        case UIInterfaceOrientationLandscapeRight: {
            return CGPointMake(point.y, screenBounds.size.width - point.x);
        }
        default: {
            return point;
        }
    }
}

