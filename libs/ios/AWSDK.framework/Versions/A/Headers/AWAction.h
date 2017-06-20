
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWAction.h */

#import <Foundation/Foundation.h>

/** @enum AWActionType
    @brief     The specific type of action.
 */
typedef enum
{
	AWActionDisplayAlert = 1,   /**< Display alert message. */
	AWActionLockUser,           /**< Lock the user out of the application. */
	AWActionWipeApplication,    /**< Wipe the application data. */
	AWActionRestrictAccess,     /**< Restrict access to the application. */
	AWActionCustom,             /**< Custom action. */
	AWActionReportBackToServer  /**< The application should report back to AirWatch via a Beacon message. */
}
AWActionType;

/**
 @brief		Executable actions. 
 @details	Action that should be executed when a defined condition is met.
 @version 5.9.3.3
 */
@interface AWAction : NSObject <NSCoding>
{
	
}

/** 
 @brief A type describing the action. 
 */
@property (nonatomic, assign) AWActionType type;

/** 
 @brief The value of the action.
 @detail This will only be non-nil when the `type` is `AWActionDisplayAlert` or `AWActionCustom`.
 */
@property (nonatomic, copy) NSString *value;

@end