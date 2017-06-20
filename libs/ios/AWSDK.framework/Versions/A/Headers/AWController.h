//
//  AWController.h
//  AirWatch
//
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

/*! \file AWController.h */

#import <Foundation/Foundation.h>

#import "AWCommon.h"
#import "AWNetworkActivityStatus.h"

typedef void(^AWControllerSoftLockCompletionHandler)(BOOL finished, NSError *error);

@class AWEnrollmentAccount;

@protocol AWSDKDelegate <NSObject>

/*
 * @abstract    AWSDKDelegate initialization lifecycle notifications to inform your app of success or failure
 in SDK initialization and profile retrieval.
 */
- (void)initialCheckDoneWithError:(NSError*) error;
- (void)receivedProfiles:(NSArray*)profiles;

/*
 * @abstract    AWSDKDelegate Action Notifications used to inform your app to take various action
 * @discussion  stopNetworkActivity and resumeNetworkActivity are not supported on iOS 9
 */
- (void)wipe;
- (void)lock;
- (void)unlock;

/**
 * @method      stopNetworkActivity:
 * @abstract    Called when a problem occurs with the network status.
 * @discussion  For this method to be called, Network Access Control must be set to true within Console.
 *              If airplane mode is switched on, SSID does not match what is on console, proxy failed, etc.
 *              this method will be called. This method may be called if when the app is resumed there is something wrong
 *              with the states defined in AWNetworkActivityStatus.
 * @param       networkActivityStatus: Most common values are AWNetworkActivityNormal, AWNetworkActivityBadSSID, AWNetworkActivityNetworkNotReachable
 */
- (void)stopNetworkActivity:(AWNetworkActivityStatus)networkActivityStatus;

/**
 * @method      resumeNetworkActivity
 * @abstract    Called when there is no longer a problem with the network status.
 * @discussion  For this method to be called, Network Access Control must be set to true within Console.
 *              If network activity becomes valid, this method should be called when the application gets resumed and if
 *              the application is launched. Reasons for a valid state is if the previous state of the app now has a good
 *              SSID in the profile, device is no longer on airplane mode, etc.
 */
- (void)resumeNetworkActivity;

@end

extern NSString *const AWCertificatePinningErrorNotification;

@interface AWController : NSObject

@property (nonatomic,unsafe_unretained) id<AWSDKDelegate> delegate;
@property (nonatomic,readonly) AWSSOStatus ssoStatus;
@property (nonatomic,strong) NSString *callbackScheme;

+ (AWController*)clientInstance;

/*
 * @method      start
 * @abstract    Use this method to start the SDK process
 * @discussion  Before calling this method, ensure the callbackScheme and delegate are set. Once this method is called,
 *              the SDK will initialize and attempt to retrieve SDK configurations from your AirWatch management server.
 *              The management server URL is retrieved automatically through several possible paths depending on your setup.
 *              Once the URL is retrieved, the SDK profile will be retrieved and the configuration will be setup. Once the
 *              setup is finished, initialCheckDoneWithError in AWSDKDelegate will be called. Subsequent start calls will be
 *              ignored until the app is terminated.
 */
- (void)start;

/*
 * @method      profiles
 * @abstract    Use this method to view the stored SDK profile
 * @return      NSArray containing AWProfile object(s)
 */
- (NSArray*)profiles;

/*
 * @method      sync
 * @abstract    Use this method to force the SDK to go through the start process again
 */
- (void)sync;

/*
 * @method      account
 * @abstract    Use this method to access the user's enrollment credentials
 * @discussion  The credentials will be nil for devices where single factor token or SAML enrollment is used
 * @return      AWEnrollmentAccount object which contains the enrolled user's credentials
 */
- (AWEnrollmentAccount*)account;

/*
 * @method      setAPNSToken:token
 * @abstract    Use this method to send your APNS token to AirWatch in order to receive push notifications from AirWatch
 * @param       token: the APNS token received from Apple
 */
- (void)setAPNSToken:(NSData*)token;

