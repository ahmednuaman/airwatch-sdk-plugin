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

/*! \file AWContentRepository.h */


#import <Foundation/Foundation.h>
#import "AWRepositoryTypeConstants.h"

/**
 @brief		Content management repository.
 @details	Represents a repository to manage content.
 @version 5.2
 */
@interface AWContentRepository : NSObject {
    
}

/** @name Configuring a Content Repository */
//@{

/** The identifier of the repository. */
@property (nonatomic, assign) NSInteger identifier;

/** The display name of the repository. */
@property (nonatomic, copy) NSString *name;

/** The URL to the repository. */
@property (nonatomic, copy) NSString *link;

/** The creator's name of the repository. */
@property (nonatomic, copy) NSString *createdBy;

/** The last modifier's name of the repository. */
@property (nonatomic, copy) NSString *modifiedBy;

/** The last modified date of the repository. */
@property (nonatomic, copy) NSDate *modifiedOn;

/** The boolean value of if the repository allows write access. */
@property (nonatomic, assign) BOOL allowWrite;

/** The boolean value of if this repository is your personal repository. (NOTE: Console sets this to TRUE for Personal Content and User added repositories) */
@property (nonatomic, assign) BOOL isPersonal;

/** The folder identifer for the root level folder. */
@property (nonatomic, assign) NSInteger rootFolderID;

/** The type of repository. */
@property (nonatomic, assign) AWRepositoryType repositoryType;

/** The total number of bytes of content the repository can accommodate. */
@property (nonatomic, assign) long long totalContentCapacity;

/** The number of bytes allowed over the totalContentCapacity. */
@property (nonatomic, assign) long long allowedOverage;

/** The largest individual file size allowed for upload into the repository. */
@property (nonatomic, assign) long long maximumFileSize;

/** The number of bytes currently being used within the reposistory. */
@property (nonatomic, assign) long long usedBytes;

/** Whether or not the repository supports checking content in and out. */
@property (nonatomic, assign) BOOL supportsContentCheckOut;

/** The boolean value of if this repository is user repository. */
@property (nonatomic, assign) BOOL isUserRepository;

/** The identifier of the user repository. */
@property (nonatomic, assign) NSInteger userRepositoryID;

/** Tells whether a repository has automatic downlaods. */
@property (nonatomic, assign) BOOL hasAutomaticDownloads;

/** Tells whether a repository is created using Automatic Templates or not. */
@property (nonatomic, assign) BOOL isAutoTemplate;

/** User can export the files exists in the repository */
@property (nonatomic, assign) BOOL canOpenInOtherApp;


//@}

@end
