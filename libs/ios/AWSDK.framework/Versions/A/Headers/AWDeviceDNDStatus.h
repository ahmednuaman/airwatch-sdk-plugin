
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWDeviceDNDStatus.h */


#import <Foundation/Foundation.h>

/**
 @brief		Provides an interface to query/set device DND status from/on the server.
 */

@interface AWDeviceDNDStatus : NSObject


/** @name Fetch Device DND Status */
//@{
/** Queries the AirWatch server to get the current DND status for the device, if DND is enabled.
 
 @param block   The callback block to be executed when a response is received
    from the AirWatch console, and get response of DND status in boolean object and DND enable period in NSDate object.
 */

+ (void)fetchDeviceDNDStatus:(void(^)(BOOL responseStatus, BOOL dndStatus, NSDate *dndTime, NSError *error))block;

//@}



/** @name Set Device DND state */
//@{
/** Set the DND state to TRUE OR FALSE on the AirWatch Server.
 
 @param setDndState     The DND state to be set on the server.
 
 @param callBackBlock   The callback block to be executed when a response is received from
    the AirWatch console, and get response of DND status in boolean object and DND enable period in NSDate object.
 */

+ (void)setDeviceDNDStatus:(BOOL)setDndState completionBlock:(void(^)(BOOL responseStatus, BOOL dndStatus, NSDate *dndTime, NSError *error))block;

//@}


@end