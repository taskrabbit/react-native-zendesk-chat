//
//  RNZendeskSDKMessaging.m
//  Tasker
//
//  Created by Jean-Richard Lai on 11/23/15.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>
#import <React/RCTEventEmitter.h>

@interface RCT_EXTERN_MODULE(RNZendeskSDKMessagingModule, RCTEventEmitter)

RCT_EXTERN_METHOD(initialize: (NSString *)channelKey
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)

RCT_EXTERN_METHOD(loginUser: (NSString *)jwt
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)

RCT_EXTERN_METHOD(logoutUser: (RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)

RCT_EXTERN_METHOD(showMessaging)

RCT_EXTERN_METHOD(hideMessaging)

RCT_EXTERN_METHOD(getUnreadMessageCount:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)

RCT_EXTERN_METHOD(sendPageViewEvent:(NSString *)pageTitle
                  withUrl:(NSString *)url
                  resolver:(RCTPromiseResolveBlock)resolve
                  rejecter:(RCTPromiseRejectBlock)reject)

RCT_EXTERN_METHOD(startObservingEvents)

RCT_EXTERN_METHOD(stopObservingEvents)

RCT_EXTERN_METHOD(invalidate:(BOOL)clearStorage)

RCT_EXTERN_METHOD(setLoggable:(BOOL)enable level:(NSInteger)logLevel)

@end
