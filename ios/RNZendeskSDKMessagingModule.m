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

NSArray *SUPPORTED_EVENTS = @[
    /// Invoked when there is a change to the current total number of unread messages.
    @"ZDKZendeskEventUnreadMessageCountChanged",
    /// Invoked when a rest call fails for authentication reasons.
    @"ZDKZendeskEventAuthenticationFailed",
    /// Invoked when a conversation has been added.
    @"ZDKZendeskEventConversationAdded",
    /// The SDK <code>ConnectionStatus</code> has changed due to an action or another event.
    @"ZDKZendeskEventConnectionStatusChanged",
    /// Invoked when a message fails to be sent.
    @"ZDKZendeskEventSendMessageFailed",
    /// Invoked when the conversation screen is opened.
    @"ZDKZendeskEventConversationOpened",
    /// Invoked when the conversation is started on the device.
    @"ZDKZendeskEventConversationStarted",
    /// Invoked when the messages shown to the user are updated.
    @"ZDKZendeskEventMessagesShown"
];


RCT_EXPORT_MODULE(RNZendeskSDKMessagingModule);

- (NSArray<NSString *> *)supportedEvents {
    return SUPPORTED_EVENTS;
}

RCT_EXPORT_METHOD(initialize: (NSString *)channelKey
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject) {
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

RCT_EXPORT_METHOD(startObservingEvents) {
    // Get your Zendesk instance:
    Zendesk *instance = [Zendesk instance];
    
    // To add an event observer to your Zendesk instance:
    [instance addEventObserver:self :^(enum ZDKZendeskEvent event, id _Nullable value) {
        switch (event) {
            case ZDKZendeskEventUnreadMessageCountChanged:
                [self sendEventWithName:@"ZDKZendeskEventUnreadMessageCountChanged" body:value];
            case ZDKZendeskEventAuthenticationFailed:
                [self sendEventWithName:@"ZDKZendeskEventAuthenticationFailed" body:value];
            case ZDKZendeskEventConversationAdded:
                [self sendEventWithName:@"ZDKZendeskEventConversationAdded" body:value];
            case ZDKZendeskEventConnectionStatusChanged:
                [self sendEventWithName:@"ZDKZendeskEventConnectionStatusChanged" body:value];
            case ZDKZendeskEventSendMessageFailed:
                [self sendEventWithName:@"ZDKZendeskEventSendMessageFailed" body:value];
            case ZDKZendeskEventConversationOpened:
                [self sendEventWithName:@"ZDKZendeskEventConversationOpened" body:value];
            case ZDKZendeskEventConversationStarted:
                [self sendEventWithName:@"ZDKZendeskEventConversationStarted" body:value];
            case ZDKZendeskEventMessagesShown:
                [self sendEventWithName:@"ZDKZendeskEventMessagesShown" body:value];
            default:
                break;
        }
    }];
}

RCT_EXPORT_METHOD(stopObservingEvents) {
    // Get your Zendesk instance:
    Zendesk *instance = [Zendesk instance];
    
    // To remove an event observer from your Zendesk instance:
    [instance removeEventObserver:self];
}

RCT_EXPORT_METHOD(loginUser: (NSString *)jwt
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        Zendesk *instance = [Zendesk instance];
        [instance loginUserWith:jwt completionHandler:^(ZDKZendeskUser * _Nullable user, NSError * _Nullable error) {
            if (error != nil) {
                NSLog(@"Zendesk can't login.\nError: %@", error.localizedDescription);
                reject(@(error.code).stringValue, error.localizedDescription, error);
                return;
            }
            // login successful
            resolve(user);
        }];
    });
}

RCT_EXPORT_METHOD(logoutUser: (RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        Zendesk *instance = [Zendesk instance];
        [instance logoutUserWithCompletionHandler:^(NSError * _Nullable error) {
            if (error != nil) {
                NSLog(@"Zendesk can't logout.\nError: %@", error.localizedDescription);
                reject(@(error.code).stringValue, error.localizedDescription, error);
                return;
            }
            // logout successful
            resolve(@(YES));
        }];
    });
}

RCT_EXPORT_METHOD(showMessaging) {
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *rootViewController = RCTPresentedViewController();
        UIViewController *messagingViewController = [Zendesk.instance.messaging messagingViewController];
        
        if (rootViewController != nil && messagingViewController != nil) {
            if ([rootViewController isMemberOfClass: [messagingViewController class]]) {
                // exit early if the ZenDesk chat is already presented
                return;
            }
            
            [rootViewController showViewController:messagingViewController sender:self];
        }
    });
}

RCT_EXPORT_METHOD(hideMessaging)
{
  dispatch_async(dispatch_get_main_queue(), ^{
      UIViewController *presentedViewController = RCTPresentedViewController();
      UIViewController *messagingViewController = [Zendesk.instance.messaging messagingViewController];

      if (presentedViewController != nil &&
          messagingViewController != nil &&
          [presentedViewController isMemberOfClass: [messagingViewController class]]) {
          // dismiss only if the presented view controller is the ZenDesk chat modal
          [presentedViewController dismissViewControllerAnimated:YES completion:nil];
      }
  });
}

RCT_EXPORT_METHOD(getUnreadMessageCount:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        // Get the instance of messaging
        Zendesk *instance = [Zendesk instance];
        // Get the unread count
        NSNumber *unreadCount = @(instance.messaging.getUnreadMessageCount);
        resolve(unreadCount);
    });
}

RCT_EXPORT_METHOD(sendPageViewEvent:(NSString *)pageTitle
                  withUrl:(NSString *)url
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        Zendesk *instance = [Zendesk instance];
        // Create a PageView
        ZDKPageView *pageView = [[ZDKPageView alloc] initWithPageTitle:pageTitle url:url];
        [instance sendPageViewEvent:pageView completionHandler:^(NSError *error) {
            if (error != nil) {
                NSLog(@"Zendesk can't send PageView event.\nError: %@", error.localizedDescription);
                reject(@(error.code).stringValue, error.localizedDescription, error);
                return;
            }
            // event sent successfully
            resolve(@(YES));
        }];
    });
}

RCT_EXPORT_METHOD(invalidate:(BOOL)clearStorage)
{
  dispatch_async(dispatch_get_main_queue(), ^{
      [Zendesk invalidateWithClearStorage:clearStorage];
  });
}

RCT_EXPORT_METHOD(setLoggable:(BOOL)enable location:(NSInteger)logLevel)
{
    ZDKLogger.enabled = enable;
    ZDKLogger.level = logLevel;
}

@end
