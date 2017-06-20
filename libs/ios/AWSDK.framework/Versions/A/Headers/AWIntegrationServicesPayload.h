/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */


/*! \file AWIntegrationServicesPayload.h */

#import "AWProfilePayload.h"

/**
 @brief     Breezy payload that is contained within a 'AWProfile'.
 @version 5.9.3.3
 */

@interface AWIntegrationServicesPayload : AWProfilePayload

@property (nonatomic, readonly, copy) NSString *breezyMDMAuthToken;
@property (nonatomic, readonly, copy) NSString *breezyServerURL;

@property (nonatomic, readonly, copy) NSString *breezyOauthConsumerID;
@property (nonatomic, readonly, copy) NSString *breezyOauthConsumerSecret;

@property (nonatomic, readonly) BOOL isEnabled;

@end