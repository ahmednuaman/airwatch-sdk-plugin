
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWCompliance.h */


#import <Foundation/Foundation.h>
#import "AWCompliancePayload.h"


/** The notification name for when the device is compromised and user access is restricted. */
extern NSString * const AWComplianceUserAccessRestrictedNotification;

/** The notification name for when the device is compromised and application wipe needed. */
extern NSString * const AWComplianceUserApplicationWipeNotification;

/** The notification name for when the device is compromised and application wipe needed. */
extern NSString * const AWComplianceCustomActionNotification;

/** The notification name for when the AWCompliance Settings are updated */
extern NSString * const AWComplianceSettingsUpdated;

/** The notification name for when the device is compromised and a message needs to be displayed. */
extern NSString *const AWComplianceDisplayMessageNotification;

/** The key used to access the AWAction object stored in the userInfo dictionary of Notifications. */
extern NSString *const AWComplianceUserInfoObjectKey;


/**
 @brief		Compliance service to enforce compromised device restrictions.
 @details	A service that is used to monitor device for compromisation. When device is compromised, notifications are posted.
 @version 5.9.3.3
 */
@interface AWCompliance : NSObject {
    
}


/** AWCompliance Intializer.
 
 @brief AWCompliance object made by this function.
 @return A newly initialized AWCompliance.
 */
+ (AWCompliance *)sharedInstance;

/**
 * @brief Starts the AWCompliance service with settings defined in the cached SDK Profile
 *        AWCompliance will automatically up be updated with new profiles as they are received.
 * @return A BOOL indicating if the AWCompliance service was started successfully.
 */
+ (BOOL)startService:(NSError**)outError;

/**
 * @brief Stop monitoring the device for compliance
 * @return A BOOL indicating if the AWCompliance service was stop successfully.
 */
+ (BOOL)stopService:(NSError**)outError;

/** Check Device compromisedStatus
 @brief This method will return the JailBroken Status.
 @return AWJailBrokenStatus \nAWDeviceJailBroken if a Jailbreak is detected.
 \nAWDeviceNotJailBroken if a Jailbreak isn't detected.
 */
#if	TARGET_OS_IPHONE
- (AWJailBrokenStatus)jailBrokenStatus;
#endif
@end