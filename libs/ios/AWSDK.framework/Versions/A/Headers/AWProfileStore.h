/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWProfileStore.h */


#import <Foundation/Foundation.h>
#import "AWProfile.h"

extern NSString *const kAWStoredSDKProfileInfoKey;
extern NSString *const kAWStoredAppProfileInfoKey;


@interface AWProfileStore:NSObject

/**
 Stores the AWProfile object in local storage.
 @return BOOL indicating whether the profile was stored successfully
*/
- (BOOL)storeProfile:(AWProfile*)profile;

/**
 Provides an array of all AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allProfiles;

/**
 Provides an array of all SDK AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allSDKProfiles;

/**
 Provides an array of all App AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allAppProfiles;

/**
 Provides an array of all AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allProfileDictionaries;

/**
 Provides an array of all SDK AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allSDKProfileDictionaries;

/**
 Provides an array of all App AWProfiles currently stored on the device.
 @return NSArray of AWProfile objects.
 */
- (NSArray*)allAppProfileDictionaries;

@end