
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWCompliancePayload.h */

#import "AWProfilePayload.h"

/**
 @brief		Compliance payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the compliance group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWCompliancePayload : AWProfilePayload
{
	
}

/** A boolean indicating if compromised (jailbroken) devices should be prevented. */
@property (nonatomic, readonly) BOOL preventCompromisedDevices;

/** A boolean indicating if device restorations should be prevented. */
@property (nonatomic, readonly) BOOL preventRestoringBackupDevices;

/** An array of actions to be performed if the device is compromised. */
@property (nonatomic, readonly) NSArray *preventCompromisedDevicesActions;

/** A boolean indicating if compromised (jailbroken) devices should be prevented. */
@property (nonatomic, readonly) BOOL enableCompromisedProtection;

/** A string for the id of the compromised policy. */
@property (nonatomic, readonly) NSString *compromisedPolicyID;

@end
	