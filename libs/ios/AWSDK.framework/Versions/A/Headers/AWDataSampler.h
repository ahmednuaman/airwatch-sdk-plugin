
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWDataSampler.h */

#import <Foundation/Foundation.h>
#import "AWMacro.h"

/**
 @enum  An enum holding the possible DataSampler transmission types
 */

typedef enum
{
	kTransmitterUnknown = 0,	/**< Transmit method unknown. */
	kTransmitterHttp,		/**< Transmit Interrogator samples through HTTP */
	kTransmitterTcp,		/**< Transmit Interrogator samples through TCP */
}
AWDataSamplerTransmitterType;

@class AWDataSamplerConfiguration;

/**
 @brief		AWDataSampler is utility kind of interface, by using this user can send dynamic data of device, like system info, analytics info, GPS info, callLog info, usage info, usageData info etc.
 @details	AWDataSampler declares the programmatic interface for an object that manages the SDK‚Äôs DataSampler module. AWDataSampler declares methods for starting and stopping the AWDataSampler service on a device. Settings for the DataSampler is passed through a configuration object of type AWDataSamplerConfiguration. Using the configuration object, the user can stop and start various DataSampler modules. To set up DataSampler module, user has to initialize the DataSampler module instance with a configuration object and then start the module by calling the method startUp:outError on DataSampler module instance. Calling shutDown:outError on the DataSampler module instance will stop sampling and transmission.
 @version 5.9.3.3
 */
@interface AWDataSampler : NSObject
{
	BOOL g_AWDataSamplerIsInitialized;
	BOOL g_AWDataSamplerIsStarted;
	AWDataSamplerTransmitterType _transmitType;
	BOOL sendGPSImmediate;
}

/** Property to indicate whether or not the DataSampler is initialized with an DataSamplerConfig. **/
@property (nonatomic, assign) BOOL g_AWDataSamplerIsInitialized;

/** Property to indicate whether or not the DataSampler is currently started and transmitting. **/
@property (nonatomic) BOOL g_AWDataSamplerIsStarted;

/** Property to indicate whether DataSampler should transmit GPS updates imediately. **/
@property (nonatomic) BOOL sendGPSImmediate;

/** Property to indicate whether DataSampler should transmit imediately during startup. **/
@property (nonatomic,assign) BOOL transmitAtStartUp;

///-------------------------------------
/// @name DataSampler Module Management
///-------------------------------------

/**  Gets the instance of the DataSampler module so that multiple instances cannot be started.
 
 Method should be called when other classes need to access the DataSampler instance.
 
 @return a pointer to the AWDataSampler object.
 */
+ (AWDataSampler*)mDataSamplerModule;

/** Configures the DataSampler module for use.
 @param config An AWDataSamplerConfiguration that defines the proper DataSampler settings.
 */
- (void)setConfig:(AWDataSamplerConfiguration *)config;

/** Starts up the DataSampler module and begins the timer on the configured modules.
 
 Method should be called when the host application is ready to start transmitting DataSampler data.
 
 @return A BOOL value indicating method success.
 @param outError Out parameter used if an error occurs while starting the DataSampler module.  May be NULL.
 */
- (BOOL)startUp:(NSError **)outError;

/** Closes all network connections, stops all DataSampler transmissions. The DataSampler can be restarted, given it has a valid configuration.
 
 Method should be called when the host application no longer needs the capabilities of the DataSampler module.
 
 @return A BOOL value indicating method success.
 @param modules An array of module objects to be started. These modules should be initialized with a timer value.
 @param outError Out parameter used if an error occurs while shutting down the DataSampler module.  May be NULL.
 */
- (BOOL)shutDown:(NSError **)outError;

/** Forces a transmit of all DataSampler data on the device.
 
 Method should be called only when there is a critical need to get DataSampler data to the console.
 
 @return A BOOL value indicating method success.
 @param outError Out parameter used if an error occurs while transmitting. May be NULL.
 @param delegate The id of the object to call delegate methods on. This needs to implement <AWDataSamplerTransmitterDelegate>.
 */
- (BOOL)Transmit:(NSError **)outError delegate:(id)delegate;

-(BOOL)Transmit:(NSError **)outError withCompletionHandler:(void(^)(NSError *err)) acompletionHanlder;

/** Forces a sample of all DataSampler data on the device.
 
 Method should be called only when there is a critical need to get DataSampler data to the console, and used in conjunction with Transmit.
 */

- (void)SampleModules;


/** Forces to transmit cellular DataSampler data on the device.
 */
- (BOOL)TransmitCellular:(NSError **)outError withCompletionHandler:(void (^)(NSError *))acompletionHanlder;

@end