
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWProfile.h */

#import <Foundation/Foundation.h>

#import "AWGeofencePayload.h"
#import "AWCertificatePayload.h"
#import "AWAnalyticsPayload.h"
#import "AWRestrictionsPayload.h"
#import "AWCompliancePayload.h"
#import "AWAuthenticationPayload.h"
#if	TARGET_OS_IPHONE
    #import "AWBrandingPayload.h"
#endif
#import "AWLoggingPayload.h"
#import "AWCustomPayload.h"
#import "AWIntegratedAuthPayload.h"
#import "AWOfflineAccessPayload.h"
#import "AWNetworkAccessPayload.h"
#import "AWIntegrationServicesPayload.h"

@class AWProxyPayload;
@class AWSSOPayload;

/**
 @enum AWProfileType			Enumeration that defines the type of profile.
 */
typedef enum AWProfileType {
	AWSDKProfile = 0,
	AWAppProfile
} AWProfileType;

/**
 @brief		Represents an unmanaged configuration profile.
 @details	Profile containing multiple payloads that are used to configure a device and application.
 @version 5.9.3.3
 */
@interface AWProfile : NSObject
{
    
}

/** @name Generic Profile Information */
//@{

/** The description of the profile. */
@property (nonatomic, copy) NSString *comments;

/** The display name of the profile. */
@property (nonatomic, copy) NSString *displayName;

/** The identifier of the profile. */ 
@property (nonatomic, copy) NSString *identifier;

/** The organization of the profile. */
@property (nonatomic, copy) NSString *organization;

/** A boolean value that determines whether the profile can not be removed. */
@property (nonatomic, assign) BOOL removalDisallowed;

/** The command type name of the profile */
@property (nonatomic, copy) NSString *type;

/** The UUID of the profile. */
@property (nonatomic, copy) NSString *uuid;

/** The version of the profile. */
@property (nonatomic, assign) NSInteger version;

/** The profile groups enclosed within the profile. */
@property (nonatomic, readonly) NSSet *payloads;

/** The type of the profile. */
@property (nonatomic, readonly) AWProfileType profileType;

//@}

/** @name SDK Profile Payloads */
//@{

/** 
 The geofence profile group.
 */
@property (nonatomic, readonly) AWGeofencePayload *geofencePayload;

/**
 The analytics payload.
 */
@property (nonatomic, readonly) AWAnalyticsPayload *analyticsPayload;

/**
 The access control profile group.
 */
@property (nonatomic, readonly) AWRestrictionsPayload *restrictionsPayload;

/**
 The compliance profile group.
 */
@property (nonatomic, readonly) AWCompliancePayload *compliancePayload;

/**
 The authentication profile group.
 */
@property (nonatomic, readonly) AWAuthenticationPayload *authenticationPayload;

#if	TARGET_OS_IPHONE
/**
 The branding profile group.
 */
@property (nonatomic, readonly) AWBrandingPayload *brandingPayload;


#endif

/**
 The integrationServices SDK profile group.
 */
@property (nonatomic, readonly) AWIntegrationServicesPayload *integrationServicesPayload;

/**
 The custom SDK profile group.
 */
@property (nonatomic, readonly) AWCustomPayload *customPayload;

/**
 The Logging profile group. 
 */
@property (nonatomic, readonly) AWLoggingPayload *loggingPayload;

//@}

/**
 The SSO profile group.
 */
@property (nonatomic, readonly) AWSSOPayload *ssoPayload;

//@}


/**
 The Integrated Authentication profile group.
 */
@property (nonatomic, readonly) AWIntegratedAuthPayload *integratedAuthPayload;

//@}

/**
 The Offline Access profile group.
 */
@property (nonatomic, readonly) AWOfflineAccessPayload *offlineAccessPayload;

//@}

/**
 The Proxy Settings profile group.
 */
@property (nonatomic, readonly) AWProxyPayload *proxyPayload;

/**
 The Network Access Restrictions profile group.
 */
@property (nonatomic, readonly) AWNetworkAccessPayload *networkAccessPayload;

//@}

/** @name Application Profile Payloads */
//@{

/**
 The certificate payload. 
*/
@property (nonatomic, readonly) AWCertificatePayload *certificatePayload;

//@}



/** @name Creating a Profile */
//@{

/** Returns a configuration profile built from a dictionary.
 
 @param info The dictionary to be used to build the configuraiton profile.
 @return Returns a newly initialized profile object.
*/
- (id)initWithDictionary:(NSDictionary *)info;

//@}

/** @name Accessing Payloads */
//@{
/** Returns True if the profile contains the provided value for PayloadType
 @param type The string value used to determine presence of a PayloadType
 @return Returns a BOOL.
 */
- (BOOL) hasPayloadType:(NSString*)type;

/**
 @param type The string value used to find a payload matching the value for PayloadType.
 @return Returns a NSDictionary representation of the payload matching the value for PayloadType.
 */
- (NSDictionary*) payloadForPayloadType:(NSString*)type;

/**
 @return Returns a Dictionary containing all of the profile information.
 */
- (NSDictionary*) toDictionary;
//@}
@end