
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWCrashLogReporter.h */


#import <Foundation/Foundation.h>


/**
 * @version 5.9.3.3
 */
@interface AWCrashLogReporter : NSObject


/** Enables the crash reporter and registers for crash tracking.
 
 Method should be called when the host application is ready to start crash tracking.
 
 @return A BOOL value indicating registration was a success or failure.
 @param outError Out parameter used if an error occurs while registering for crash tracking. May be NULL.
 */
- (BOOL)startUp:(NSError **)outError;


//- (BOOL)shutDown:(NSError **)outError;

/**
 
 @brief Returns YES if the application has previously crashed and an pending crash report is available.
 */
- (BOOL)hasPendingCrashReport;

/**
 
 @brief If an application has a pending crash report, this method crash reporting and cleanup.
 */
- (void)reportCrashLogToConsole;


@end