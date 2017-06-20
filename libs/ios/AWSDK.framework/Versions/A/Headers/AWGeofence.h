
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWGeofence.h */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "AWGeofencePayload.h"

/** The notification posted when AWGeofence settings have been updated */
extern NSString *const AWGeofenceSettingsUpdated;


/**
 @brief		Describes a geofence to be used with `AWGeofenceService`.
 @details	A model that is used to represent a geofence.
 @version 5.9.3.3
 */
AW_DEPRECATED_ATTRIBUTE_MESSAGE("This will be removed in the 5.9 SDK.")
@interface AWGeofence : NSObject
{

}

/** The name of the geofence. */
@property (nonatomic, copy) NSString *name;

/** The center point of the geofence. */
@property (nonatomic, assign) CLLocationCoordinate2D centerCoordinate;

/** The distance (in meters) from the fence's centerpoint to the inner boundary. */
@property (nonatomic, assign) CLLocationDistance innerRadius;

/** The distance (in meters) from the fence's centerpoint to the middle boundary. */
@property (nonatomic, assign) CLLocationDistance middleRadius;

/** The distance (in meters) from the fence's centerpoint to the outer boundary. */
@property (nonatomic, assign) CLLocationDistance outerRadius;

/** Actions to be performed once the device enters the inner fence. */
@property (nonatomic, strong) NSArray *innerFenceEnterActions;

/** Actions to be performed once the device exits the inner fence. */
@property (nonatomic, strong) NSArray *innerFenceExitActions;

/** Actions to be performed once the device enters the middle fence. */
@property (nonatomic, strong) NSArray *middleFenceEnterActions;

/** Actions to be performed once the device exits the middle fence. */
@property (nonatomic, strong) NSArray *middleFenceExitActions;

/** Actions to be performed once the device enters the outer fence. */
@property (nonatomic, strong) NSArray *outerFenceEnterActions;

/** Actions to be performed once the device exits the outer fence. */
@property (nonatomic, strong) NSArray *outerFenceExitActions;

/**
 Helper initializer to create and configure a geo-fence according to a profile payload.
 
 @param payload Geo-fence payload containg properties to be applied.
 @return Newly intialized and configured geo-fence.
 */
- (id)initWithGeofencePayload:(AWGeofencePayload *)payload;

/**
 @return A `CLLocation` object representing the geofence's center. 
 */
- (CLLocation *)centerLocation;

@end