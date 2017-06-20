//
//  AWContentEntity.h
//  AWFileLocker
//
//  Created by AirWatch on 7/19/11.
/*
 Copyright © 2014 AirWatch, LLC. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

/*! \file AWContentEntity.h */

#import <Foundation/Foundation.h>
#import <AWSDK/AWMacro.h>

@class AWContentVersion;

/** 
 @enum AWContentType             Enumeration that defines the content type.
 */

typedef enum {
    
    AWContentTypeExcel,         /**< Content type Excel. */
    AWContentTypeWord,          /**< Content type Word. */
    AWContentTypePowerPoint,    /**< Content type PowerPoint. */
    AWContentTypeNumbers,       /**< Content type Numbers. */
    AWContentTypePages,         /**< Content type Pages. */
    AWContentTypeKeynote,       /**< Content type Keynote. */
    AWContentTypePDF,           /**< Content type PDF. */
    AWContentTypeRTF,           /**< Content type RTF. */
    AWContentTypeHTML,          /**< Content type HTML. */
    AWContentTypeVideo,         /**< Content type Video. */
    AWContentTypeAudio          /**< Content type Audio. */
    
} AWContentType;

/** 
 @enum AWContentDownloadPriority                  Enumeration that defines the download priority.
 */

typedef enum {
    
    AWContentDownloadPriorityLow = 0,   /**<  Download Priority Low */
    AWContentDownloadPriorityMedium,    /**<  Download Priority Medium */
    AWContentDownloadPriorityHigh,      /**<  Download Priority High */
    AWContentDownloadPriorityForce      /**<  Download Priority Force */
    
} AWContentDownloadPriority;

/** 
 @enum AWContentDownloadPriority                    Enumeration that defines the content importance policy.
 */

typedef enum
{    
    AWContentImportancePriorityLow = 0,  /**<  Content importance priority Low. */
    AWContentImportancePriorityMedium,   /**<  Content importance priority Medium. */
    AWContentImportancePriorityHigh      /**<  Content importance priority High. */    
}
AWContentImportancePriority;

/** 
 @enum AWContentDownloadNetwork                    Enumeration that defines the allowed Network type for download.
 */

typedef enum {
    
    AWContentDownloadAllowedNetworkAny = 1,	/**< allowed Any Netwoek for content download. */
    AWContentDownloadAllowedNetworkWiFi,	/**< allowed Wifi Netwoek for content download. */
    AWContentDownloadAllowedNetworkCell		/**<  allowed Cell Netwoek for content download. */
    
} AWContentDownloadNetwork;

/**
 @brief		Content management entity.
 @details	AWContentEntity manage to configure content entity. AWContentEntity is module class which contains content entity.
 @version 5.2
 */
@interface AWContentEntity : NSObject {
    
}

/** @name Configuring a Content Entity */
//@{

/** The identifier of the content entity. */
@property (nonatomic, assign) NSInteger identifier;

/** The identifier of the content entity's folder. */
@property (nonatomic, assign) NSInteger folderIdentifier;

/** The identifier of the content entity's repository. */
@property (nonatomic, assign) NSInteger repositoryIdentifier;

/** The display name. */
@property (nonatomic, copy)   NSString *name;

/** The file extension of the file. */
@property (nonatomic, copy)   NSString *extension;

/** Optional comments describing the content entity. */
@property (nonatomic, copy)   NSString *comments;

/** The MIME type of the file. */
@property (nonatomic, copy)   NSString *MIMEType;

/** The creator of the file. */
@property (nonatomic, copy)   NSString *createdBy;

/** The last date the content entity was created. */
@property (nonatomic, strong) NSDate *createdDate;

/** The last date the content entity was modified. */
@property (nonatomic, strong) NSDate *modifiedDate;

/** A textual representation of the type of file. */
@property (nonatomic, copy)   NSString *type;

/** The content version associated with the content entity. */
@property (nonatomic, strong) AWContentVersion *version;

/** The expiration date of the content entity. */
@property (nonatomic, strong) NSDate *expirationDate;

/** The effective date of the content entity. */
@property (nonatomic, strong) NSDate *effectiveDate;

/** A boolean indicating whether or not the user must have an active network connection to view the content. */
@property (nonatomic, assign) BOOL requireOnlineRead;

/** A boolean indicating whether or not the content is to be force installed. */
@property (nonatomic, assign) BOOL forceDownload;

/** A boolean indicating whether or not the content is required. */
@property (nonatomic, assign) BOOL isRequired;

/** The boolean indicating whether the user can export or not. */
@property (nonatomic, assign) BOOL canExport;

/** The type of network that a device must be on to download the content. */
@property (nonatomic, assign) AWContentDownloadNetwork allowedDownloadNetwork; 

/** The download priority of the content. */
@property (nonatomic, assign) AWContentDownloadPriority downloadPriority;

/** The content priority of the content. */
@property (nonatomic, assign) AWContentImportancePriority contentPriority;

/** The categories that the content entity belongs to. */
@property (nonatomic, strong) NSSet *categories;

/** The boolean indicating whether the user can email or not. */
@property (nonatomic, assign) BOOL canEmail;

/** The boolean indicating whether the user can email or not. */
@property (nonatomic, assign) BOOL canPrint;

/** The boolean indicating whether the user can annotate or not. */
@property (nonatomic, assign) BOOL canAnnotate AW_DEPRECATED_ATTRIBUTE_MESSAGE("6.5 consoles and forward use allowDocumentModification");

/** The boolean indicating whether the user can perform document mondifications (Annotations, Editing, etc.) */
@property (nonatomic, assign) BOOL allowDocumentModification;

/** Determine whether or not content should have watermark overlay. */
@property (nonatomic, assign) BOOL requireWatermark;

/*! The boolean indicating wheter the user can read the content. */
@property (nonatomic, readonly) BOOL hasReadPermission;

/*! The boolean indicating wheter the user can write the content. */
@property (nonatomic, readonly) BOOL hasWritePermission;

/*! The boolean indicating wheter the user can delete the content. */
@property (nonatomic, readonly) BOOL hasDeletePermission;

/*! The boolean indicating wheter the user can view the sharing settings. */
@property (nonatomic, readonly) BOOL hasShareReadPermission;

/*! The boolean indicating wheter the user can edit the sharing settings. */
@property (nonatomic, readonly) BOOL hasShareWritePermission;

/** The user who checked out the content. */
@property (nonatomic, copy)   NSString *checkedOutUser;

/** The user can share. */
@property (nonatomic, assign) BOOL canShareLink;

/** If the link has been shared. */
@property (nonatomic, assign) BOOL isLinkShared;

/** Total number of comments. */
@property (nonatomic, assign) NSInteger totalComments;

/** If the entity has new comments. */
@property (nonatomic, assign) BOOL hasNewComments;

/** If the entity can be moved between repositories. */
@property (nonatomic, assign) BOOL allowRepoExport;

//@}

@end
