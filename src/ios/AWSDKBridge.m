//
//  AWSDKBridge.m
//
//  Created by Jeff Jones on 7/22/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import "AWSDKBridge.h"
#import "AWCertificateUtility.h"
#import <AWSDK/AWSDKCore.h>
#import <AWSDK/AWCommandManager.h>
#import <AWSDK/AWProfile.h>

static NSString * const DEFAULT_CALLBACK_SCHEME = @"awsdkcallback";

static AWSDKBridge *sharedInstance;

@interface AWSDKBridge ()

@property (strong, nonatomic) AWProfile *sdkProfile;
@property (strong, nonatomic) AWController *controller;
@property (weak, nonatomic) id<AWSDKCertificateReceiver> certReceiver;

@end

@implementation AWSDKBridge

BOOL initialized = NO;

+ (instancetype) sharedInstance {
    @synchronized (self) {  // self in a static method means the class object
        if (!sharedInstance)
            sharedInstance = [AWSDKBridge new];
    }
    return sharedInstance;
}

- (instancetype) init {
    if (self = [super init]) {
        [[NSNotificationCenter defaultCenter] addObserver: self
                                                 selector: @selector(handleUpdatedProfile:)
                                                     name: AWNotificationCommandManagerInstalledNewProfile
                                                   object: nil];
    }
    return self;
}


- (void) startAirwatchSDK {
    self.controller = [AWController clientInstance];

    self.controller.callbackScheme = [self findAirWatchSDKCallbackScheme];
    self.controller.delegate = self;

    [self.controller start];
}

- (BOOL) isInitialized {
    return initialized;
}

- (void) fetchCertificatesForReceiver: (id<AWSDKCertificateReceiver>) certReceiver {
    self.certReceiver = certReceiver;
    if ([self isInitialized]) {
        NSLog(@"In AWSDKBridge -fetchCertForReceiver, SDK already initialized");
        [[AWCommandManager sharedManager] loadCommands];
    } else {
        NSLog(@"In AWSDKBridge -fetchCertForReceiver, SDK not yet initialized");
        [self startAirwatchSDK];
    }
}



/* initialCheckDoneWithError is called after the SDK finishes its "Start" workflow.
 * If the error is nil, then initialization was successful.
 */
- (void) initialCheckDoneWithError: (NSError *) error {

    if (error) {
        NSLog(@"In AWSDKBridge -initialCheckDoneWithError: Initial check failed with error: %@", [error localizedDescription]);
        [self initFailure];
    } else {
        NSLog(@"In AWSDKBridge -initialCheckDoneWithError: Initial check succeeded");
        initialized = YES;
        [self initSuccess];
    }
}


/* receivedProfiles is called after initialCheckDoneWithError.
 * This will retrieve all of the SDK profiles queued by the server.
 * The most recent profile will be the lastObject in the profiles array.
 */
- (void) receivedProfiles: (NSArray *) profiles {
    NSLog(@"In AWSDKBridge -receivedProfiles: got %d profiles", (int)[profiles count]);
    for (int i = 0; i < [profiles count]; i++) {
        AWProfile *profile = (AWProfile *)profiles[i];
        if (profile.profileType == AWSDKProfile)
            self.sdkProfile = profile; // if more than one SDK pofile is present, the most recent one is the last one in the array
    }
}

- (void) handleUpdatedProfile: (NSNotification *) notification {

    // Get the profile that just got received in this call; it could be an application profile or an SDK profile.
    AWProfile *profile = (AWProfile *) notification.object;

    if (profile.profileType == AWSDKProfile) {
        NSLog(@"In AWSDKBridge -handleUpdatedProfile, got SDK profile");
        self.sdkProfile = profile;

    } else {
        // this is an application profile, which should contain a certificate payload

        // IMPORTANT: If expecting an application profile with a certificate, you can ONLY obtain the certificate values
        // from the notification object. For security reasons the certificate does not get stored locally, like all the
        // other settings in an SDK profile

        SecIdentityRef identityRef = nil;
        NSError *error = nil;

        AWCertificatePayload *certificatePayload = profile.certificatePayload;
        if (certificatePayload) {
            NSString *certificateName = [certificatePayload certificateName];
            NSData *certificateData = [certificatePayload certificateData];
            NSString *certificatePassword = [certificatePayload certificatePassword];

            NSLog(@"In AWSDKBridge -handleUpdatedProfile, got app profile, cert payload data %d bytes", (int)[certificateData length]);


            if ([certificateData length] > 0 && [certificatePassword length] > 0) {

                [AWCertificateUtility importCertToKeychain: certificateData
                                                  withName: certificateName
                                                  password: certificatePassword
                                                  identity: &identityRef
                                                     error: &error];
            }
        }

        if (self.certReceiver)
            [self.certReceiver receivedCertificate: identityRef
                                         withError: error];
    }

}

