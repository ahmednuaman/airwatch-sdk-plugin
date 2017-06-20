
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWAnalyticsPayload.h */

#import "AWProfilePayload.h"

/**
 @brief		Analytics payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the analtyics group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWAnalyticsPayload : AWProfilePayload

@property (nonatomic, readonly) BOOL enabled;   /**< A boolean indicating if analytics are enabled. */

@end