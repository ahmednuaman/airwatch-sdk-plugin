
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWDeviceStatusConfiguration.h */

/**
 @brief		Configuration used to setup a `AWDeviceStatusController`.
 @details	`AWDeviceStatusConfiguration` is a container that holds server details to retrieve device information.
 @version 5.9.3.3
 */
AW_DEPRECATED_ATTRIBUTE_MESSAGE("This will be removed in the 5.9 SDK.")
@interface AWDeviceStatusConfiguration : NSObject
{
    
}

/** The device status service action to perform.
 
 The default is GetDeviceStatus.
 */
@property (nonatomic, copy) NSString *deviceStatusAction;

/** 
 
 The designated intializer to create device management configurations.
 
 @brief AWDeviceStatusController can be configured by getting AWDeviceStatusConfiguration object.
 Creates a device management configuration with the specified parameters.
 
 @return A new device management configuration object.
 @param hostName The host name of the AirWatch console conforming to RFC 1808.
 @param endpointPath The endpoint path of the device info service.
 @param deviceStatusAction The device status service action to perform.
 
 */
- (id)initWithHostName:(NSString *)hostName endpointPath:(NSString *)endpointPath deviceStatusAction:(NSString *)deviceStatusAction;

@end