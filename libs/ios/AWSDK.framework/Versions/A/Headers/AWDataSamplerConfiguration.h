
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWInterrogatorConfiguration.h */

#import <Foundation/Foundation.h>
#import "AWCommon.h"
#import "AWDataSamplerTypes.h"
#import "AWMacro.h"

#define DEFAULT_TRANSMIT_INTERVAL_VALUE_IN_SECONDS 7200
#define DEFAULT_HTTP_SCHEME  @"http"

/**
 @brief AWDataSamplerConfiguration is the property container for configurable DataSampler settings.
 User can specify the sampling modules to be started, destination server, sampling intervals , transmission intervals.
 @version 5.9.3.3
 */
@interface AWDataSamplerConfiguration : NSObject
{
	AWDataSamplerModuleBitmask sampleModules;
	NSTimeInterval defaultSampleInterval;
	NSTimeInterval transmitInterval;
	enum AWTraceLevel traceLevel;
	NSString* urlScheme;
}

/** @name Configuration an DataSampler Configuration */
//@{

/** A bitmask whose flags specify which modules to use. See `Sample Modules` for bitmask constants. */
@property (nonatomic, assign) AWDataSamplerModuleBitmask sampleModules;

/** The time (in seconds) between DataSampler samples. */
@property (nonatomic, assign) NSTimeInterval defaultSampleInterval;

/** The time (in seconds) between DataSampler transmissions. */
@property (nonatomic, assign) NSTimeInterval transmitInterval;

/** The error and information logging level the DataSampler module is run at. */
@property enum AWTraceLevel traceLevel;

/** The URL scheme to be used for http DataSampler transmitter. */
@property (nonatomic, strong) NSString *urlScheme;

//@}

/** @name Creating a DataSampler Configuration */
//@{

/**
 @return Returns an AWDataSamplerConfiguration initialized with the specified values.
 
 @param sampleModules A bitmask whose flags specify which modules to use. See `Sample Modules` for bitmask constants.
 @param defaultSampleInterval The time in seconds between DataSampler samples for all modules by default.
 @param defaultTransmitInterval The time in seconds between DataSampler transmissions for all modules by default.
 @param theTraceLevel The error and information logging level the DataSampler module is run at.
 */
- (id)initWithSampleModules:(AWDataSamplerModuleBitmask)module
      defaultSampleInterval:(NSTimeInterval)sampleInterval
    defaultTransmitInterval:(NSTimeInterval)theTransmitInterval
                 traceLevel:(enum AWTraceLevel)theTraceLevel;

//@}

@end