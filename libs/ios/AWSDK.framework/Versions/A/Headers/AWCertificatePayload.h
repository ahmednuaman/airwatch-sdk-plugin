
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWCertificatePayload.h */

#import "AWProfilePayload.h"

/**
 @brief		Analytics payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the certificate group of an application profile.
 @version 5.9.3.3
 */
@interface AWCertificatePayload : AWProfilePayload
{
	
}

/** The certificate's data. */
@property (nonatomic, readonly) NSData *certificateData;

/** The name of the certificate. */
@property (nonatomic, readonly) NSString *certificateName;

/** The password of the certificate. */
@property (nonatomic, readonly) NSString *certificatePassword;

/** The thumbprint of the certificate. */
@property (nonatomic, readonly) NSString *certificateThumbprint;

/** The type of the certificate. */
@property (nonatomic, readonly) NSString *certificateType;

@end