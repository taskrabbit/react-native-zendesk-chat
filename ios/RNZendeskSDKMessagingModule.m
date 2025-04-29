//
//  RNZendeskChat.m
//  Tasker
//
//  Created by Jean-Richard Lai on 11/23/15.
//


#import "RNZendeskChatModule.h"

#import <React/RCTUtils.h>
#import <React/RCTConvert.h>

#import <ChatSDK/ChatSDK.h>
#import <ChatProvidersSDK/ChatProvidersSDK.h>
#import <MessagingSDK/MessagingSDK.h>
#import <CommonUISDK/CommonUISDK.h>


@implementation RCTConvert (ZDKChatFormFieldStatus)

RCT_ENUM_CONVERTER(ZDKFormFieldStatus,
				   (@{
					   @"required": @(ZDKFormFieldStatusRequired),
					   @"optional": @(ZDKFormFieldStatusOptional),
					   @"hidden": @(ZDKFormFieldStatusHidden),
					}),
				   ZDKFormFieldStatusOptional,
				   integerValue);

@end

@interface RNZendeskChatModule ()
@end

@implementation RNZendeskChatModule
// Backwards compatibility with the unnecessary setVisitorInfo method
ZDKChatAPIConfiguration *_visitorAPIConfig;


RCT_EXPORT_MODULE(RNZendeskChatModule);

RCT_EXPORT_METHOD(setVisitorInfo:(NSDictionary *)options) {
	if (!NSThread.isMainThread) {
		dispatch_async(dispatch_get_main_queue(), ^{
			[self setVisitorInfo:options];
		});
		return;
	}

	ZDKChat.instance.configuration = _visitorAPIConfig = [self applyVisitorInfo:options intoConfig: _visitorAPIConfig ?: [[ZDKChatAPIConfiguration alloc] init]];
}

- (ZDKChatAPIConfiguration*)applyVisitorInfo:(NSDictionary*)options intoConfig:(ZDKChatAPIConfiguration*)config {
	if (options[@"department"]) {
		config.department = options[@"department"];
	}
	if (options[@"tags"]) {
		config.tags = options[@"tags"];
	}
	config.visitorInfo = [[ZDKVisitorInfo alloc] initWithName:options[@"name"]
														email:options[@"email"]
												  phoneNumber:options[@"phone"]];

	NSLog(@"[RNZendeskChatModule] Applied visitor info: department: %@ tags: %@, email: %@, name: %@, phone: %@", config.department, config.tags, config.visitorInfo.email, config.visitorInfo.name, config.visitorInfo.phoneNumber);
	return config;
}

#define RNZDKConfigHashErrorLog(options, what)\
if (!!options) {\
	NSLog(@"[RNZendeskChatModule] Invalid %@ -- expected a config hash", what);\
}

- (ZDKMessagingConfiguration *)messagingConfigurationFromConfig:(NSDictionary*)options {
	ZDKMessagingConfiguration *config = [[ZDKMessagingConfiguration alloc] init];
	if (!options || ![options isKindOfClass:NSDictionary.class]) {
		RNZDKConfigHashErrorLog(options, @"MessagingConfiguration config options");
		return config;
	}
	if (options[@"botName"]) {
		config.name = options[@"botName"];
	}

	if (options[@"botAvatarName"]) {
		config.botAvatar = [UIImage imageNamed:@"botAvatarName"];
	} else if (options[@"botAvatarUrl"]) {
		config.botAvatar = [UIImage imageWithData:[NSData dataWithContentsOfURL:[NSURL URLWithString:options[@"botAvatarUrl"]]]];
	}

	return config;
}

