//
//  AWCertificateUtility.m
//
//  Created by Jeff Jones on 8/2/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import "AWCertificateUtility.h"


static NSString * const LOG_TAG = @"CERTIFICATE_PROVIDER";
static NSString * const AW_CERT_PROVIDER_LABEL = @"AWx509CertificateProviderIdentity";

@implementation AWCertificateUtility

+ (void) importCertToKeychain: (NSData *) certData
                     withName: (NSString *) name
                     password: (NSString *) password
                     identity: (SecIdentityRef *) identityRef
                        error: (NSError **) error {

    NSLog(@"In +importCertToKeychain: name == <<%@>>, data length = %d", name, (int)[certData length] );

    if (identityRef == NULL) {
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                     code: ERR_Output_Parameter_Was_Null
                                 userInfo: @{ NSLocalizedDescriptionKey : @"identityRef cannot be null!" }];
        return;
    }


    *identityRef = nil;
    if (error)
        *error = nil;
    SecIdentityRef tempIdRef = nil;

    [self deleteStoredCertificateWithError: error];

    // Import certificate from raw data

    tempIdRef = [self createCertFromData: certData
                    withName: name
                    password: password
                       error: error];
    if (*error) {
        return;
    }

    // Try adding cert to keychain
    [self addCertToKeychain: tempIdRef
               permanentRef: identityRef
                      error: error];

}

+ (void) addCertToKeychain: (SecIdentityRef) tempRef
              permanentRef: (SecIdentityRef *) permRef
                     error: (NSError **) error {

    CFArrayRef items = NULL;
    OSStatus status = 0;
    if (permRef)
        *permRef = nil;
    if (error)
        *error = nil;

    NSDictionary *queryCertificate = @{ SEC_ATTR_LABEL : AW_CERT_PROVIDER_LABEL,
                                        SEC_VALUE_REF  : (__bridge id) tempRef };

    status = SecItemAdd((__bridge CFDictionaryRef) queryCertificate, (CFTypeRef *)permRef);

    if (status == errSecSuccess) {
        NSLog(@"Item successfully added to keychain");

    } else if (status == errSecDuplicateItem) {
        NSLog(@"Item already present in keychain");

    } else {
        NSString *msg = [NSString stringWithFormat: @"%@: Failed to save certificate to keychain, status = %d", LOG_TAG, (int)status];
        NSLog(@"%@", msg);
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                     code: ERR_Save_Certificate_To_KeyChain_Failed
                                 userInfo: @{ NSLocalizedDescriptionKey : msg }];
    }

    if (items != nil)
        CFRelease(items);
}

/**
 * Method to synchronously get a certificate from saved local copy
 * If saved certicate exists, return true and also set the identityref parameter to the certificate
 * If no saved certificate exists, return true and also setting identityRef parameter to nil.
 * If error happens during getting the saved certificate, return false with related error, also setting identityRef parameter to nil
 * @param identityRef \b out parameter: on success return should contains the SecIdentityRef
 * @param error the error in case the operation fail
 * @return YES if the method was success NO otherwise
 */
+ (BOOL) getStoredCertificate: (SecIdentityRef *) identityRef
                        error: (NSError **) error {

    if (identityRef == NULL) {
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                     code: ERR_Output_Parameter_Was_Null
                                 userInfo: @{ NSLocalizedDescriptionKey : @"identityRef cannot be null!" }];
        return NO;
    }

    *identityRef = [self findCertInKeychainWithLabel: AW_CERT_PROVIDER_LABEL
                                               error: error];

    return (*error == nil);
}

