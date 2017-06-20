/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

//
//  AWSDKAppProfileRetriever.h
//  AirWatch
//
//  Created by Airwatch on 10/16/13.
//

/*! \file AWSDKAppProfileRetriever*/

#import <Foundation/Foundation.h>
#import "AWProfile.h"

typedef void (^profileFetchCompletionHandler)(AWProfile *profile,NSError *error);

@interface AWSDKAppProfileRetriever : NSObject

@property(nonatomic,strong) NSString* appUrlScheme;

/*! Callback that gets called when SDK Profile exists for the device
 @param profileFetchCompletionHandler - The completion block has two parameters AWProfie  and NSError error
 @discussion: The completion block is called when the profile exists for the device and the device is enrolled. Otherwise error is set and completionblock is called.
 
 */

@property(nonatomic,copy) profileFetchCompletionHandler profilefetchHandler;


/*! used to fetch SDK Profile of device which is enrolled.
 @discussion : Checks for the device enrollment and calls the profileFetchCompletionHandler to return the status of the fetch operation.
 */
-(void)fetchProfiles;

@end