
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWIntegratedAuthPayload.h */
#import "AWProfilePayload.h"

/**
 @brief		AWIntegratedAuthPayload payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the Integrated Authentication group of an SDK profile (V2).
 @version 5.9.3.3
 */
@interface AWIntegratedAuthPayload : AWProfilePayload

@property (nonatomic, readonly) BOOL enableIntegratedAuthentication;   /**< A boolean indicating if Integrated Authentication is enabled. */

@property (nonatomic, readonly) NSArray *allowedSites;

@end