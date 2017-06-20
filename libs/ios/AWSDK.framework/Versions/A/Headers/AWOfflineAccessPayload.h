
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWOfflineAccessPayload.h */
#import "AWProfilePayload.h"

/**
 @brief		AWOfflineAccessPayload payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the Offline Access group of an SDK profile (V2).
 @version 5.9.3.3
 */
@interface AWOfflineAccessPayload : AWProfilePayload

/** A boolean indicating if Offline Access is enabled. */
@property (nonatomic, readonly) BOOL enableOfflineAccess;

/** The maximum seconds allowed to be offline.*/
@property (nonatomic, readonly) NSTimeInterval maximumSecondsAllowedOffline;

@end