/*
 * @method      handleOpenURL:fromApplication
 * @abstract    Place this inside your app's application:openURL:sourceApplication:annotation method to handle app-to-app communication
 * @return      returns YES if the url is understood by the SDK, returns NO otherwise
 */
- (BOOL)handleOpenURL:(NSURL*)url fromApplication:(NSString*) sourceApplication;

/*
 * @method      handleChallenge
 * @abstract    Handles NSURLConnection authenticaton challenges using SDK credentials
 * @discussion  Credentials depend on SDK profile configuration and enrollment mechanism
 * @param       challenge: Authentication challenge to be handled
 * @return      YES if challenge is handled successfully otherwise NO
 */
-(BOOL)handleChallenge:(NSURLAuthenticationChallenge*)challenge;

/*
 * @method      handleChallengeForURLSessionChallenge:completionHandler
 * @abstract    Handles NSURLSession authenticaton challenges using SDK credentials
 * @discussion  Credentials depend on SDK profile configuration and enrollment mechanism
 * @param       challenge: Authentication challenge to be handled
 * @param       completionHandler: completion handler for NSURLSession call
 * @return      YES if challenge is handled successfully otherwise NO
 */
-(BOOL)handleChallengeForURLSessionChallenge:(NSURLAuthenticationChallenge *)challenge
                           completionHandler:(void (^)(NSURLSessionAuthChallengeDisposition disposition,
                                                       NSURLCredential *credential))completionHandler;
/*
 * @method      canHandleProtectionSpace:withError
 * @abstract    Use this method to determine if the SDK has the credentials for handling the challenge type
 * @param       protectionSpace: protectionSpace for the authentication challenge received
 * @param       error: the error object which contains the relevant error code in case protection space
 * @return      YES if challenge can be handled, NO otherwise
 */
-(BOOL)canHandleProtectionSpace:(NSURLProtectionSpace*)protectionSpace withError:(NSError**)error;

/*
 *  Use this method to get/update user credentials i.e AD password change

 * @method      updateUserCredentialsWithCompletion:completionHandler
 * @abstract    Use this method to get/update user credentials stored in the SDK (i.e AD password change on the backend)
 * @discussion  If SSO is enabled in the SDK profile, then the app will invoke the anchor application (Agent or Container)
 *              in order to update the credentials. This will require Agent v5.1 or Container 2.1.
 *              If SSO is disabled, then the authentication update prompt will take place within the SDK application.
 * @param       completionHandler: block which contains the status of the attempted credentials update.
 */
- (void)updateUserCredentialsWithCompletion:(void(^)(BOOL success,NSError *error))completionHandler;

/*
 
 * @method      fetchNewCertificatesWithError:error
 * @abstract    Use this method to force the SDK to retrieve a new certificate
 * @param       error: If the retrieval was successful, then nil will be returned.
 * @return      whether the operation is successfull or not
 */

-(BOOL)fetchNewCertificatesWithError:(NSError**)error;

/*
 * @method      removeLockAnimated:withCompletionBlock
 * @abstract    Use this methods to temporarily delay the SDK authentication lock UI
 * @discussion  Every removeLockAnimated call must eventually be balanced with a resumeLock call. if there is no resumeLock call to balance
 this method, then the lock delay will be present until the application is terminated.
 * @param       animated: Specifies if the dismissing of the lock UI should be animated
 * @param       completionHandler: block which informs the app the lock delay has been removed
 */
-(void) removeLockAnimated:(BOOL) animated withCompletionBlock:(AWControllerSoftLockCompletionHandler) completionHandler;

/*
 * @method      resumeLock
 * @abstract    Use this method in conjunction with removeLockAnimated:withCompletionBlock in order to remove the lock delay.
 */
-(void) resumeLock;

/*
 * @method      AWSDKVersion
 * @abstract    Use this methods to get current AWSDK version number/
 * @return      The current AWSDK verion number as a NSString.
 */
-(NSString*)AWSDKVersion;
@end

