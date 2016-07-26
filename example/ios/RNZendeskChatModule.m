//
//  RNZendeskChat.m
//  Tasker
//
//  Created by Jean-Richard Lai on 11/23/15.
//  Copyright © 2015 Facebook. All rights reserved.
//

#import "RNZendeskChatModule.h"
#import <ZDCChat/ZDCChat.h>

@implementation RNZendeskChatModule

RCT_EXPORT_MODULE(RNZendeskChatModule);

RCT_EXPORT_METHOD(setVisitorInfo:(NSDictionary *)options) {
  [ZDCChat updateVisitor:^(ZDCVisitorInfo *visitor) {
    if (options[@"name"]) {
      visitor.name = options[@"name"];
    }
    if (options[@"email"]) {
      visitor.email = options[@"email"];
    }
    if (options[@"phone"]) {
      visitor.phone = options[@"phone"];
    }
    visitor.shouldPersist = options[@"shouldPersist"] || NO;
  }];
}

RCT_EXPORT_METHOD(startChat:(NSDictionary *)options) {
  [self setVisitorInfo:options];

  dispatch_sync(dispatch_get_main_queue(), ^{
    [ZDCChat startChat:^(ZDCSessionConfig *config) {
      config.preChatDataRequirements.name       = ZDCPreChatDataRequired;
      config.preChatDataRequirements.email      = ZDCPreChatDataRequired;
      config.preChatDataRequirements.phone      = ZDCPreChatDataRequired;
      config.preChatDataRequirements.department = ZDCPreChatDataRequired;
      config.preChatDataRequirements.message    = ZDCPreChatDataRequired;
    }];
  });
}

@end
