/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWCommand.h */

#import <Foundation/Foundation.h>
#import "AWMacro.h"

/**
 @enum AWCommandType
 Indicates the type of command
 */
typedef enum
{
	AWUnknownCommand = -1,                  /**< Unknown command. */
	AWInstallProfileCommandType,            /**< Install profile command. */
	AWInstallContentCommandType,            /**< Install content command. */
	AWRemoveContentCommandType,             /**< Remove content command. */
	AWScreenCaptureCommandType,             /**< Screen capture command. */
	AWEraseDeviceCommandType,               /**< Erase device command. */
    AWRequestProfilesCommandType,           /**< Request Profiles command. */
    AWRemoveApplicationProfilesCommandType, /**< Remove Application Profiles Command. */
    AWRequestCertificatesCommandType,        /**< Request Certificates Command. */
    AWUploadLogsCommandType,
    AWResetAppPasscodeType,                     /**< Reset the app passcode */
    AWDeviceLockCommandType,
    AWClearPasscodeCommandType,
    AWClearSSOPasscodeCommandType,         /**< Clear Sso Passcode Command. */
    AWLockSSOCommandType                   /**< Lock Sso Command. */

}
AWCommandType;

/**
 @brief		Represents a command received from AirWatch.
 @details	An abstract class that represents commands created on the AirWatch console.
 @version 5.9.3.3
 */
@interface AWCommand : NSObject
{
    
}

/** 
 *  @name Information About the Command
 */
//@{

/** The UUID of the command. */
@property (nonatomic, readonly) NSString *UUID;

/** The contents of the 'Command' element */
@property (nonatomic, readonly) NSDictionary *commandInfo;

/** A type describing the command. */
@property (nonatomic, assign) AWCommandType type;

//@}

/** @name Initialization */
//@{

/** 
 *  Returns a command built from a dictionary.
 *
 *  @param info The dictionary to be used to build the command.
 *  @return Returns initialized object.
 */
- (id)initWithDictionary:(NSDictionary *)info;

//@}

@end