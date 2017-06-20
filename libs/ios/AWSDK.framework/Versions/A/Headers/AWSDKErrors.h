
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWSDKErrors.h */ 

#import <Foundation/Foundation.h>

extern NSString *const AWSDKErrorDomain;

/** @constant The Game Kit framework error domain. */
extern NSString *const AWSDKReachabilityErrorDomain;

/** @constant Error domain for NSError values stemming from the Beacon module. */
extern NSString *const AWSDKBeaconErrorDomain;

/** @constant Error domain for NSError values stemming from the Interrogator module. */
extern NSString *const AWSDKInterrogatorErrorDomain;

/** @constant Error domain for NSError values stemming from the DataSampler module. */
extern NSString *const AWSDKDataSamplerErrorDomain;

/** @constant Error domain for NSError values stemming from the Security module. */
extern NSString *const AWSDKSecurityErrorDomain; 

/** @constant Error domain for NSError values stemming from the Logging module. */
extern NSString *const AWSDKLoggingErrorDomain;

/** @constant Error domain for NSError values stemming from the Device Management module. */
extern NSString *const AWSDKDeviceStatusErrorDomain;

/** @constant Error domain for NSError values stemming from the AWCompliance Service. */
extern NSString *const AWSDKComplianceErrorDomain;

/** @constant Error domain for NSError values stemming from AWRequeryDevice */
extern NSString *const AWSDKMDMInformationErrorDomain;

/** @constant Error domain for NSError values stemming from Certificate Pinning */
extern NSString *const AWSDKCertPinningErrorDomain;

/*! @constant Error domain for NSError values stemming from AWContentController */
extern NSString *const AWSDKContentErrorDomain;

/*! @constant Error domain for NSError values stemming from AWCommandManager */
extern NSString *const AWSDKCommandManagerErrorDomain;

/*! @constant Error domain for NSError values stemming from the Server module */
extern NSString *const AWSDKServerErrorDomain;

/*! @constant Error domain for NSError values stemming from the NIAP Validation*/
extern NSString *const AWNIAPPolicyValidationErrorDomain;

/*! @constant Error domain for NSError values stemming from the NIAP TLS Client Authentication*/
extern NSString *const AWNIAPClientAuthenticationErrorDomain;

/**
 @enum Enum of error codes specific to the AWSDKCommandManagerErrorDomain
 */
typedef NS_ENUM(NSUInteger, AWSDKCommandManagerError) {
	AWSDKCommandManagerErrorHMACKeyMissing,
	AWSDKCommandManagerErrorHMACKeyInvalid,
	AWSDKCommandManagerErrorUnsupportedEndpoint,
	AWSDKCommandManagerErrorNoProfilesAvailable,
	AWSDKCommandManagerErrorUnknownServerError
};

/**
 @enum      Enum provides status of general errors,enrollment authentication errors,logging module errors, beacon module errors, interrogator module errors, security module errors.
 @version 5.9.3.3
 */
