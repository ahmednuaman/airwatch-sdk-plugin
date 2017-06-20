
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWEnrollmentAuthenticationCredentialsTypes.h */

#import <Foundation/Foundation.h>

// TODO: This enum should be a bitmask
/** The possible types of authentication credentials. */
typedef enum
{    
	AWEnrollmentAuthenticationCredentialsNone = 0,			/**< No credentials */
	AWEnrollmentAuthenticationCredentialsPin,			/**< PIN only credentials. */
	AWEnrollmentAuthenticationCredentialsUsernamePassword,		/**< Username and password credentials. */
	AWEnrollmentAuthenticationCredentialsCertificate,		/**< Certificate based credentials. */
	AWEnrollmentAuthenticationCredentialsCertificateWithPin,		/**< Credentials with both a certicate and PIN. */
	AWEnrollmentAuthenticationCredentialsAuthorizationToken,		/**< Credentials with one time authorization token from SSP*/
    AWEnrollmentAuthenticationCredentialsSSO
}
AWEnrollmentAuthenticationCredentialsType;

/** The default authentication credential type. */
extern AWEnrollmentAuthenticationCredentialsType const AWDefaultAuthenticationCredentialsType;
extern AWEnrollmentAuthenticationCredentialsType const AWTokenAuthenticationCredentialsType;

/**
 @brief		Constants for authentication.
 @details	Defines numerous constants used for authenticating a user.
 @version 5.9.3.3
 */
@interface AWEnrollmentAuthenticationCredentialsTypes : NSObject

@end