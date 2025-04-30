//
//  RNZendeskSDKMessaging.m
//  Tasker
//
//  Created by Jean-Richard Lai on 11/23/15.
//


#import "RNZendeskSDKMessagingModule.h"

#import <React/RCTUtils.h>
#import <React/RCTConvert.h>

#import <ZendeskSDK/ZendeskSDK.h>
#import <ZendeskSDKMessaging/ZendeskSDKMessaging.h>
#import <ZendeskSDKLogger/ZendeskSDKLogger.h>

@interface RNZendeskSDKMessagingModule ()
@end

@implementation RNZendeskSDKMessagingModule


RCT_EXPORT_MODULE(RNZendeskSDKMessagingModule);

RCT_EXPORT_METHOD(initialize: (NSString *)channelKey resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject) {
    dispatch_async(dispatch_get_main_queue(), ^{
        [Zendesk initializeWithChannelKey:channelKey messagingFactory:[[ZDKDefaultMessagingFactory alloc] init] completionHandler:^(Zendesk * _Nullable zendesk, NSError * _Nullable error) {
            if (error != nil) {
                NSLog(@"Zendesk did not initialize.\nError: %@", error.localizedDescription);
                reject(@(error.code).stringValue, error.localizedDescription, error);
                return;
            }
            resolve(@(YES));
        }];
    });
}

RCT_EXPORT_METHOD(showMessaging) {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *rootViewController = RCTPresentedViewController();
        UIViewController *messagingViewController = [Zendesk.instance.messaging messagingViewController];
        
        if (rootViewController != nil && messagingViewController != nil) {
            [rootViewController showViewController:messagingViewController sender:self];
        }
    });
}

RCT_EXPORT_METHOD(hideMessaging)
{
  dispatch_async(dispatch_get_main_queue(), ^{
      UIViewController *messagingViewController = [Zendesk.instance.messaging messagingViewController];
      
      if (messagingViewController != nil && messagingViewController.isBeingPresented) {
          [messagingViewController dismissViewControllerAnimated:YES completion:nil];
      }
  });
}

RCT_EXPORT_METHOD(getUnreadMessageCount:
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        // Get the instance of messaging
        Zendesk *instance = [Zendesk instance];
        // Get the unread count
        NSNumber *unreadCount = @(instance.messaging.getUnreadMessageCount);
        resolve(unreadCount);
    });
}

RCT_EXPORT_METHOD(invalidate:(BOOL)clearStorage)
{
  dispatch_async(dispatch_get_main_queue(), ^{
      [Zendesk invalidateWithClearStorage:clearStorage];
  });
}

RCT_EXPORT_METHOD(setLogLevel:(BOOL)enable location:(NSInteger)logLevel)
{
    ZDKLogger.enabled = enable;
    ZDKLogger.level = logLevel;
}

@end
