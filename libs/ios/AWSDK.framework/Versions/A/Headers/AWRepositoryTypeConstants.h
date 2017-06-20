//
//  AWRepositoryTypeConstants.h
//  AirWatch
//
//  Created by Karthik Ramakrishna on 11/6/15.
//  Copyright © 2015 AirWatch. All rights reserved.
//

/**
 @enum AWRepositoryType              Enumeration that defines the repository type.
 */
typedef enum {
    AWRepositoryTypeUnknown,
    AWRepositoryTypeSharePoint,
    AWRepositoryTypeSharePointWebDAV,
    AWRepositoryTypeSharePointOffice365,
    AWRepositoryTypeFile,
    AWRepositoryTypeWebDAV,
    AWRepositoryTypeBox,
    AWRepositoryTypeAmazonS3,
    AWRepositoryTypeGoogleDrive,
    AWRepositoryTypeSkyDrive,
    AWRepositoryTypeRepoWindowsAuth,
    AWRepositoryTypeSharePointADFS,
    AWRepositoryTypeSharePointOffice365ADFS,
    AWRepositoryTypeSharePointOneDriveADFS,
    AWRepositoryTypeCMIS,
    AWRepositoryTypeDropBox
} AWRepositoryType;
