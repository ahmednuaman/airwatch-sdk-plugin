//
//  AWCertificateUtility.h
//
//  Created by Jeff Jones on 8/2/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import <Foundation/Foundation.h>

//define error code and error domain for error message localization
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
#define ERR_Output_Parameter_Was_Null               -10


#define SEC_ATTR_LABEL             ((__bridge NSString *)kSecAttrLabel)
#define SEC_ATTR_APPL_TAG          ((__bridge NSString *)kSecAttrApplicationTag)
#define SEC_CLASS                  ((__bridge NSString *)kSecClass)
#define SEC_CLASS_IDENTITY         ((__bridge NSString *)kSecClassIdentity)
#define SEC_CLASS_CERTIFICATE      ((__bridge NSString *)kSecClassCertificate)
#define SEC_RETURN_REF             ((__bridge NSString *)kSecReturnRef)
#define SEC_RETURN_ATTRIBUTES      ((__bridge NSString *)kSecReturnAttributes)
#define SEC_VALUE_REF              ((__bridge NSString *)kSecValueRef)
#define SEC_MATCH_LIMIT            ((__bridge NSString *)kSecMatchLimit)
#define SEC_MATCH_LIMIT_ALL        ((__bridge NSNumber *)kSecMatchLimitAll)
#define SEC_ATTR_KEY_CLASS         ((__bridge NSString *)kSecAttrKeyClass)
#define SEC_ATTR_KEY_CLASS_PRIVATE ((__bridge NSString *)kSecAttrKeyClassPrivate)
#define SEC_IMPORT_EXPORT_PASSWD   ((__bridge NSString *)kSecImportExportPassphrase)

@interface AWCertificateUtility : NSObject

+ (void) importCertToKeychain: (NSData *) certData
                     withName: (NSString *) name
                     password: (NSString *) password
                     identity: (SecIdentityRef *) identityRef
                        error: (NSError **) error;

+ (BOOL) getStoredCertificate: (SecIdentityRef *) identityRef
                        error: (NSError **) error;

+ (SecIdentityRef) findCertInKeychainWithLabel: (NSString *) label
                                         error: (NSError **) error;

+ (void) deleteStoredCertificateWithError: (NSError **) error;

@end
