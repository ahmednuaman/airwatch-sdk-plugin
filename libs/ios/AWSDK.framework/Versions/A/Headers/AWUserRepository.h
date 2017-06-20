/*
 Copyright © 2014 AirWatch, LLC. All rights reserved. This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties. AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
/*
 AirWatch iOS Software Development Kit
 Copyright © 2014 AirWatch, LLC. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 
 Unless required by applicable law, this Software Development Kit and sample code is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied. AirWatch expressly disclaims any and all liability resulting from User’s use of this Software Development Kit. Any modification made to the SDK must have written approval by AirWatch.
 */

/*! \file AWUserRepository.h */


#import <Foundation/Foundation.h>

/**
 @brief		Content management user repository.
 @details	Represents a user repository to manage content.
 @version 4.1.1
 */
@interface AWUserRepository : NSObject {
    
}

/** @name Configuring a Content Repository */
//@{

/** The identifier of the user repository. */
@property(nonatomic, assign)NSInteger identifier;

/** The name of the user added repository. */
@property(nonatomic, copy)NSString *name;

/** The link of the user added repository. */
@property(nonatomic, copy)NSString *link;

/** The user who created the user added repository. */
@property(nonatomic, copy)NSString *createdBy;

/** The the user who modified the user added repository. */
@property(nonatomic, copy)NSString *modifiedBy;

/** The date on which the user added repository was modified. */
@property(nonatomic, copy)NSDate *modifiedOn;

/** Bool value indicating if the user added repository is online only. */
@property(nonatomic, assign)BOOL onlineOnly;

/** Bool value to indicate whether we can email the content in the user added repository. */
@property(nonatomic, assign)BOOL email;

/** Bool value to indicate whether we can print the content in the user added repository */
@property(nonatomic, assign)BOOL print;

/** The priority of the user added repository. */
@property(nonatomic, copy)NSString *priority;

/** The method of the user repository. */
@property(nonatomic, copy)NSString *method;

/** Bool value to indicate whether roaming is enabeld in the user added repository. */
@property(nonatomic, assign)BOOL roaming;

//@}

@end
