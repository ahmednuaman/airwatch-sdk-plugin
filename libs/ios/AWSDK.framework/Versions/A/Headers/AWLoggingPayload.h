
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWLoggingPayload.h */

#import "AWProfilePayload.h"
#import "AWLog.h"

/**
 @brief		Logging payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the Logging group of an SDK profile.
 @version 5.9.3.3
 */

@interface AWLoggingPayload : AWProfilePayload

/** An AWLogTraceLevel that defines the logging module's trace level. */
@property (nonatomic, readonly) AWLogLevel loggingLevel;

/** A boolean that defines if logs should only be sent while connected to wifi. */
@property (nonatomic, readonly) BOOL sendLogsOverWifiOnly;

@end