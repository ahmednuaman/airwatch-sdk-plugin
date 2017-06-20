//
//  AWSDKBridge.h
//
//  Created by Jeff Jones on 7/22/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import <Foundation/Foundation.h>
#import <AWSDK/AWController.h>

@protocol AWSDKBridgeDelegate

- (void) initSuccess;
- (void) initFailure;
- (void) wipe;
- (void) lock;
- (void) unlock;
- (void) stopNetworkActivity: (AWNetworkActivityStatus) networkActivityStatus;
- (void) resumeNetworkActivity;

@end


@protocol AWSDKCertificateReceiver

- (void) receivedCertificate: (SecIdentityRef) cert
                   withError: (NSError *) error;

@end


@interface AWSDKBridge : NSObject <AWSDKDelegate>

@property (weak, nonatomic) id<AWSDKBridgeDelegate> bridgeDelegate;

+ (instancetype) sharedInstance;

- (void) startAirwatchSDK;

- (BOOL) isInitialized;

- (void) fetchCertificatesForReceiver: (id<AWSDKCertificateReceiver>) certReceiver;

// Connection information

- (NSString *) groupId;

- (NSString *) username;

- (NSString *) serverName;

// Restrictions payload

- (BOOL) allowCopyPaste;

- (BOOL) allowOffline;

- (BOOL) restrictDocumentToApps;

- (NSArray *) allowedApplications;

// Custom settings payload

- (NSString *) customSettings;

// Uncategorized

- (BOOL) isCompliant;

- (BOOL) isCompromised;


@end
