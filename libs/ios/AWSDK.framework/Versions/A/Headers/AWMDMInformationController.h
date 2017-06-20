//
//  AWMDMInformationController.h
//  AirWatch
//
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//
/*! @file AWMDMInformationController.h */

#import <Foundation/Foundation.h>
#import "AWSession.h"

typedef enum {
    AWComplianceStatusUnknown = 0,
    AWComplianceStatusAllowed,
    AWComplianceStatusBlocked,
    AWComplianceStatusCompliant,
    AWComplianceStatusNonCompliant,
    AWComplianceStatusNotAvailable,
    AWComplianceStatusNotApplicable,
    AWComplianceStatusPendingComplianceCheck,
    AWComplianceStatusPendingComplianceCheckForAPolicy,
    AWComplianceStatusRegistrationActive,
    AWComplianceStatusRegistrationExpired,
    AWComplianceStatusQuarantined
}AWComplianceStatus;

typedef enum
{
    AWEnrollmentStatusDeviceNotFound = 0,
    AWEnrollmentStatusDiscovered,
    AWEnrollmentStatusRegistered,
    AWEnrollmentStatusEnrollmentInProgress,
    AWEnrollmentStatusEnrolled,
    AWEnrollmentStatusEnterpriseWipePending,
    AWEnrollmentStatusDeviceWipePending,
    AWEnrollmentStatusRetired,
    AWEnrollmentStatusUnenrolled,
    // This is not a status explictly returned by the console, so starting the enum
    // value at 100 will leave room for future console statuses to be added.
    AWEnrollmentStatusUnknown = 100
}AWEnrollmentStatus;

typedef enum {
	AWRequeryApplist = 1,
	AWRequeryDeviceInfo,
	AWRequeryProfileInfo,
	AWRequerySecurityInfo
}AWRequeryType;

typedef enum
{
    AWDeviceNotManaged = 0,
    AWDeviceManagedByMDM,
    AWDeviceManagedByMAM,
    AWDeviceQuarantine
}AWDeviceManagmentType;

typedef void (^ StatusCompletionHandler)(BOOL isManaged,
                                         AWEnrollmentStatus enrollmentStatus,
                                         AWComplianceStatus complianceStatus,
                                         NSString *groupName,
                                         NSString *groupID,
                                         NSError *error);

typedef void (^ StatusCompletionHandlerWithManagementType)(BOOL isManaged,
                                         AWEnrollmentStatus enrollmentStatus,
                                         AWComplianceStatus complianceStatus,
                                         NSString *groupName,
										 NSString *groupID,
                                         AWDeviceManagmentType managementType,
                                         NSError *error);
/*!
 @brief policies is an array of NSDictionary Objects.
 */
typedef void (^ CompliancePoliciesHandler)(BOOL success, NSArray *policies,NSError *error);

/*!
 @brief policyRules is an array of NSDictionary Objects.
 */
typedef void (^ CompliancePolicyRuleHandler)(BOOL success, NSArray *policyRules,NSError *error);
typedef void (^ UserInfoHandler)(BOOL success, NSDictionary *userInfo,NSError *error);
typedef void (^ RequeryHandler)(BOOL success,NSError *error);


/** Keys used to access information the user dictionary */
extern NSString *const AWMDMUserNameKey;
extern NSString *const AWMDMUserAccountTypeKey;
extern NSString *const AWMDMUserIsActiveKey;
extern NSString *const AWMDMUserLocationGroupKey;

/** Keys used to access information from a Policy dictionary */
extern NSString *const AWMDMPolicyIDKey;
extern NSString *const AWMDMPolicyNameKey;
extern NSString *const AWMDMPolicyStatusKey;
extern NSString *const AWMDMPolicyLastComplianceCheckKey;

/** Keys used to access informantion from a policy rule dictionary */
extern NSString *const AWMDMPolicyRuleOperatorKey;
extern NSString *const AWMDMPolicyRuleTypeKey;
extern NSString *const AWMDMPolicyRuleValuesKey;

@interface AWMDMInformationController : NSObject

/** session
 AWSession object used to obtain a session token from the AirWatch console.
 This object should be initialized and have a valid token.
 */
@property (nonatomic, strong) AWSession *session;

- (id)initWithSession:(AWSession*)session;

/*!
 @brief Retrieves device enrollmentStatus, complianceStatus, groupName, groupID and deviceManagementType
 @param block the block of code that the receiver should execute once the operation is complete.
 */
- (void)fetchStatusWithManagementTypeAndCompletionBlock:(StatusCompletionHandlerWithManagementType)block;

/*!
 @brief Retrieves available compliance policies.
 @param block the block of code that the receiver should execute once the operation is complete.
 */
-(void) fetchCompliancePoliciesWithCompletionBlock:(CompliancePoliciesHandler)block;

/*!
 @brief Retrieves rules for a particula policy.
 @param policyID the id of the policy to obtain rules for.
 @param block the block of code that the receiver should execute once the operation is complete.
 */
-(void) fetchCompliancePolicyRule:(NSInteger) policyID
              withCompletionBlock:(CompliancePolicyRuleHandler) block;

/*!
 @brief Request that the AirWatch Console re-query information from the device.
 @param queryType The type of query you wish the server to perform.
 */
-(void) fetchUserInfoWithCompletionBlock:(UserInfoHandler)block;

/*!
 @brief Request that the AirWatch Console re-query information from the device.
 @param queryType The type of query you wish the server to perform.
 */
-(void) reQuery:(AWRequeryType)queryType withCompletionBlock:(RequeryHandler) block;

@end