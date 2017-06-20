//
//  AWX509CertificateProvider.m
//
//  Created by Jeff Jones on 7/19/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import <Foundation/Foundation.h>

#import "AWX509CertificateProvider.h"
#import "AWCertificateUtility.h"
#import "AWSDKBridge.h"

@interface AWX509CertificateProvider () <AWSDKCertificateReceiver>

@property (copy) void(^completion)(SecIdentityRef identityRef, NSError *error);

@end

@implementation AWX509CertificateProvider

/**
 * Asynchronous method to provision a certificate, the completion block can be called to return the result.
 * The method first checks if the certificate is already provisioned, if it is not yet provisioned, then it requests the certificate from remote server
 * @param option key/value map of the parameters the provider needs
 * @param completion a completion block which should be called on end of the asynchronous operation even on success or fail
 */
- (void) initialize: (NSDictionary *) options
     withCompletion: (void(^)(SecIdentityRef identityRef, NSError *error)) completion {

    NSLog(@"In AWX509CertificateProvider -initialize");

    NSError* err = nil;
    SecIdentityRef identity = nil;

    // See if the certificate is already saved in the keychain
    [self getStoredCertificate: &identity
                         error: &err];

    if (identity != nil) {
        // certificate found
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSLog(@"In AWX509CertificateProvider -initialize, found cert, running completion");
            completion(identity, nil);
            CFRelease(identity);
        });

    } else if (err != nil) {
        // an error happened while searching for the certificate
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            NSLog(@"In AWX509CertificateProvider -initialize, got error getting cert from keychain: %@", [err localizedDescription]);
            completion(nil, err);
        });
        
    } else {
        // certificate not in keychain, but there was no error; poke the SDK to get it to check for a certificate
        NSLog(@"In AWX509CertificateProvider -initialize, no cert, no error, starting AWSDKBridge");
        AWSDKBridge *sdkBridge = [AWSDKBridge sharedInstance];
        self.completion = completion;
        [sdkBridge fetchCertificatesForReceiver: self];
    }
}

- (void) receivedCertificate: (SecIdentityRef) cert
                   withError: (NSError *) error {
    if (self.completion)
        self.completion(cert, error);
}


/**
 * Returns the unique certificate provider ID for the current provider. It is suggested to use reverse domain format for example com.sap.CertProvider
 * @return the unique ID of the provider
 */
- (NSString *) getProviderID {
    return NSStringFromClass(self.class);
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
- (BOOL) getStoredCertificate: (SecIdentityRef *) identityRef
                        error: (NSError **) error {

    [AWCertificateUtility getStoredCertificate: identityRef
                                         error: error];
    return *error == nil;
}


/**
 * Method to delete the saved local copy
 * If not saved certificate exists, do nothing and return true,
 * If saved certificate is deleted, return true
 * If saved certificate exists and fails to delete, reture false with error
 * @param anError \b out parameter, pointer to an NSError* variable. In case of fail the cause of error will be put to this variable
 * @return YES if the method was success NO otherwise
 */
- (BOOL) deleteStoredCertificateWithError: (NSError **) error {
    *error = nil;
    //[AWCertificateUtility deleteStoredCertificateWithError: error];
    return *error == nil;
}


// asynchronous method to get a certificate, the delegate can be called to retrieve user input and return the result.
// The method first check and return the local saved certificate if available, before requesting the certificate from remote server
// report error to caller by calling onGetCertificateFailure delegate method
// return the certificate by calling onGetCertificateSuccess method, the certificate should be saved locally before calling
// onGetCertificateSuccess method
// @deprecated since v3.8.0. This selector is deprecated and obsolite. Please use initialize:option:withCompletion selector instead
- (void) getCertificate: (id<CertificateProviderDelegate>) delegate __attribute__ ((deprecated)) {
    // not implemented
}

/**
 * Method allows the Certificate Provider implementation to expose parameters to the caller.
 * This could useful in case the provider would like the caller to cache or store session data securely.
 * For instance the caller application already implements a Secure Storage that can be used to store pin or other information between sessions.
 * The setParameters:failedWithError: method or the initialize:withCompletion: methods can then be used to send back the data exposed by this
 * method in previous sessions.
 */
- (NSDictionary *) getParameters {
    return nil;
}

/**
 * Method to set required parameters input by user or other sources. For example in case of application:openUrl the url will be passed through this method with a key kCertificateProviderParameterKeyURL
 * Report error immediately by output reference,
 * This error will not cancel the getcertificate operation
 * @param params key/value map of the paramters which should be used by the provider to get the certificate properly.
 * @param error anError \b out parameter, pointer to an NSError* variable. In case of fail the cause of error will be put to this variable
 * @return YES if the method was success NO otherwise
 */
- (BOOL) setParameters: (NSDictionary *) params
       failedWithError: (NSError **) error {
    return NO;
}


@end
