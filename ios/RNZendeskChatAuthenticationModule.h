//
//  RNZendeskChatAuthenticationModule.h
//  Pods
//
//  Created by Eric Adamski on 2023-09-25.
//

#ifndef RNZendeskChatAuthenticationModule_h
#define RNZendeskChatAuthenticationModule_h

#import <ChatSDK/ChatSDK.h>
#import <ChatProvidersSDK/ChatProvidersSDK.h>

@interface JwtAuthStrategy: NSObject<ZDKJWTAuthenticator>
- (id)initJWTAuthFromConfig: (NSDictionary *)options;
- (bool)canUseJwtAuth;
@end

#endif /* RNZendeskChatAuthenticationModule_h */
