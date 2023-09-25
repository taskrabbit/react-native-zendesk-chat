//
//  RNZendeskChatAuthenticationModule.m
//  RNZendeskChat
//
//  Created by Eric Adamski on 2023-09-25.
//  Copyright © 2023 TaskRabbit. All rights reserved.
//

#import "RNZendeskChatAuthenticationModule.h"

#import <ChatSDK/ChatSDK.h>
#import <ChatProvidersSDK/ChatProvidersSDK.h>

@implementation JwtAuthStrategy

NSString *tokenEndpoint = nil;
NSString *externalId = nil;
NSString *prefetchedJwt = nil;
NSDictionary *extraHeaders = nil;

- (id)initJWTAuthFromConfig: (NSDictionary *)options {
    self = [super init];
    
    NSDictionary *authOptions = options[@"authenticationOptions"];
    
    if (!authOptions || ![authOptions isKindOfClass:NSDictionary.class]) {
        return self;
    }
    
    if (self) {
        if (authOptions[@"jwt"] != nil) {
            prefetchedJwt = authOptions[@"jwt"];
        } else {
            
            NSDictionary *headers = authOptions[@"headers"];
            
            if (headers && [headers isKindOfClass:NSDictionary.class]) {
                extraHeaders = headers;
            }
            
            tokenEndpoint = authOptions[@"tokenEndpoint"];
            externalId = authOptions[@"externalId"];
        }
    }
    
    return self;
}

- (bool)canUseJwtAuth {
    return (tokenEndpoint != nil && externalId != nil) || prefetchedJwt != nil;
}

- (void)getToken: (void (^)(NSString * _Nullable, NSError * _Nullable)) completion {
    if (prefetchedJwt != nil) {
        completion(prefetchedJwt, nil);
        
        return;
    }
    
    [self makeHttpRequest: completion];
}

- (void)makeHttpRequest: (void (^)(NSString * _Nullable, NSError * _Nullable)) completion {
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:
                                    [NSURL URLWithString:tokenEndpoint]];
    [request setHTTPMethod:@"POST"];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setHTTPBody:[self getTokenRequestJson]];
    
    [self applyCustomHeaders: request];
    
    [[[NSURLSession sharedSession]
     dataTaskWithRequest:request
     completionHandler:
         ^(NSData * _Nullable responseData,
           NSURLResponse * _Nullable response,
           NSError * _Nullable error) {
        
        if (error != nil) {
            NSLog(@"[ZendeskChat:JWTAuthStrategy] Found error requesting JWT token.");
            
            return;
        }
        
        NSError *parseError;
        NSDictionary *responseJson = [NSJSONSerialization JSONObjectWithData:responseData options:NSJSONReadingMutableContainers error:&parseError];
        
        if (parseError == nil) {
            NSString *jwt = [responseJson objectForKey:@"jwt"];
            
            completion(jwt, nil);
        } else {
            completion(nil, parseError);
        }
        
    }] resume];
}

- (void)applyCustomHeaders: (NSMutableURLRequest *)request {
    if (extraHeaders == nil) {
        return;
    }
    
    for (id header in extraHeaders) {
        [request addValue:extraHeaders[header] forHTTPHeaderField:header];
    }
}

- (NSData *)getTokenRequestJson {
    NSError *error;
    NSDictionary *data = [[NSDictionary alloc] initWithObjectsAndKeys: externalId, @"externalId", nil];
    
    return [NSJSONSerialization dataWithJSONObject:data options:0 error:&error];
}

@end
