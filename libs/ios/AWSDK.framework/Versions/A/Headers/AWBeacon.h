//
//  AWBeacon.m
//  AirWatch
//
//  Created by John Tran on 1/11/13.
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//
/*! \file AWBeacon.h */

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "AWLocationModeTypes.h"
#import "AWMacro.h"

// NSString keys for AWBeacon Notifications
extern NSString *const AWBeaconDidFailToSendNotification;
extern NSString *const AWBeaconDidSendNotification;
extern NSString *const AWBeaconErrorUserInfoKey;

/**
 @brief		The Beacon service is used to send a heartbeat message to AirWatch.
 @details	AWBeacon represent an AirWatch beacon object. Beacon represent static kind of device data like IP Address,MAC Address etc. AWBeacon manage Beacon operation. By using AWBeacon we can start communicating to server and send Beacon to server.
 @version 5.9.3.3
 */
@interface AWBeacon : NSObject

/**
 NSString object which represent APNS (Apple Push Notification Server) Token.
 */
@property (nonatomic, copy) NSString *APNSToken;

/**
 NSString object which represent bundleIdentifier.
 */
@property (nonatomic, copy) NSString *bundleIdentifier;

/**
 Optional NSString object which contains user emailAddress.
 */
@property (nonatomic, copy) NSString *emailAddress;

/**
 Optional NSString object which contains location groupCode.
 */
@property (nonatomic, copy) NSString *groupCode;

/**
 Optional NSString object which contains user phoneNumber.
 */
@property (nonatomic, copy) NSString *phoneNumber;

/**
 transmitInterval specifies the time Interval in seconds for sending Beacon to server, Means after every specified transmitInterval device send Beacon to server.
 */
@property (nonatomic, assign) NSTimeInterval transmitInterval;

/**
 locationMode is enum object specifies  communication is kicked start or not.
 */
@property (nonatomic, assign) AWLocationMode locationMode;

/**
 The distance in meters for the distance between traveling points, means after specified distance change, device will send Beacon to server.
 */
@property (nonatomic, assign) CLLocationDistance locationDistanceFilter;

/**
 Specifies the distance in meter for location accuracy.
 */
@property (nonatomic, assign) CLLocationAccuracy locationDesiredAccuracy;

/** @name Beacon Initialization */
//@{

/** 
 This method will initialize the Beacon with basic values to begin with. All other values can be manually set.
 
 @param token This is a required APNS (Apple Push Notification Service) token that will be used for communication between the app and the server.
 @param interval This is a required time interval (in seconds) that specify how often a beacon should be send to the server
 @param locationGroup An optional value that can be used to send user's location group to the server
 @param locationMode An optional value, if enabled, will allow the beacon to be sent to the server even when the app is in background.
 @param distanceFilter Ano optional value to specify how often to update the user's location. For best result, the distance should not be less then 25 meters. The default value is 50 meters.
 */
- (id)initWithAPNSToken:(NSString *)token
       transmitInterval:(NSTimeInterval)interval
          locationGroup:(NSString *)lg
           locationMode:(AWLocationMode)locationModeIn
               distance:(CLLocationDistance)distanceFilter;

/**
 Start the beacon and set it ready to send information.
 */
- (void)start;

/**
 Stop the beacon
 */
- (void)stop;

/**
 Send the beacon to the server
 */
- (void)send;

/**
 A class method to allow the app to access the time that the last successful beacon was sent
 */
+ (NSDate *)lastSuccessfulBeaconTimeStamp;

@end