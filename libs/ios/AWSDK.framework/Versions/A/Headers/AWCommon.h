
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*!
 *  @brief     Shared header with constants.
 *  @details   A common header file for used by all classes that needed to use the below constants.
 *  @version 5.9.3.3
 *  @file      AWCommon.h
 */

/** @name sending notifications */
//@{


#ifndef AWSDK_AWCommon_h
#define AWSDK_AWCommon_h


#define NOTIF_AWBeaconSendComplete		@"AWBeaconSendComplete"		/**< beacon send  completion notification */
#define NOTIF_AWInterrogatorSendComplete        @"AWInterrogatorSendComplete"	/**< interrogator send  completion notification */
#define NOTIF_AWLogSendComplete			@"AWLogSendComplete"		/**< log send  completion notification */
//@}

/** @name AWLog keys */
//@{
#define AWLogSendHTTPStatusKey			@"AWLogSendHTTPStatusKey"		/**< Http status key sended by log */
#define AWLogSendNSErrorKey			@"AWLogSendNSErrorKey"			/**< NSError key sended by log  */
#define AWLogSendIsHTTPStatusValidKey		@"AWLogSendIsHTTPStatusValidKey"	/**< Is Http Status valid key sended by log  */
#define AWLogSendConnectionNameKey		@"AWLogSendConnectionNameKey"		/**< Is Http Status valid key sended by log  */
//@}

/** @name Beacon keys */
//@{
#define AWBeaconSendHTTPStatusKey		@"AWBeaconSendHTTPStatusKey"	/**< Http status key sended by beacon */
#define AWBeaconSendNSErrorKey			@"AWBeaconSendNSErrorKey"	/**< NSError key sended by beacon */
#define AWBeaconConsoleStatusKey		@"AWBeaconConsoleStatusKey"	/**< console status key sended by beacon */
#define AWBeaconConsoleMessagesKey		@"AWBeaconConsoleMessagesKey"	/**< console messages key sended by beacon */
#define AWBeaconSuccessfulTimeStamp             @"AWBeaconSuccessfulTimeStamp"	/**< Key to save Beacon TimeStamp when it is successfull. */
#define NumberOfDaysForJailbrokenOffline        7.0				/**< Number of days Jailbroken Status offline */

//@}

/** @name Error code */
//@{
#define ERR_Success				0       /**< 0      ->  Success Error code */
#define ERR_BEACON_InvalidConfiguration		-100    /**< -100   ->  Invalid configuration Error code */
#define ERR_BEACON_AlreadyRunning		-101    /**< -101   ->  Invalid configuration Error code  */
#define ERR_BEACON_NoConfigurationAvailable	-102    /**< -102   ->  No  configuration Error code  */
#define ERR_ModuleAlreadyRegistered		-103    /**< -103   ->  Module already registered Error code  */
#define	ERR_NotInitialized			-104    /**< -104   ->  Not Initialized Error code  */
//@}

/** @name Beacon sended file name */
//@{
#define kSystemFileName                         @"System.dat"		/**< System file sended through beacon */
#define kAnalyticsFileName                      @"Analytics.dat"	/**< Analytics file sended through beacon */
#define kNetworkAdapterFileName                 @"NetworkAdapters.dat"  /**< Net adapters sent through interrogator */
#define kGPSFileName                            @"GPS.dat"		/**< GPS data file */
#define kGPSBeaconFileName                      @"BeaconGps.dat"	/**< GPS file sended through beacon */
#define kBeaconShouldSendGPS                    @"BeaconShouldSendGPS"  /**< GPS should be sendede through beacon */
#define kWLAN2Sample                            @"WLAN2Sample.dat"	/**< WLAN2Sample2 be sended through Intrragrator  **/

#define kApplicationSample                      @"application.dat"	/**< application sample be send through Intrragrator  **/
//@}

/** @name Different type key and general Info key */
//@{
#define kBeaconType                             @"beacon"		    /**< beacon type */
#define kInterrogatorType                       @"interrogator"		/**< interrogator type */
#define kDataSamplerType						@"datasampler"		/**< datasampler type */
#define kDeviceInfoType                         @"deviceStatus"		/**< device status */
#define kUserInfoType                           @"userInfo"		    /**< user info */
#define kSupportInfoType                        @"supportInfo"		/**< support info */
#define kCommandProcesorType                    @"commandProcessor"	/**< command processor type */
#define kSettingsEndpointType                   @"settingsEndPoint"	/**< setting end point */
#define kConfigTypeId                           @"configtypeid"		/**< config type Id */
#define kServerError                            @"serverError"		/**< server error */
#define kForceDataSend                          @"AWForceDataSend"	/**< AirWatch forced data send */
#define kMessageType                            @"message"          /***< Message type */
#define kPinningCertificate                     @"pinningKeySet"    /*** <certificatePinning> */
//@}

/**
 @enum AWTraceLevel              Enumeration that defines the module's trace level.
 
 */
typedef enum AWTraceLevel
{
	AWTraceLevelOff		= 0,   /**< Output no tracing and debugging messages. */
	AWTraceLevelError		= 1,   /**< Output error-handling messages. */
	AWTraceLevelWarning		= 2,   /**< Output warnings and error-handling messages.*/
	AWTraceLevelInfo		= 3,   /**< Output informational messages, warnings, and error-handling messages.*/
	AWTraceLevelVerbose		= 4    /**< Output all debugging and tracing messages.*/
}
AWTraceLevel;

typedef enum
{
	AWSSOStatusUnknown,
	AWSSOStatusEnabled,
	AWSSOStatusDisabled
	
}
AWSSOStatus;
#define AW_SDK_VERSION @"5.9.3.3"

typedef enum
{
    AWAuthentication
    
}AwViewControllerType;

typedef enum AWJailBrokenStatus
{
    AWJailBrokenStatusNotAvailable =0,
    AWDeviceNotJailBroken,
    AWDeviceJailBroken
} AWJailBrokenStatus;

#endif
