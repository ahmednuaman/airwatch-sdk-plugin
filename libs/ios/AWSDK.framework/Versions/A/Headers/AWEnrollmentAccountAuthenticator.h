
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWEnrollmentAccountAuthenticator.h */ 

#import <Foundation/Foundation.h>
#import "AWEnrollmentAuthenticationCredentialsTypes.h"

@class AWEnrollmentAccount;

/**
 * An enum holding the possible authentication failure reasons.
 */

typedef enum
{    
    AWEnrollmentAuthenticationUserDeviceMismatch    = -5,	///< The authenticated user was not used to enroll the target device. 
    AWEnrollmentAuthenticationNotEnrolled           = -4,	///< The device is not enrolled.
    AWEnrollmentAuthenticationDeviceNotFound        = -3,	///< The device has not checked in to the console.
    AWEnrollmentAuthenticationInternalServerError   = -2,	///< An internal server error occurred.
    AWEnrollmentAuthenticationInvalidCredentials    = -1,	///< Invalid credentials were supplied.
    AWEnrollmentAuthenticationInvalidActivationCode = 0		///< An invalid activation code was supplied.    
}
AWEnrollmentAuthenticationResult; ///< Enumeration describing the cause of failure.

typedef NS_ENUM(NSInteger, AWAuthenticationEndPointStatusCode)
{
    AWAuthenticationEndPointStatusSuccess                 = 1000,    // credentials are successfully validated (success, all other are failures)
    AWAuthenticationEndPointStatusInvalidCredentials            ,    // invalid credentials were supplied.
    AWAuthenticationEndPointStatusAccountLockedOut              ,    // account has been locked out
    AWAuthenticationEndPointStatusInactiveAccount               ,    // account not activated yet
    AWAuthenticationEndPointStatusMDMEnrollmentRequired         ,    // Credentails are validated but MDM enrollment is required.
    AWAuthenticationEndPointStatusInvalidToken                  ,    // Invalid Token was supplied
    AWAuthenticationEndPointStatusDeviceNotFound                ,    // Device not found
    AWAuthenticationEndPointStatusConfigurationError            ,    // TODO: Configuration Error
    AWAuthenticationEndPointStatusUnknownError                       // Unknow error occured
    
}; //Enumeration describing the cause of failure.

/**
 * Call back block given authentication status of account after authentication attempt
 */

typedef void(^AWEnrollmentAuthenticatorCompletionStatusBlock)(BOOL authenticated, AWEnrollmentAccount *account, NSError *error);

/** 
 The AWEnrollmentAccountAuthenticator provides an interface to authenticate an enrollment account at a specified server location. The details of server is passed to the AWEnrollmentAccountAuthenticator through an AWServer object.
 @brief AWEnrollmentAccountAuthenticator manage to check authenticate AWEnrollmentAccount object.
 
 */

/**
 @brief		Enrollment account authenticator.
 @details	Controller used to authenticate an enrollment account against AirWatch.
 @version 5.9.3.3
 */
@interface AWEnrollmentAccountAuthenticator : NSObject
{
    
}

/** @name Authenticating an Account */
//@{

/** Authenticates an AirWatch enrollment account.
 
 @param account The account to be authenticated.
 @param block A callback block used to retrieve the status of the authentication. Boolean object indicate whether the AWEnrollmentAccount is authenticated or not, and error will be get if any error occur regarding authentication.
 */
- (void)authenticateAccount:(AWEnrollmentAccount *)account callBackBlock:(AWEnrollmentAuthenticatorCompletionStatusBlock)block;

//@}

+ (AWEnrollmentAccountAuthenticator*)authenticatorForGroup:(NSString*)group;
@end