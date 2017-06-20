//
//  AWNetworkActivityStatus.h
//  AirWatch
//
//  Created by Iury Bessa on 10/19/15.
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

#ifndef AWNetworkActivityStatus_h
#define AWNetworkActivityStatus_h

typedef enum
{
    AWNetworkActivityInit = -2,
    AWNetworkActivityNormal = -1,
    AWNetworkActivityBadSSID,
    AWNetworkActivityCellularDisabled,
    AWNetworkActivityRoaming,
    AWNetworkActivityProxyFailed,
    AWNetworkActivityNetworkNotReachable
}AWNetworkActivityStatus;


#endif /* AWNetworkActivityStatus */