typedef enum {
	// General Errors
	AWFileDoesNotExist = 1,		 			///< The requested file does not exist
	AWUnableToWriteFile,					///< Unable to save requested file
	AWConfigurationValuesUnavailable,			///< The module was unable to read configuration values
	AWModuleNotInitialized,					///< The module was not initialized.
	AWInteralServerError,					///< The endpoint encountered an internal server error.
    AWJSONSerializationError,
	AWMissingParameters,
    
	// Enrollment Authentication Errors
	AWInvalidActivationCode,				///< The enrollment activation code was invalid.
	AWInvalidCredentials,					///< The enrollment credentials were invalid.
	AWDeviceNotFoundErrorCode,				///< The device could not be found on the specified AirWatch instance.
	AWDeviceNotEnrolledErrorCode,				///< The device was found on the specified AirWatch instance, but appears to be unenrolled.
	AWAccountDeviceMismatch,				///< The authenticated user has not enrolled using this device.
	
	// Logging Module Errors
    AWSDKLoggingTriedToSendEmptyLogFile,
    AWSDKLoggingFailedToSendLogsWithoutWIFI,
	
	// Beacon Module Errors
	AWBeaconModuleBusy,					///< The request could not be processed because other processes are underway.
	AWBeaconConfigFieldsMissing,				///< One or more required fields are missing.
	AWBeaconShutdownFailure,				///< Beacon shut down failed - see underlying reason.
	AWBeaconStartUpFailure,					///< The Beacon module start up failed.
	AWBeaconJSONParsingFailure,				///< The response interpreter encountered an error during JSON parsing.
	AWBeaconMessageNotInitialized,				///< Beacon message must be initialized before sending.
	AWBeaconMessageSendFailure,				///< Beacon message could not be sent - connection failed.
	AWBeaconSendMgrNotInitialized,				///< Beacon send manager must be initialized before use.
	AWBeaconDeviceNotEnrolled,				///< Beacon responded from the console with a device not enrolled status.
	AWBeaconUnknownStatus,					///< Beacon responded from the console with an unknown status code.
	
	// Interrogator Module Errors
	AWInterrogatorModuleBusy,				///< The request could not be processed because other processes are underway.
	AWInterrogatorFieldsMissing,				///< One or more required fields are missing.
	AWInterrogatorShutdownFailure,				///< Interrogator shut down failed - see underlying reason.
	AWInterrogatorStartUpFailure,				///< Interrogator start up failed.
	AWInterrogatorMessageNotInitialized,			///< Interrogator message must be initialized before sending.
	AWInterrogatorMessageSendFailure,			///< Interrogator message could not be sent - connection failed.
	AWInterrogatorTransmitterNotInitialized,		///< Interrogator send manager must be initialized before use.
	
    AWDataSamplerNotInitialized,           // Data Sampler not Initialized
    
	// Security Module Errors
	AWErrorSecurityApplicationSecurityDisabled,		///< The application has the security module disabled.
	AWErrorSecurityBackupPolicyViolated,			///< The device has broken the device compliance policy for being installed from a backup
	AWErrorSecurityCompromisedPolicyViolated,		///< The device has broken the device compliance policy for being compromised
	AWErrorSecurityOfflinePolicyViolated,			///< The device has broken the device compliance policy for being offline.
	AWErrorSecurityOfflineUseCountPolicyViolated,		///< The device has broken the device compliance policy for being used offline more than allowed number of times.
	AWErrorSecurityOfflineUseDurationPolicyViolated,	///< The device has broken the device compliance policy for being used offline more than allowed duration.
	
	
	// Other Errors
	AWErrorDeviceStatusMalformedURL,			///< The request could not be fulfilled because of a malformed URL.
	AWSecureChannelInvalidServerCertificateError,		///< The server certificate returned is not trusted.
	AWSecureChannelHandshakeFailedError,			///< The handshake process was not completed successfully.
    AWServerUrlNotSet,
	AWUnhandledExceptionError,
	
	// Restrictions Module Errors
	AWRestrictionsInitializationFailure,
	
	// Compliance Service Errors
	AWComplianceStartUpFailure,
	AWComplianceShutdownFailure,
    
	AWSDKEndpointUnavailable,
    AWSDKEndPointAuthenticationFailed,
    AWSDKServerResponseError,
    AWSDKErrorHMACTokenDoesNotExist,
    
    // Content Errors
    AWSDKServerDoesNotSupportOperation,
    
    // Session Errors
    AWSessionFailedToGetTokenError,
    AWSessionFailedToInvalidateTokenError,
    
    // Server HTTP response errors
    AWServerPageNotFound,  // http response code 404
    AWServerUnavailable,    // http response code 503
    AWSDKErrorUnexpectedServerResponse, // i.e. not a 200
    AWSDKErrorResponseBodyMissing,
    
    AWSDKErrorUnexpectedJSONType,
    AWSDKErrorJSONDeserializationFailed,
    
    // UDID related stuff
    AWSDKErrorNoUDIDPresent,
    
    AWSDKErrorNotInitialized,
    AWSDKErrorServerNotSet,
    AWSDKErrorInitializationFailed,
	
	AWSDKErrorSDKSchemeNotSet,
	AWSDKErrorOpenURLSchemeIsMissing,
    AWSDKErrorMissingParameterInURL,
    
    AWSDKFailedParse,
	
	AWSDKErrorUIDLookupEndpointUnavailable = 9000,
	AWSDKErrorUIDLookupEndpointLookUpFailed = 9001,
	AWSDKErrorUIDLookupEndpointUnsupported = 9002,
	
	AWSDKErrorIOS7UIDLookupEndpointUnavailable = 9003,
	AWSDKErrorIOS7UIDLookupEndpointLookUpFailed = 9004,
	AWSDKErrorIOS7UIDLookupEndpointUnsupported = 9005,
    AWSDKErrorIOS7InvalidMacAddress = 9006,
	
	AWSDKErrorApplicationAuthenticationFailed = 11000,
	AWSDKErrorProfileFetchFailed,
	AWSDKErrorProxySetupFailed,
    AWSDKErrorContentFilterSetupFailed,
    
    //certificate errors
    AWSDKErrorCertNotAvailableForHost,
    AWSDKErrorCredentialNotAvialableForHost,
    AWSDKErrorAuthenticationMethodNotSupported,
    AWSDKErrorCertShareNotSupported,
    AWSDKInvalidCertificateRequested,

    // Reachability error
    AWNetworkNotReachable,
    
    //Certificate Pinning error
    AWCertificateFetchInProgress,
    AWAutodiscoverEndpointAlreadyCalledOnceInFGStateOfApp,    // We need to call AW autodiscovery endpoint only once, even if it does not return payload
    AWDSEndpointCanNotProceedSinceAutodiscoveryReturnNULL,
    
    // Device Services
    AWDeviceServicesURLNil,
    
    AWAuthInvalidCredentials = -1001,           // InvalidCredentialsErrorTitle
    AWAccountLocked = -1002,                    // AccountLockedErrorMessage
    AWInActive = -1003,                         // InActiveErrorMessage
    AWNotMDMEnrolled = -1004,                   // NotMDMEnrolledErrorMessage
    AWInvalidToken = -1005,                     // InvalidTokenErrorMessage
    AWDeviceNotFound = -1006,                   // DeviceNotFoundErrorMessage
    AWSyncClientNotEnabled = -1007,             // SyncClientNotEnabledErrorMessage
    AWPersonalContentNotEnabled = -1008,        //PersonalContentNotEnabledErrorMessage
    AwchatNotEnabled = -1009,                   // AwchatNotEnabled
    
   
    
    
}AWInternalServerErrorType;