- (ZDKChatFormConfiguration * _Nullable)preChatFormConfigurationFromConfig:(NSDictionary*)options {
	if (!options || ![options isKindOfClass:NSDictionary.class]) {
		RNZDKConfigHashErrorLog(options, @"pre-Chat-Form Configuration Options");
		return nil;
	}
#define ParseFormFieldStatus(key)\
	ZDKFormFieldStatus key = [RCTConvert ZDKFormFieldStatus:options[@"" #key]]
	ParseFormFieldStatus(name);
	ParseFormFieldStatus(email);
	ParseFormFieldStatus(phone);
	ParseFormFieldStatus(department);
#undef ParseFormFieldStatus
	return [[ZDKChatFormConfiguration alloc] initWithName:name
													email:email
											  phoneNumber:phone
											   department:department];
}
- (ZDKChatConfiguration *)chatConfigurationFromConfig:(NSDictionary*)options {
	options = options ?: @{};

	ZDKChatConfiguration* config = [[ZDKChatConfiguration alloc] init];
	if (![options isKindOfClass:NSDictionary.class]){
		RNZDKConfigHashErrorLog(options, @"Chat Configuration Options");
		return config;
	}
	NSDictionary * behaviorFlags = options[@"behaviorFlags"];
	if (!behaviorFlags || ![behaviorFlags isKindOfClass:NSDictionary.class]) {
		RNZDKConfigHashErrorLog(behaviorFlags, @"BehaviorFlags -- expected a config hash");
		behaviorFlags = NSDictionary.dictionary;
	}

#define ParseBehaviorFlag(key, target)\
config.target = [RCTConvert BOOL: behaviorFlags[@"" #key] ?: @YES]
	ParseBehaviorFlag(showPreChatForm, isPreChatFormEnabled);
	ParseBehaviorFlag(showChatTranscriptPrompt, isChatTranscriptPromptEnabled);
	ParseBehaviorFlag(showOfflineForm, isOfflineFormEnabled);
	ParseBehaviorFlag(showAgentAvailability, isAgentAvailabilityEnabled);
#undef ParseBehaviorFlag

	if (config.isPreChatFormEnabled) {
		ZDKChatFormConfiguration * formConfig = [self preChatFormConfigurationFromConfig:options[@"preChatFormOptions"]];
		if (!!formConfig) {
			// Zendesk Swift Code crashes if you provide a nil form
			config.preChatFormConfiguration = formConfig;
		}
	}
	return config;
}

RCT_EXPORT_METHOD(startChat:(NSDictionary *)options) {
	if (!options || ![options isKindOfClass: NSDictionary.class]) {
		if (!!options){
			NSLog(@"[RNZendeskChatModule] Invalid JS startChat Configuration Options -- expected a config hash");
		}
		options = NSDictionary.dictionary;
	}

	dispatch_sync(dispatch_get_main_queue(), ^{

		ZDKChat.instance.configuration = [self applyVisitorInfo:options
													 intoConfig: _visitorAPIConfig ?: [[ZDKChatAPIConfiguration alloc] init]];

		ZDKChatConfiguration * chatConfig = [self chatConfigurationFromConfig:options];

		NSError *error = nil;
		NSArray *engines = @[
			[ZDKChatEngine engineAndReturnError:&error]
		];
		if (!!error) {
			NSLog(@"[RNZendeskChatModule] Internal Error loading ZDKChatEngine %@", error);
			return;
		}

		ZDKMessagingConfiguration *messagingConfig = [self messagingConfigurationFromConfig: options[@"messagingOptions"]];

		UIViewController *viewController = [ZDKMessaging.instance buildUIWithEngines:engines
																 configs:@[chatConfig, messagingConfig]
																   error:&error];
		if (!!error) {
			NSLog(@"[RNZendeskChatModule] Internal Error building ZDKMessagingUI %@",error);
			return;
		}

		viewController.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle: options[@"localizedDismissButtonTitle"] ?: @"Close"
																						   style: UIBarButtonItemStylePlain
																						  target: self
																						  action: @selector(dismissChatUI)];

		UINavigationController *chatController = [[UINavigationController alloc] initWithRootViewController: viewController];
		[RCTPresentedViewController() presentViewController:chatController animated:YES completion:nil];
	});
}

- (void) dismissChatUI {
	[RCTPresentedViewController() dismissViewControllerAnimated:YES completion:nil];
}

RCT_EXPORT_METHOD(_initWith2Args:(NSString *)zenDeskKey appId:(NSString *)appId) {
	if (appId) {
		[ZDKChat initializeWithAccountKey:zenDeskKey appId:appId queue:dispatch_get_main_queue()];
	} else {
		[ZDKChat initializeWithAccountKey:zenDeskKey queue:dispatch_get_main_queue()];
	}
}

RCT_EXPORT_METHOD(registerPushToken:(NSString *)token) {
	dispatch_sync(dispatch_get_main_queue(), ^{
		[ZDKChat registerPushTokenString:token];
	});
}

RCT_EXPORT_METHOD(areAgentsOnline:
	(RCTPromiseResolveBlock) resolve
	rejecter: (RCTPromiseRejectBlock) reject) {

  [ZDKChat.accountProvider getAccount:^(ZDKChatAccount *account, NSError *error) {
		if (account) {
			switch (account.accountStatus) {
				case ZDKChatAccountStatusOnline:
					resolve(@YES);
					break;

				default:
					resolve(@NO);
					break;
			}
		} else {
			reject(@"no-available-zendesk-account", @"DevError: Not connected to Zendesk or network issue", error);
		}
	}];
}

@end
