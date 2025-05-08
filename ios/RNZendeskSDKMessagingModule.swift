//
//  RNZendeskSDKMessagingModule.swift
//  RNZendeskSDKMessaging
//
//  Created by Radu Popovici on 06.05.2025.
//  Copyright © 2025 TaskRabbit. All rights reserved.
//

import Foundation
import React

import ZendeskSDKMessaging
import ZendeskSDK
import ZendeskSDKLogger

@objc(RNZendeskSDKMessagingModule)
class RNZendeskSDKMessagingModule: RCTEventEmitter {

    private let SUPPORTED_EVENTS: [String] = [
        /// Invoked when there is a change to the current total number of unread messages.
        "ZDKZendeskEventUnreadMessageCountChanged",
        /// Invoked when a rest call fails for authentication reasons.
        "ZDKZendeskEventAuthenticationFailed",
        /// Invoked when a conversation has been added.
        "ZDKZendeskEventConversationAdded",
        /// The SDK <code>ConnectionStatus</code> has changed due to an action or another event.
        "ZDKZendeskEventConnectionStatusChanged",
        /// Invoked when a message fails to be sent.
        "ZDKZendeskEventSendMessageFailed",
        /// Invoked when the conversation screen is opened.
        "ZDKZendeskEventConversationOpened",
        /// Invoked when the conversation is started on the device.
        "ZDKZendeskEventConversationStarted",
        /// Invoked when the messages shown to the user are updated.
        "ZDKZendeskEventMessagesShown"
    ];

    override func supportedEvents() -> [String] {
      return SUPPORTED_EVENTS
    }
    
    // MARK: - React Native Functions
    
    @objc(initialize:resolver:rejecter:)
    func initialize(channelKey: String, resolver resolve: @escaping RCTPromiseResolveBlock, rejecter reject: @escaping RCTPromiseRejectBlock) {
        DispatchQueue.main.async {
            Zendesk.initialize(withChannelKey: channelKey, messagingFactory: DefaultMessagingFactory()) {
                result in
                if case .success(_) = result {
                    resolve(true)
                }
                if case let .failure(error) = result {
                    print("Zendesk did not initialize.\nError: \(error.localizedDescription)")
                    reject("INIT_ERROR", error.localizedDescription, error)
                }
            }
        }
    }
    
    @objc(loginUser:resolver:rejecter:)
    func loginUser(jwt: String, resolver resolve: @escaping RCTPromiseResolveBlock, rejecter reject: @escaping RCTPromiseRejectBlock) {
        DispatchQueue.main.async {
            Zendesk.instance?.loginUser(with: jwt) { result in
                switch result {
                case .success(let user):
                    resolve(user)
                case .failure(let error):
                    reject("LOGIN_ERROR", error.localizedDescription, error)
                }
            }
        }
    }
    
    @objc(logoutUser:rejecter:)
    func logoutUser(resolver resolve: @escaping RCTPromiseResolveBlock, rejecter reject: @escaping RCTPromiseRejectBlock) {
        DispatchQueue.main.async {
            Zendesk.instance?.logoutUser { result in
                switch result {
                case .success:
                    resolve(true)
                case .failure(let error):
                    reject("LOGOUT_ERROR", error.localizedDescription, error)
                }
            }
        }
    }
    
    @objc(showMessaging)
    func showMessaging() {
        DispatchQueue.main.async {
            guard let rootViewController = RCTPresentedViewController() else {
                print("No presented view controller found")
                return
            }
            
            guard let messagingViewController = Zendesk.instance?.messaging?.messagingViewController() else {
                print("Zendesk is not initialized")
                return
            }
            
            if (type(of: rootViewController) == type(of: messagingViewController) ) {
                // exit early if the ZenDesk chat is already presented
                return;
            }
            
            rootViewController.show(messagingViewController, sender:self);
        }
    }
    
    @objc(hideMessaging)
    func hideMessaging() {
        DispatchQueue.main.async {
            guard let presentedViewController = RCTPresentedViewController() else {
                print("No presented view controller found")
                return
            }
            
            guard let messagingViewController = Zendesk.instance?.messaging?.messagingViewController() else {
                print("Zendesk is not initialized")
                return
            }

            if (type(of: presentedViewController) == type(of: messagingViewController) ) {
                // dismiss only if the presented view controller is the ZendeskSDKMessaging.ConversationViewController
                presentedViewController.dismiss(animated: true, completion: nil);
            }
        }
    }
    
