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

/*! \file AWRepositoryQuotaInfo.h */

/**
 @brief		Content management repository/user quota info.
 @details	AWRepositoryQuotaInfo encapsulates the quota information on a user's personal repository.
 @version 5.2
 */

#import <Foundation/Foundation.h>

@interface AWRepositoryQuotaInfo : NSObject

/** The name of the user owning the repository. */
@property (nonatomic, copy) NSString * userName;

/** The users unique identifier. */
@property (nonatomic, assign) NSInteger userID;

/** The location group that the user belongs to. */
@property (nonatomic, copy) NSString * locationGroupName;

/** The unique idnetifier for the repository. */
@property (nonatomic, assign) NSInteger repositoryID;

/** The total number of bytes of content the repository can accommodate. */
@property (nonatomic, assign) long long totalContentCapacity;

/** The number of bytes allowed over the totalContentCapacity. */
@property (nonatomic, assign) long long allowedOverage;

/** The largest individual file size allowed for upload into the repository. */
@property (nonatomic, assign) long long maximumFileSize;

/** The number of bytes currently being used within the reposistory. */
@property (nonatomic, assign) long long usedBytes;

@end
