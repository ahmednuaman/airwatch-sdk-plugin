//
//  AWController_RSAAA.h
//  AirWatch
//
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

#import "AWController.h"

@interface AWController ()

typedef NS_ENUM(NSUInteger, AWRSAAADeviceInfoLevel)
{
    AWRSAAABasicData = 0,
    AWRSAAADeviceData = 1,
    AWRSAAAAllDeviceData = 2

};

/*
 * @method      isRSAAAResponse:
 * @abstract    Use this method to determine if response contains information regarding RSA Adaptive Authentication
 * @param       response: HTTP response
 * @return      YES if response contains RSA Adaptive Authentication information
 */

- (BOOL)isRSAAAResponse:(NSHTTPURLResponse*)response;

/*
 * @method      processRSAAAResponse: withCompletionHandler:
 * @abstract    Use this method to start RSA Adaptive Authentication Process
 completionHandler will be called with if
 1. User completes authentication.
 success = true
 error = nil
 
 2. User cancels authentication process.
 success = false
 error.Domain = AWProxyErrorDomain
 error.code = AWSDKRSAAErrorActionCancelled
 
 3. Authentication process already in progress.
 success = false
 error.Domain = AWSDKErrorDomain
 error.code = AWSDKRSAAErrorActionInprogress
 
 4. Answer for authentication challenge is not in proper format.
 success = false
 error.Domain = AWProxyErrorDomain
 error.code = AWSDKRSAAErrorAnswerNotInCorrectFormat
 
 * @param       response: HTTP response containing RSA Adaptive Authentication information.
 
 */


- (void)processRSAAAResponse:(NSHTTPURLResponse*)response withCompletionHandler:(void(^)(BOOL success,NSError *error)) completionHandler;

/*
 * @method      setRSAAADeviceInfoLevel:
 * @abstract    Use this method set data collection level for RSA Adaptive Authentication
 * @param       AWRSAAADeviceInfoLevel
 */


- (void)setRSAAADeviceInfoLevel:(AWRSAAADeviceInfoLevel)deviceInfoLevel;

@end