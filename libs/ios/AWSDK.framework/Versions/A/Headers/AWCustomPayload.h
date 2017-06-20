/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */


/*! \file AWCustomPayload.h */

#import "AWProfilePayload.h"

/**
 @brief     Custom payload that is contained within a 'AWProfile'.
 @version 5.9.3.3
 */
@interface AWCustomPayload : AWProfilePayload
{
	
}

/** The custom settings represented as a string. */
@property (nonatomic, readonly) NSString *settings;

@end