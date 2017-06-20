
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWDeviceStatusController.h */

#import <Foundation/Foundation.h>
#import "AWMacro.h"

@class AWDeviceStatusConfiguration;

/** 
 @brief		Provides an interface to query device enrollment information from the server. Server information can be set by passing an instance of type `AWDeviceStatusConfiguration`.
 @version 5.9.3.3
 */

@interface AWDeviceStatusController : NSObject
{
    
}

/** @name Configuring a Device Status Controller */
//@{

/** The device status configuration to be used with the device status controller. */
@property (nonatomic, strong) AWDeviceStatusConfiguration *configuration AW_DEPRECATED_ATTRIBUTE;

//@}

/** @name Creating a Device Status Controller */
//@{

/** The designated initializer to 
 AWDeviceStatusController object is manage to get status of device enrollment with Airwatch console. AWDeviceStatusController is configured through AWDeviceStatusConfiguration object. 
 @return An initlialized device status controller.
 @param configuration a container that holds server details to retrieve device information.
 */
- (id)initWithConfiguration:(AWDeviceStatusConfiguration *)configuration AW_DEPRECATED_ATTRIBUTE;

//@}

/** @name Obtaining Device Status */
//@{
/** Queries the AirWatch console to determine if the current device is enrolled.
 
 @param callBackBlock The callback block to be executed when a response is received from the AirWatch console, and also get response of enrollment status in boolean object.
 */
+ (void)queryDeviceEnrollmentStatus:(void(^)(BOOL enrolled, NSError *error))callbackBlock;

//@}

@end