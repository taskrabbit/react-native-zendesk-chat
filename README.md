# react-native-zendesk-chat

Simple module that allows displaying Zopim Chat from Zendesk for React Native.

## VERSIONS

- For RN version higher than 0.59 use version >= 0.3.0 (Zendesk Chat v1)
- For RN version lower than 0.59 use version <= 0.2.2 (Zendesk Chat v1)

## Known Issues

## Getting Started

Follow the instructions to install the SDK for [iOS](https://developer.zendesk.com/embeddables/docs/ios-chat-sdk/introduction) and [Android](https://developer.zendesk.com/embeddables/docs/android-chat-sdk/introduction).

With npm:

`npm install react-native-zendesk-chat --save`

or with yarn:

`yarn add react-native-zendesk-chat`

### QuickStart & Usage

1. Setup Native Dependencies<br/> **iOS** If you're on react-native >= 0.60 and you have Cocoapods setup, then you just need to:

```bash
$ yarn install # and see if there are any errors
$ (cd ios; pod install) # and see if there are any errors
 # -- you may need to do `pod install --repo-update`
```

If you're on older react-native versions, please see the [Advanced Setup](#advanced-setup) section below

**Android** If you're on react-native >= 0.60, Android should autodetect this dependency. You may need to call `react-native link`

2. Call the JS Initializer:

```javascript
import ZendeskChat from "react-native-zendesk-chat";

// Once in your application:
ZendeskChat.init("YOUR_ZENDESK_ACCOUNT_KEY");
```

3. Show the Chat UI

```javascript
// On button press, when you want to show chat:
ZendeskChat.startChat({
	name: user.full_name,
	email: user.email,
	phone: user.mobile_phone,
	tags: ["tag1", "tag2"],
	department: "Your department",
});
```

### Advanced Setup

Advanced users, or users running on older versions of react-native may want to initialize things in native.

#### iOS: Manually Setting up with Cocoapods

If you're on iOS < 0.60, you may need to manually install the cocoapod:

Add a reference to your Podfile:

```Podfile
pod 'RNZendeskChat', :git => 'https://github.com/taskrabbit/react-native-zendesk-chat.git'
```

then run pod install: `(cd ios; pod install)`

or manually:

In Xcode, drag and drop `node_modules/react-native-zendesk-chat/RNZendeskChat.m` and `node_modules/react-native-zendesk-chat/RNZendeskChat.h` into your project.

#### iOS: Configure `ZDCChat` in `AppDelegate.m`:

```objective-c
#import <ZDCChat/ZDCChat.h>

// ...

// Inside the appropriate appDidFinishLaunching method
[ZDCChat initializeWithAccountKey:@"YOUR_ZENDESK_ACCOUNT_KEY"];

// And access other interesting APIs
```

#### Android: Manual Setup & Configuration

If you're on react-native < 0.60, you should be able to call `react-native link`.

If this doesn't work, then you may need to do a complete manual install as follows:

1. Open up `android/app/main/java/[...]/MainApplication.java`

- Add `import com.taskrabbit.zendesk.*;` to the imports at the top of the file
- Add `new RNZendeskChatPackage(this)` to the list returned by the `getPackages()` method

2. Append the following lines to `android/settings.gradle`:

```gradle
include ':react-native-zendesk-chat'
project(':react-native-zendesk-chat').projectDir = new File(rootProject.projectDir,	'../node_modules/react-native-zendesk-chat/android')
```

3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:

```gradle
compile project(':react-native-zendesk-chat')
```

4. Configure `ZopimChat` in `android/app/main/java/[...]/MainActivity.java`

```java
// Note: there is a JS method to do this!
// Call this once in your Activity's bootup lifecycle
ZopimChat.init("YOUR_ZENDESK_ACCOUNT_KEY").build();
```

## TODO

- Allow setting form configuration from JS
- Add examples

## License

React Native is MIT licensed, as found in the [LICENSE](https://github.com/taskrabbit/react-native-zendesk-chat/LICENSE) file.
