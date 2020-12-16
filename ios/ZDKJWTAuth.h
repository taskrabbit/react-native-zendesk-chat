#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ChatProvidersSDK/ChatProvidersSDK.h>

@interface ZDKJWTAuth: NSObject<ZDKJWTAuthenticator>

{
    NSString *AlfUrl;
}

- (void)setUrl:(NSString *_Nullable) urlString;
- (void)getToken:(void (^ _Nonnull)(NSString * _Nullable, NSError * _Nullable))completion;

@end
