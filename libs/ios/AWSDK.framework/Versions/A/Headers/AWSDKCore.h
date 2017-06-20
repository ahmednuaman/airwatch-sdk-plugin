
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*!
 *  @brief      AirWatch SDK framework umbrella.
 *  @details    A framework header umbrella. Once imported, you can use any feature of the AirWatch SDK.
 *  @version 5.9.3.3
 *  @file       AWSDKCore.h
 */

// Actions that can be performed on the device e.g. restrict access, lock user, wipe device, etc.

#ifndef AirWatch_AWSDKCore_h
#define AirWatch_AWSDKCore_h

#import "AWAction.h"

//======== Common ========
#import "AWSDK.h"
#import "AWCommon.h"
#import "AWMacro.h"
#import "AWSDKErrors.h"

//======== Access Restriction ========
#import "AWRestrictions.h"
#import "AWRestrictionsPayload.h"
#import "AWOfflineAccessPayload.h"
#import "AWNetworkAccessPayload.h"

//======== Analytics ========
#import "AWAnalytics.h"
#import "AWAnalyticsPayload.h"

//======== Authentication ========
#import "AWAuthenticationPayload.h"

//======== Beacon ========
#import "AWBeacon.h"

#if	TARGET_OS_IPHONE
//======== Branding ========
    #import "AWBrandingPayload.h"
    #import "AWBranding.h"
#endif

//======== Security ========
#import "AWCertificatePayload.h"

//======== Compliance =======
#import "AWCompliance.h"
#import "AWCompliancePayload.h"

//======== Command Manager ========
#import "AWCommandManager.h"

//======== Commands ========
#import "AWCommand.h" 

//======== Policies ========
#import "AWIntegratedAuthPayload.h"
#import "AWCustomPayload.h"

//======== Device ========
#import "AWDeviceStatusConfiguration.h"
#import "AWDeviceStatusController.h"

//======== Enrollment ========
#import "AWEnrollmentAccount.h"
#import "AWEnrollmentAccountAuthenticator.h"
#import "AWEnrollmentAuthenticationCredentialsTypes.h"
#import "AWMDMInformationController.h"

//======== Geofencing ========
#import "AWGeofence.h"
#import "AWGeofencePayload.h"
#import "AWLocationModeTypes.h"

//======== Profiles ========
#import "AWProfile.h"
#import "AWProfilePayload.h"

//======== Data Sampler ========
#import "AWDataSampler.h"
#import "AWDataSamplerConfiguration.h"
#import "AWDataSamplerTypes.h"

//======== Logging ========
#import "AWLog.h"
#import "AWLoggingPayload.h"
#import "AWCrashLogReporter.h"

//======== AWServer singleton ========
#import "AWServer.h"
#import "AWSession.h"

//======== Proxy ========
#import "AWProxyErrors.h"

//======== AWController ========
#import "AWController.h"

#endif