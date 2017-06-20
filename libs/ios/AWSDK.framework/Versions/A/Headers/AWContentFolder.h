//
//  AWContentFolder.h
//  AWSDKCore
//
//  Created by Syed Yusuf on 7/6/12.
/*
 Copyright © 2014 AirWatch, LLC. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

/*! \file AWContentFolder.h */


#import <Foundation/Foundation.h>


/**
 @brief		Content management folder.
 @details	Represents a folder to manage content.
 @version 5.2
 */
@interface AWContentFolder : NSObject {
    
}


/** @name Configuring a Content Folder */
//@{

/** The identifier of the folder. */
@property (nonatomic, assign) NSInteger identifier;

/** The display name of the folder. */
@property (nonatomic, copy) NSString *name;

/** The identifier of the folder's parent. */
@property (nonatomic, assign) NSInteger parent;

/** The URL to the folder. */
@property (nonatomic, copy) NSURL *href;

/** The boolean indicating whether the folder is private or not. */
@property (nonatomic, assign) BOOL isPrivate;

/** The type of the folder. */
@property (nonatomic, assign) NSInteger type;

/** The creator's name of the folder. */
@property (nonatomic, copy) NSString *createdBy;

/** The last modifier's name of the folder. */
@property (nonatomic, copy) NSString *modifiedBy;

/** The creation date of the folder. */
@property (nonatomic, copy) NSDate *createdOn;

/** The last modified date of the folder. */
@property (nonatomic, copy) NSDate *modifiedOn;

/*! The boolean indicating whether the user can read the content within the folder. */
@property (nonatomic, readonly) BOOL hasReadPermission;

/*! The boolean indicating whether the user can write into the folder. */
@property (nonatomic, readonly) BOOL hasWritePermission;

/*! The boolean indicating whether the user can delete the folder. */
@property (nonatomic, readonly) BOOL hasDeletePermission;

/*! The boolean indicating whether the user can view the sharing settings. */
@property (nonatomic, readonly) BOOL hasShareReadPermission;

/*! The boolean indicating whether the user can edit the sharing settings. */
@property (nonatomic, readonly) BOOL hasShareWritePermission;

/*! The boolean indicating whether the folder is shared. */
@property (nonatomic, assign) BOOL isShared;

/*! The ID of the user which owns the folder. */
@property (nonatomic, assign) NSInteger ownerUserID;

/*! The boolean indicating whether the folder has automatic downloads. */
@property (nonatomic, assign) BOOL hasAutomaticDownloads;

/*! The name of the owner of the shared folder. (exists only if shared) */
@property (nonatomic, copy) NSString *ownerDisplayName;

//@}

@end
