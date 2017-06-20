/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWLog.h */ 

#import <Foundation/Foundation.h>
#import "AWMacro.h"

/*
 * define log level related macros
 */
#define AWLogFlag  NSUInteger
#define AWLogLevel NSUInteger

extern const AWLogFlag AWLogFlagError;
extern const AWLogFlag AWLogFlagWarning;
extern const AWLogFlag AWLogFlagInfo;
extern const AWLogFlag AWLogFlagVerbose;

extern const AWLogLevel AWLogLevelError;
extern const AWLogLevel AWLogLevelWarning;
extern const AWLogLevel AWLogLevelInfo;
extern const AWLogLevel AWLogLevelVerbose;

/*
 * define macros that trigger the logging method that makes everything easy.
 */
#define AWLogError(frmt,   ...) [[AWLog sharedInstance] logWithLogLevel:AWLogFlagError \
                                                                   file:__FILE__ \
                                                             methodName:__PRETTY_FUNCTION__ \
                                                                   line:__LINE__ \
                                                                message:[NSString stringWithFormat:(frmt), ##__VA_ARGS__]]
#define AWLogWarning(frmt, ...) [[AWLog sharedInstance] logWithLogLevel:AWLogFlagWarning \
                                                                   file:__FILE__ \
                                                             methodName:__PRETTY_FUNCTION__ \
                                                                   line:__LINE__ \
                                                                message:[NSString stringWithFormat:(frmt), ##__VA_ARGS__]]
#define AWLogInfo(frmt,    ...) [[AWLog sharedInstance] logWithLogLevel:AWLogFlagInfo \
                                                                   file:__FILE__ \
                                                             methodName:__PRETTY_FUNCTION__ \
                                                                   line:__LINE__ \
                                                                message:[NSString stringWithFormat:(frmt), ##__VA_ARGS__]]
#define AWLogVerbose(frmt, ...) [[AWLog sharedInstance] logWithLogLevel:AWLogFlagVerbose \
                                                                   file:__FILE__ \
                                                             methodName:__PRETTY_FUNCTION__ \
                                                                   line:__LINE__ \
                                                                message:[NSString stringWithFormat:(frmt), ##__VA_ARGS__]]

/**
 @attention	Please note that AWLog is not thread-safe. Any calls to AWLog should be made on the main thread.
 @brief		AWLog is an utility class, through which we can get specific log of SDK's functionality. Log is very handy way to trace any system's status and through which we can get the senario of any functionalities.
 @discussion In order for the Logging module to function properly, Logging must be enabled in AirWatch console for your
 location group.
 @version 5.9.3.3
 */
@interface AWLog : NSObject

/**
 Initializes the Logging module for use.
 @return AWLog singleton.
 */
+ (AWLog *)sharedInstance;

/*
 * method that reocord log including current file, current function, and the line number
 */
- (void)logWithLogLevel:(AWLogLevel  )logLevel
                   file:(const char *)file
             methodName:(const char *)methodName
                   line:(NSInteger   )lineNumber
                message:(NSString   *)message;

/**
 Sends application level logs to the AirWatch console. Use this to upload log statements created with
 -logWithLogLevel:methodName:line:message:
 
 @param completion - The completion block called once the operation has finished. Two parameters are provided to the
 block.
 BOOL success indicates if the logs were uploaded successfully.
 NSError error will be provided if an error occured. nil otherwise.
 
 @params completion
 */

- (void)sendApplicationLogsWithCompletion:(void(^)(BOOL success, NSError *error))completion;

/**
 Checks if logs are collected.
 
 */
- (BOOL)hasAWLogs;


@end