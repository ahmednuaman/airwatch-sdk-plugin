
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWNetworkAccessPayload.h */

#import "AWProfilePayload.h"

extern NSString *const kNetworkAccessPayloadTypeV2;

typedef NS_ENUM(NSInteger, AWNetworkAccessAllowCellular) {
    AWNetworkAccessAllowCellularNever = 0,
    AWNetworkAccessAllowCellularAlways = 1,
    AWNetworkAccessAllowCellularNotRoaming = 2
};

typedef NS_ENUM(NSInteger, AWNetworkAccessAllowWiFi) {
    AWNetworkAccessAllowWiFiAlways = 1,
    AWNetworkAccessAllowWiFiFilter = 2
};

@interface AWNetworkAccessPayload : AWProfilePayload

@property (nonatomic, readonly) BOOL enableNetworkAccess;
@property (nonatomic, readonly) AWNetworkAccessAllowCellular allowCellularConnection;
@property (nonatomic, readonly) AWNetworkAccessAllowWiFi allowWifiConnection;
@property (nonatomic, readonly) NSArray *allowedSSIDs;

@end