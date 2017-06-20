/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWSession.h */

#import <Foundation/Foundation.h>
#import "AWMacro.h"

typedef enum {
    AWAuthenticationTypeToken = 1,
    AWAuthenticationTypeHMAC = 2
}AWAuthenticationType;

@protocol AWSessionDelegate;

@class AWEnrollmentAccount;

extern NSString *const AWSessionTokenUnsupported;
extern NSString *const AWSessionHeaderToken;

/**
 * @brief   AWSession manages the session of enrollmented account with endpoint.
 * @details	Represents a unique temporary, session used to authenticate against AirWatch API
            endpoints.
 * @version 5.9.3.3
 */
@interface AWSession:NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate,
NSXMLParserDelegate>
{
}

/*!
    @param account The AWEnrollmentAccount used to obtain a session token.
    @return Returns an instance of AWSession
 */
- (id)initWithAccount:(AWEnrollmentAccount *)account;

/*!
    Request a token for the receiver. This token will be used for subsequent requests to the 
    AirWatch Console.
    @return YES if the connection was created, NO if the connection was not created.
    @discussion The return value does not indicate a token was received. You must implement the
                @link AWSessionDelegate @\link protocol.
 */
- (BOOL)requestToken;

/*!
    Request that the receiver's token be invalidated. This will a prevent any subsequent
    requests to the AirWatch Console using the invalidated token.
    @return YES if the connection was created, NO if the connection was not created.
    @discussion The return value does not indicate a token was invalidated. You must implement
                the @link AWSessionDelegate @\link protocol.
 */
- (BOOL)invalidateToken;

/*!
    Returning a Boolean value that indicates whether the receiver's token is valid.
    @return YES if the token is valid otherwise NO if the token is not valid.
 */
- (BOOL)tokenIsValid;

/*!
    The token of the receiver.
    @property
    @discussion If a request for a token has not been made, or the token has been invalidated token
                will be nil.
 */
@property (nonatomic, copy) NSString *token;

/*!
    The delegate of the receiver.
    @property
    @discussion The AWSessionDelegate will be notified when a token is received or invalidated, and
                if an error occured while requesting a token or invalidating a token.
 */
@property (nonatomic, unsafe_unretained) id<AWSessionDelegate> delegate;

/*!
    Boolean value indicating if  the receiver is requesting a token.
    @property
 */
@property (nonatomic, readonly) BOOL isRequestingToken;

/*!
    Boolean value indicating if the receiver is invalidating a token
    @property
 */
@property (nonatomic, readonly) BOOL isInvalidatingToken;

/*!
    The enrollmenteAccount object that the receiver uses to get a session token.
    @property
 */
@property (nonatomic, strong) AWEnrollmentAccount *account;

/*!
    The AWAuthenticationType that the receiver will use.
    @property
 */
@property (nonatomic, assign) AWAuthenticationType authenticationType;

/*!
    NSString representing the authenticationGroup, which is simply the BundleIdentifier.
    @property
 */
@property (nonatomic, strong) NSString *authenticationGroup;

/*!
    NSString representing the temperory token, used for retriving HMAC token post
    successful enrollment through native enrollment process
 */
@property (nonatomic, strong) NSString *authorizationCode;

@end


/*!
    The AWSessionDelegate will be notified when a token is received or invalidated, and
    if an error occured while requesting a token or invalidating a token.
    @protocol
 */
@protocol AWSessionDelegate <NSObject>

@required
/*!
    This method notifies the receiver when the AWSession object receives a token.
 */
- (void)AWSession:(AWSession *)session didRecieveToken:(NSString *)token;

/*!
    This method notifies the receiver when the AWSession failed to connect.
 */
- (void)AWSession:(AWSession *)session didFailWithError:(NSError *)error;

/*!
    This method notifies the receiver when the AWSession invalidated the token successfully.
 */
- (void)AWSessionDidInvalidate:(AWSession *)session;

/*!
    This method notifies the receiver when the AWSession failed to invalidate the token.
 */
- (void)AWSession:(AWSession *)session failedToInvalidateTokenWithError:(NSError *)error;
@end