- (BOOL) application: (UIApplication *) application
             openURL: (NSURL *) url
   sourceApplication: (NSString *) sourceApplication
          annotation: (id) annotation {

    return [self.controller handleOpenURL: url
                          fromApplication: sourceApplication];
}

// Connection information

- (NSString *) groupId {
    if([self.controller account]){
        return [[self.controller account] activationCode];
    }
    else{
        return nil;
    }
}

- (NSString *) username {
    if([self.controller account]){
        return [[self.controller account] username];
    }
    else{
        return nil;
    }
}

- (NSString *) serverName {
    if([[AWServer sharedInstance] deviceServicesURL]){
        return [[[AWServer sharedInstance] deviceServicesURL] host];
    }
    else{
        return nil;
    }
}

// Restrictions payload

- (BOOL) allowCopyPaste {
    if(self.sdkProfile && self.sdkProfile.restrictionsPayload){
        AWRestrictionsPayload *payload = self.sdkProfile.restrictionsPayload;
        return ![payload preventCopyAndCut];
    }
    else{
        return YES;
    }
    
}

- (BOOL) allowOffline {
    if(self.sdkProfile && self.sdkProfile.offlineAccessPayload){
        AWOfflineAccessPayload *payload = self.sdkProfile.offlineAccessPayload;
        return [payload enableOfflineAccess];
    }
    else{
        return NO;
    }
    
}

- (BOOL) restrictDocumentToApps {
    if(self.sdkProfile && self.sdkProfile.restrictionsPayload){
        AWRestrictionsPayload *payload = self.sdkProfile.restrictionsPayload;
        return [payload restrictDocumentToApps];
    }
    else{
        return NO;
    }
    
}

- (NSArray *) allowedApplications {
    if(self.sdkProfile && self.sdkProfile.restrictionsPayload){
        AWRestrictionsPayload *payload = self.sdkProfile.restrictionsPayload;
        return [payload allowedApplications];
    }
    else{
        return @[];
    }
    
}

// Custom settings payload

- (NSString *) customSettings {
    if(self.sdkProfile){
        AWCustomPayload *custom = [self.sdkProfile customPayload];
        return custom.settings;
    }
    else{
        return @"";
    }
    
}

// Uncategorized

- (BOOL) isCompliant {
    // TODO
    return NO;
}

- (BOOL) isCompromised {
    // TODO
    return NO;
}

// Bridge delegate methods

- (void) initSuccess {
    if (self.bridgeDelegate)
        [self.bridgeDelegate initSuccess];
}

- (void) initFailure {
    if (self.bridgeDelegate)
        [self.bridgeDelegate initFailure];
}


- (void) wipe {
    if (self.bridgeDelegate)
        [self.bridgeDelegate wipe];
}

- (void) lock {
    if (self.bridgeDelegate)
        [self.bridgeDelegate lock];
}

- (void) unlock {
    if (self.bridgeDelegate)
        [self.bridgeDelegate unlock];
}

- (void) stopNetworkActivity: (AWNetworkActivityStatus) networkActivityStatus {
    if (self.bridgeDelegate)
        [self.bridgeDelegate stopNetworkActivity: networkActivityStatus];
}

- (void) resumeNetworkActivity {
    if (self.bridgeDelegate)
        [self.bridgeDelegate resumeNetworkActivity];
}

- (NSString *) findAirWatchSDKCallbackScheme {
    NSString *callbackScheme = nil;
    NSArray *urlsArray = (NSArray *) [[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleURLTypes"];
    for (NSDictionary *dict in urlsArray) {
        NSString *schemeName = [dict valueForKey: @"CFBundleURLName"];
        if (schemeName && [schemeName isEqualToString:@"com.airwatch.sdk"]) {
            callbackScheme = [dict valueForKey: @"CFBundleURLSchemes"][0];
            break;
        }
    }
    if (callbackScheme && [callbackScheme length])
        return callbackScheme;
    else
        return DEFAULT_CALLBACK_SCHEME;

}

@end