+ (SecIdentityRef) findCertInKeychainWithLabel: (NSString *) label
                                         error: (NSError **) error {

    NSDictionary *query;
    CFArrayRef searchResults = nil;
    SecIdentityRef foundIdentity = nil;
    *error = nil;

    if (label && [label length]) {
        query = @{ SEC_CLASS : SEC_CLASS_IDENTITY,
                   SEC_RETURN_REF : @YES,
                   SEC_RETURN_ATTRIBUTES : @YES,
                   SEC_MATCH_LIMIT : SEC_MATCH_LIMIT_ALL,
                   SEC_ATTR_LABEL :  AW_CERT_PROVIDER_LABEL };
    } else {
        query = @{ SEC_CLASS : SEC_CLASS_IDENTITY,
                   SEC_RETURN_REF : @YES,
                   SEC_RETURN_ATTRIBUTES : @YES,
                   SEC_MATCH_LIMIT : SEC_MATCH_LIMIT_ALL };
    }

    OSStatus status = SecItemCopyMatching((__bridge CFDictionaryRef)query, (CFTypeRef *)&searchResults);

    if (status == errSecItemNotFound) {
        return nil;

    } else if ((status == errSecSuccess) && searchResults) {
        CFIndex resultCount = CFArrayGetCount(searchResults);

        for (int i = 0; i < resultCount; i++) {

            NSDictionary *thisResult = (NSDictionary *) CFArrayGetValueAtIndex(searchResults, i);
            id keyClass = thisResult[SEC_ATTR_KEY_CLASS];
            if (keyClass && [[keyClass description] isEqual: SEC_ATTR_KEY_CLASS_PRIVATE]) {
                foundIdentity = (__bridge SecIdentityRef)thisResult[SEC_VALUE_REF];
                //get hold of the new identity object
                CFRetain(foundIdentity);
                break;
            }
        }
        CFRelease(searchResults);
        return foundIdentity;

    } else {
        NSLog(@"Received error code %d while trying to search for identities matching label <<%@>>", (int)status, label);
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                     code: ERR_Read_KeyChain_Item_Failed
                                 userInfo: @{ NSLocalizedDescriptionKey : @"Failed to read certificate from keychain" }];
        return nil;
    }
    

}


/**
 * Method to delete the saved local copy
 * If not saved certificate exists, do nothing and return true,
 * If saved certificate is deleted, return true
 * If saved certificate exists and fails to delete, reture false with error
 * @param anError \b out parameter, pointer to an NSError* variable. In case of fail the cause of error will be put to this variable
 * @return YES if the method was success NO otherwise
 */
+ (void) deleteStoredCertificateWithError: (NSError **) error {

    NSLog(@"Deleting all certificates");

    *error = nil;
    OSStatus status = noErr;
    NSDictionary *queryIdentity;

    queryIdentity = @{ SEC_ATTR_LABEL : AW_CERT_PROVIDER_LABEL,
                       SEC_CLASS : (__bridge id)kSecClassIdentity };

    // Delete the private key.
    status = SecItemDelete((__bridge CFDictionaryRef)queryIdentity);
    if (status != noErr && status != errSecItemNotFound) {
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                        code: ERR_Delete_Saved_Certificate_Failed
                                    userInfo: @{ NSLocalizedDescriptionKey : @"Failed to delete the saved certificate" }];
    }
}

+ (SecIdentityRef) createCertFromData: (NSData *) certData
                             withName: (NSString *) name
                             password: (NSString *) password
                                error: (NSError **) error {

    SecIdentityRef identityRef = nil;
    *error = nil;
    CFArrayRef items = NULL;
    OSStatus status = 0;


    // Import certificate from raw data

    CFDataRef p12data = (__bridge CFDataRef) certData;

    NSDictionary *options = @{SEC_IMPORT_EXPORT_PASSWD : password,
                              SEC_RETURN_REF : @YES,
                              SEC_RETURN_ATTRIBUTES : @YES };

    status = SecPKCS12Import(p12data, (__bridge CFDictionaryRef)options, &items);

    if (status != errSecSuccess) {
        *error = [NSError errorWithDomain: Certificate_Provider_Error_Domain
                                     code: ERR_Load_Certificate_From_File_Failed
                                 userInfo: @{ NSLocalizedDescriptionKey : @"Certificate data invalid." }];
        if (items != nil)
            CFRelease(items);

        return nil;
    }

    CFDictionaryRef identityAndTrust = CFArrayGetValueAtIndex(items, 0);
    identityRef = (SecIdentityRef) CFDictionaryGetValue(identityAndTrust, kSecImportItemIdentity);

    return identityRef;
}

@end
