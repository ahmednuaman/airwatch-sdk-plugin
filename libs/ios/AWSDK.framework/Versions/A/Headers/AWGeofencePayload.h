
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWGeofencePayload.h */

#import "AWProfilePayload.h"
#import <CoreLocation/CoreLocation.h>
#import "AWMacro.h"

@interface AWGeofenceArea : NSObject

@property (nonatomic, readonly) CLLocationCoordinate2D center;
@property (nonatomic, readonly) CLLocationDistance radius;
@property (nonatomic, readonly) NSString *uniqueID;
@property (nonatomic, readonly) NSString *name;

- (id)initWithInfo:(NSDictionary *)info;

@end

/**
 @brief		Geofence payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the geofence group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWGeofencePayload : AWProfilePayload
{
	
}

/** A boolean indicating if geofencing should be enabled. */
@property (nonatomic, readonly) BOOL isEnabled;

@property (nonatomic, readonly) NSArray *geofenceAreas;

@end