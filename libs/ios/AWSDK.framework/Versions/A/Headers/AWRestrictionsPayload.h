
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWRestrictionsPayload.h */

#import "AWMacro.h"
#import "AWProfilePayload.h"

/**
 @brief		Access control payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the access control group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWRestrictionsPayload : AWProfilePayload
{
	
}

/** A boolean indicating if the application can be used while the device is offline. */
@property (nonatomic, readonly) BOOL isOfflineModeAllowed;

/** The amount of time an application can be run while the device is offline. */
@property (nonatomic, readonly) long long maximumAllowedOfflineDuration;

/** The amount of times an application can be used before the device goes online. */
@property (nonatomic, readonly) NSInteger maximumOfflineUses;

/** The actions to be taken when maximum offline login is exceeded */
@property (nonatomic, readonly) NSArray *offlineOverLimitActions;

/** A boolean indicating if MDM enrollment is required. */
@property (nonatomic, readonly) BOOL isMDMEnrollmentRequired;

/** An array of actions to be performed if the device is not enrolled. */
@property (nonatomic, readonly) NSArray *deviceNotEnrolledActions;

/** A boolean indicating if Copy and Cut actions are allowed. */
@property (nonatomic, readonly) BOOL preventCopyAndCut;

/** A boolean indicating whether to only allow open document in allowed list of app */
@property (nonatomic, readonly) BOOL restrictDocumentToApps;

/** A list of Apps that're allowed to open documents */
@property (nonatomic, readonly) NSArray *allowedApplications;

/** A boolean indicating if printing is allowed. */
@property (nonatomic, readonly) BOOL printingEnabled;

/** A boolean indicating if data loss prevention is enabled. */
@property (nonatomic, readonly) BOOL enableDataLossPrevention;

/** A boolean indicating if watermark should be displayed on content that has watermark. */
@property (nonatomic, readonly) BOOL enableWatermark;

/** The string that indicate the watermark overlay on the content. */
@property (nonatomic, readonly) NSString *watermarkOverlay;

@property (nonatomic, readonly) BOOL enableMailComposing;
@property (nonatomic, readonly) BOOL enableLocationReporting;
@property (nonatomic, readonly) BOOL enableDataBackup;
@property (nonatomic, readonly) BOOL enableCameraAccess;

@end