    @objc(getUnreadMessageCount:rejecter:)
    func getUnreadMessageCount(resolver resolve: @escaping RCTPromiseResolveBlock, rejecter reject: @escaping RCTPromiseRejectBlock) {
        DispatchQueue.main.async {
            let unreadMessageCount = Zendesk.instance?.messaging?.getUnreadMessageCount()
            resolve(unreadMessageCount)
        }
    }
    
    @objc(sendPageViewEvent:withUrl:resolver:rejecter:)
    func sendPageViewEvent(pageTitle: String, withUrl url: String, resolver resolve: @escaping RCTPromiseResolveBlock, rejecter reject: @escaping RCTPromiseRejectBlock) {
        DispatchQueue.main.async {
            // Create a `PageView` object
            let pageView = PageView(pageTitle: pageTitle, url: url)
            Zendesk.instance?.sendPageViewEvent(pageView) { result in
                switch result {
                case .success:
                    resolve(true)
                case .failure(let error):
                    reject("PAGEVIEW_ERROR", error.localizedDescription, error)
                }
            }
        }
    }
    
    @objc(startObservingEvents)
    func startObservingEvents() {
        DispatchQueue.main.async {
            Zendesk.instance?.addEventObserver(self) { event in
                switch event {
                case .unreadMessageCountChanged(let unreadCount):
                    self.sendEvent(withName: "ZDKZendeskEventUnreadMessageCountChanged", body: ["unreadCount": unreadCount])
                case .authenticationFailed(let error as NSError):
                    self.sendEvent(withName: "ZDKZendeskEventAuthenticationFailed", body: error)
                case .conversationAdded(conversationId: let conversationId):
                    self.sendEvent(withName: "ZDKZendeskEventConversationAdded", body: ["conversationId": conversationId])
                case .connectionStatusChanged(connectionStatus: let connectionStatus):
                    self.sendEvent(withName: "ZDKZendeskEventConnectionStatusChanged", body: ["connectionStatus": connectionStatus])
                case .sendMessageFailed(let error as NSError):
                    self.sendEvent(withName: "ZDKZendeskEventSendMessageFailed", body: error)
                case .conversationOpened(id: let id, timestamp: let timestamp, conversationId: let conversationId):
                    self.sendEvent(withName: "ZDKZendeskEventConversationOpened", body: [
                        "id": id.uuidString,
                        "timestamp": String(timestamp.timeIntervalSince1970),
                        "conversationId": conversationId ?? ""
                    ])
                case .conversationStarted(id: let id, timestamp: let timestamp, conversationId: let conversationId):
                    self.sendEvent(withName: "ZDKZendeskEventConversationStarted", body: [
                        "id": id.uuidString,
                        "timestamp": String(timestamp.timeIntervalSince1970),
                        "conversationId": conversationId
                    ])
                case .messagesShown(id: let id, timestamp: let timestamp, conversationId: let conversationId, messages: let messages):
                    self.sendEvent(withName: "ZDKZendeskEventMessagesShown", body: [
                        "id": id.uuidString,
                        "timestamp": String(timestamp.timeIntervalSince1970),
                        "conversationId": conversationId,
                        "messages": messages.map {
                            var role = ""
                            switch $0.role {
                            case .business:
                                role = "BUSINESS"
                            case .user:
                                role = "USER"
                            @unknown default:
                                role = "UNKNOWN"
                            }
                            
                            return ["id": $0.id, "role": role, "timestamp": String($0.timestamp.timeIntervalSince1970)]
                        }
                    ])
                @unknown default:
                    break
                }
            }
        }
    }
    
    @objc(stopObservingEvents)
    func stopObservingEvents() {
        DispatchQueue.main.async {
            Zendesk.instance?.removeEventObserver(self)
        }
    }
    
    @objc(invalidate:)
    func invalidate(clearStorage: Bool) {
        DispatchQueue.main.async {
            Zendesk.invalidate(clearStorage)
        }
    }
    
    @objc(setLoggable:level:)
    func setLoggable(enable: Bool, level: LogLevel) {
        DispatchQueue.main.async {
            Logger.enabled = enable
            Logger.level = level
        }
    }
}
