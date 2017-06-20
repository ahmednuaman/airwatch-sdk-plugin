
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWEnrollmentAccount.h */

#import <Foundation/Foundation.h>
#import "AWEnrollmentAuthenticationCredentialsTypes.h"

/**
 @brief		Model representing an AirWatch enrollment account.
 @version 5.9.3.3
 */
@interface AWEnrollmentAccount : NSObject {
    
}

/** @name Configuring an Account */
//@{
/** The numeric identifier associated with the account. This will be -1 until 
 the account has been authenticated against AirWatch. Upon authentication, 
 contains a valid user identifier.
 
 Default value of -1. 
 */
@property (nonatomic, assign) NSInteger identifier;

/** The activation code (group identifier) of the account. */
@property (nonatomic, copy) NSString *activationCode;

/** The username of the account. */
@property (nonatomic, copy) NSString *username;

/** The password of the account. */
@property (nonatomic, copy) NSString *password;

/** From 6.4 console, we support one time authorization token interchangable with username/password */
@property (nonatomic, copy) NSString *authorizationToken;

/** The type of the authentication credentails used by the web service. Defaults 
 to AWEnrollmentAuthenticationCredentialsUsernamePassword if not explicitly 
 set. */
@property (nonatomic, assign) AWEnrollmentAuthenticationCredentialsType authenticationCredentialsType;

//@}

// restricting usage on init to use only custom initializers.
- (instancetype)init __attribute__((unavailable("Please use initWithActivationCode: ...")));

/** @name Creating an Account */
//@{

/** Optional helper intializer. 
 
 @brief AWEnrollmentAccount object made by this function. and it is modal class of enrollment account. 
 @param activationCode The activation code (group identifier) of the account.
 @param username The username of the account.
 @param password The password of the account.
 @return A newly initialized enrollment account. 
 */
- (id)initWithActivationCode:(NSString *)activationCode username:(NSString *)username password:(NSString *)password;

/*
 @brief AWEnrollmentAccount object made by this function. and it is modal class of enrollment account.
 @param authorizationToken Token used to authorize a user.
 @return A newly initialized enrollment account.
 @discussion The authorizationToken can be obtained from the Self Service Portal.
 */
- (id)initWithActivationCode:(NSString *)activationCode authorizationToken:(NSString *)authorizationToken;

//@}

/**
 *  Tells us if the the account is authenticated via Identifier, checks the identifier value against default value
 */
- (BOOL)isAccountAuthenticated;

@end