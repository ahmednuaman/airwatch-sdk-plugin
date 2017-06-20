//
//  AWX509CertificateProvider.h
//
//  Created by Jeff Jones on 7/19/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#ifndef AWX509CertificateProvider_h
#define AWX509CertificateProvider_h

#import "CertificateProvider.h"

// Error codes and error domain for error message localization
#define Certificate_Provider_Error_Domain            @"ERR_Certificate_Provider"
#define ERR_ShowUI_Delegate_Html                     -1
#define ERR_ShowUI_Delegate_ViewController           -2
#define ERR_ShowUI_Delegate_No_UI_Settings           -3
#define ERR_Set_Parameters_Failed                    -4
#define ERR_Certificate_File_Not_Exist               -5
#define ERR_Load_Certificate_From_File_Failed        -6
#define ERR_Save_Certificate_To_KeyChain_Failed      -7
#define ERR_Read_KeyChain_Item_Failed                -8
#define ERR_Delete_Saved_Certificate_Failed          -9

// To save some clutter, these macros provide NSString* casts of the constants
// used in the Security and Keychain API's
#define SEC_ATTR_LABEL         ((__bridge NSString *)kSecAttrLabel)
#define SEC_CLASS              ((__bridge NSString *)kSecClass)
#define SEC_RETURN_REF         ((__bridge NSString *)kSecReturnRef)
#define SEC_RETURN_ATTRIBUTES  ((__bridge NSString *)kSecReturnAttributes)
#define SEC_VALUE_REF          ((__bridge NSString *)kSecValueRef)
#define SEC_MATCH_LIMIT        ((__bridge NSString *)kSecMatchLimit)
#define SEC_MATCH_LIMIT_ALL    ((__bridge NSNumber *)kSecMatchLimitAll)

@interface AWX509CertificateProvider : NSObject <CertificateProvider>

@end

#endif /* AWX509CertificateProvider_h */
