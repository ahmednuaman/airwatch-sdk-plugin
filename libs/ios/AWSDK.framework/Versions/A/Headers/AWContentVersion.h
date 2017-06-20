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

/*! \file AWContentVersion.h */ 

#import <Foundation/Foundation.h>

@class AWContentEntity;

/** 
 @enum AWContentVersionHashAlgorithm              Enumeration that defines the content version's Hash algorithm type.
 */
typedef enum
{
    AWContentVersionMD5 = 0,  /** content version MD5 Hash algorithm. */
    AWContentVersionSHA1 = 1, /** content version SHA1 Hash algorithm. */    
}
AWContentVersionHashAlgorithm;

/**
 @brief		Content management version.
 @details	AWContentVersion manage to configure the content version. AWContentVersion is module class which keeps the information related to content version.
 @version 5.2
 */
@interface AWContentVersion : NSObject {
    
}

/** @name Configuring a Content Version */
//@{

/** The identifier of the content version. */
@property (nonatomic, assign) NSInteger identifier;

/** A human-readable text representation of the version's version. */
@property (nonatomic, copy)   NSString *friendlyVersion;

/** Notes regarding the version. */
@property (nonatomic, copy)   NSString *notes;

/** Size (in bytes) of the content's file. */
@property (nonatomic, assign) NSInteger size;

/** An MD5 or SHA1 hash of the file. */
@property (nonatomic, copy)   NSString *dataHash;

/** The URL of the file on AirWatch. */
@property (nonatomic, strong) NSURL *URL;

/** A relationship to the version's entity. */
@property (nonatomic, weak) AWContentEntity *contentEntity;

/** The author of the document. */
@property (nonatomic, copy) NSString *author;

/** The subject of the document. */
@property (nonatomic, copy) NSString *subject;

/** Keywords describing the document. */
@property (nonatomic, strong) NSArray *keywords;

/** The algorithm used to hash the file. */
@property (nonatomic, assign) AWContentVersionHashAlgorithm hashAlgorithm;

/** A flag to determine if encryption will be run on the content or not */
@property (nonatomic, assign) BOOL encrypted;


//@}

@end
