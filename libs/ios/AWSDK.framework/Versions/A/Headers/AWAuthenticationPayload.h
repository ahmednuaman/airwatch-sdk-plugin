/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWAuthenticationPayload.h */

/**
 @enum AWAuthenticationMethod
 Indicates the Authentication Method to be used
 */
typedef enum AWAuthenticationMethod
{
    AWAuthenticationMethodNone = 0,
	AWAuthenticationMethodPasscode = 1,         /**< Use the Passcode Authentication method. */
	AWAuthenticationMethodUsernamePassword = 2  /**< Use the Username and Password Authentication method. */
}
AWAuthenticationMethod;

typedef enum
{
	AWBiometricMethodNone=0,
	AWBiometricMethodTouchID
}AWBiometricMethod;
/**
 @enum AWAuthenticationPasscodeComplexity
 Specfies how complex a passcode should be.
 */
typedef enum AWAuthenticationPasscodeComplexity
{
	AWAuthenticationPasscodeSimpleComplexity = 1,       /**< Use simple passcodes */
	AWAuthenticationPasscodeAlphanumericComplexity = 2  /**< Require Passcodes to contain both letters and numbers */
}
AWAuthenticationPasscodeComplexity;

typedef NS_ENUM(NSInteger, AWPasscodeMode) {
    AWPasscodeModeOff = 0,
    AWPasscodeModeNumeric = 1,
    AWPasscodeModeAlphanumeric = 2
};

#import "AWProfilePayload.h"

/**
 @brief		Authentication payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the authentication group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWAuthenticationPayload : AWProfilePayload
{
	
}

/** The authentication type being used. */
@property (nonatomic, readonly) AWAuthenticationMethod authenticationMethod;

/** 
 The passcode complexity.
 **This only applies to passcodes.**
 */
@property (nonatomic, readonly) AWAuthenticationPasscodeComplexity passcodeComplexity;

/** The minimum length of a passcode. 

 **This only applies to passcodes.**
 */
@property (nonatomic, readonly) NSInteger minimumPasscodeLength;

/** The minimum complex characters a passcode must contain. 

 **This only applies to passcodes.**
 */
@property (nonatomic, readonly) NSInteger minimumComplexCharacters;

/** The maximum amount of days before a passcode expires and a new one must be set. 

 **This only applies to passcodes.**
 */
@property (nonatomic, readonly) NSTimeInterval maximumPasscodeAge;

/** The amount of passcodes that must be unique before reusing one is allowed. 

 **This only applies to passcodes.**
 */
@property (nonatomic, readonly) NSInteger passcodeHistory;

/** Amount of time the application can be unlocked without prompting for the passcode. 

 **This applies to username / password & passcodes.**
 */
@property (nonatomic, readonly) NSTimeInterval gracePeriod;

/** Number of failed authentication attempts allowed before actions should be executed.

 **This applies to username / password & passcode.**
 */
@property (nonatomic, readonly) NSInteger maximumFailedAttempts;

/** The sequence of action taken after max number of failed passcode / password attempts occured
 
 **This applies to username / password & passcode.**
 */
@property (nonatomic, readonly) NSArray *actionsTakenOnMaxFailedAttempt;

/** The idle time (in minute) before application will auto lock
 
 **This is currently being passed down but have no way to manipulate the value from console**
 */
@property (nonatomic, readonly) NSInteger autoLockMinute;

/** Don't know the intention of this one yet
 
 **This is currently being passed down but have no way to manipulate the value from console**
 */
@property (nonatomic, readonly) BOOL allowSamePasscodeAllApp;

/** Determine if device passcode level should be required
 
 **This start being implemented in 6.4 to replace authenticationMethod = 1 (passcode)**
 */
@property (nonatomic, readonly) BOOL requirePasscode;

@property (nonatomic, readonly) BOOL enableSingleSignOn;   /**< A boolean indicating if Single Sign-On is enabled. */

@property (nonatomic, readonly) AWPasscodeMode passcodeMode;
@property (nonatomic, readonly) BOOL allowSimple;
@property (nonatomic, readonly) NSInteger passcodeTimeout;
@property (nonatomic, readonly) NSInteger actionOnMaxFailedAttempts;
@property (nonatomic, readonly) NSString *policyId;

@property (nonatomic, readonly) BOOL isV2;

@property (nonatomic, readonly) BOOL enableIntegratedAuthentication;   /**< A boolean indicating if Integrated Authentication is enabled. */

@property (nonatomic, readonly) NSArray *allowedSites;

/*
 A boolean indicating if NAPPS authentication is enabled
 */
@property (nonatomic, readonly, assign) BOOL enableNapps;

/*
 If NAPPS is enabled, this parameter gives the URL of authentication server
 */
@property (nonatomic, readonly, copy) NSString *authServerURL;

/** To access back the dictionary used to create this payload
 
 **
 */
@property (nonatomic, readonly) NSDictionary *payloadDictionary;

// BioMetric Method
@property (nonatomic, readonly) AWBiometricMethod biometricMethod;



@end