//
//  AWContentController.h
//  AWSDKCore
//
/*
 Copyright © 2014 AirWatch, LLC. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//
/*!
 @header AWContentController.h
 AWContentController is used to retrieve and manipulate AirWatch managed content.
 
 @language objc
 @copyright Copyright 2012 AirWatch LLC. All rights reserved.<p>
 Unless required by applicable law, this Software Development Kit and sample code is distributed on
 an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. AirWatch
 expressly disclaims any and all liability resulting from User’s use of this Software Development
 Kit. Any modification made to the SDK must have written approval by AirWatch.</p>
 @version 5.2
 */

#import <Foundation/Foundation.h>

#import <AWSDK/AWMacro.h>

extern NSString *const AWContentCheckOutFailureCheckedOutByUserKey;
extern NSString *const AWContentDiscardCheckOutFailureCheckedOutByUserKey;
extern NSString *const AWUserRepositoryAdditionConflictValueKey;

@class AWHTTPRequestOperation;
@class AWNetworkOperation;
@class AWURLConnectionOperation;
@class AWContentController;
@class AWContentEntity;
@class AWContentVersion;
@class AWSession;
@class AWEnrollmentAccount;
@class AWContentFolder;
@class AWRepositoryQuotaInfo;
@class AWContentShareInfo;
@class AWContentComment;
@class AWContentCommentDetails;
@class AWContentFolderShareDetails;
@class AWContentFolderCollaboratorInfo;

/** 
 @enum AWContentStatus
 @brief Enumeration that defines content statuses.
 @constant AWContentStatusUnknown Content status Unknown.
 @constant AWContentStatusInstalled	Content status Installed.
 @constant AWContentStatusUninstalled Content status UnInstalled.
 @constant AWContentStatusViewed Content status Viewed.
 */
enum
{
    AWContentStatusUnknown = 0,
    AWContentStatusInstalled = 1,
    AWContentStatusUninstalled = 2,
    AWContentStatusViewed = 3
};
typedef NSInteger AWContentStatus;

/**
 @brief		The delegate of a `AWContentController`.
 @version 5.2
 */
@protocol AWContentControllerDelegate <NSObject>

@optional

/**
 AWContentControllerDelegate manage to notify the status and data of different operation of AWContentController like received categories, received available content, update content status and update content, search content, received forced content, received content.
  
 Retrieves all the categories, only on AirWatch 5.17+.
 */
- (void)fetchCategoryTree:(AWEnrollmentAccount *)enrollmentAccount;

/**
 Tells the delegate the content controller has received categories.
 
 @brief This method is notified on successfully calling  \link AWContentController::fetchCategories:parentCategoryIdentifier:all: fetchCategories:parentCategoryIdentifier:all: \endlink and \link AWContentController::fetchCategoryTree: fetchCategoryTree\endlink methods and receivesCategories in NSArray object.
 @param contentController The content controller that fetched categories.
 @param categories The categories that were retrieved in NSArray object.
 */
- (void)contentController:(AWContentController *)contentController receivedCategories:(NSArray *)categories;

/** Notifies the delegate of an error while retrieving categories.
 @brief This method is notified on failing to call  \link AWContentController::fetchCategories:parentCategoryIdentifier:all: fetchCategories\endlink and \link AWContentController::fetchCategoryTree: fetchCategoryTree\endlink methods and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing a failure while retrieving categories.
 */
- (void)contentController:(AWContentController *)contentController failedToReceiveCategories:(NSError *)error;

/** Tells the delegate the content controller has received available content.
 @brief This method is notified on successfully calling  \link AWContentController::fetchAvailableContent: fetchAvailableContent\endlink and \link AWContentController::fetchAllAvailableContent:parentCategoryIdentifier: fetchAllAvailableContent\endlink methods and receivesCategories in NSArray object.
 @param contentController The responsible content controller.
 @param availableContent The retrieved content entities in NSArray object.
 */
- (void)contentController:(AWContentController *)contentController receievedAvailableContent:(NSArray *)availableContent;

/** Notifies the delegate of an error while retrieving available content. 
 @brief This method is notified on failing to call \link AWContentController::fetchAvailableContent: fetchAvailableContent\endlink and \link AWContentController::fetchAllAvailableContent:parentCategoryIdentifier: fetchAllAvailableContent\endlink methods and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing the cause of failure.
 */
- (void)contentController:(AWContentController *)contentController failedToReceiveAvailableContent:(NSError *)error;

/** Tells the delegate the content controller has updated a content entity's status.  
 @brief This method is notified on successfully calling \link AWContentController::updateContent:account:status updateContent\endlink method.
 @param contentController The responsible content controller.
 @param content The updated content entity.
 */
- (void)contentController:(AWContentController *)contentController updatedContentStatus:(AWContentEntity *)content;

/** Notifies the delegate of an error while updating a content status.
 @brief This method is notified on failing to call \link AWContentController::updateContent:account:status updateContent\endlink method and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing the cause of failure.
 */
- (void)contentController:(AWContentController *)contentController failedToUpdateContentStatus:(AWContentEntity *)content error:(NSError *)error;

/** Tells the delegate the content controller has received an array of content updates. 
 @brief This method is notified on successfully calling \link AWContentController::fetchContentUpdate: fetchContentUpdate\endlink method and receivesContentUpdate in NSArray object.
 @param contentController The responsible content controller.
 @param content An array of content updates.
 */
- (void)contentController:(AWContentController *)contentController receivedContentUpdate:(NSArray *)content;

/** Notifies the delegate of an error while retrieving content updates.
 @brief This method is notified on failing to call \link AWContentController::fetchContentUpdate: fetchContentUpdate\endlink method and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing the cause of failure.
 */
- (void)contentController:(AWContentController *)contentController failedToReceiveContentUpdates:(NSError *)error;

/** Tells the delegate the content controller has received forced content. 
 @brief This method is notified on successfully calling \link AWContentController::fetchForcedContent: fetchForcedContent\endlink method and get receivedForcedContent in NSArray object.
 @param contentController The responsible content controller.
 @param content An array of `AWContentEntity` that are set as being forced.
 */
- (void)contentController:(AWContentController *)contentController receivedForcedContent:(NSArray *)content;

/** Notifies the delegate of an error while retrieving forced content.
 @brief This method is notified on failing to call \link AWContentController::fetchForcedContent: fetchForcedContent\endlink method and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing the cause of failure.
 */
- (void)contentController:(AWContentController *)contentController failedToReceiveForcedContent:(NSError *)error;

/** Tells the delegate the content controller has recieved content.  
 @brief This method is notified on successfully calling \link AWContentController::fetchContent:withIdentifiers: fetchContent:withIdentifiers: \endlink method and get contentEntity in NSArray object. 
 @param contentController The responsible content controller.
 @param contentEntities An array of `AWContentEntity`. 
 */
- (void)contentController:(AWContentController *)contentController receivedContent:(NSArray *)contentEntities;

/** Notifies the delegate of an error while retrieving receiveContent.
 @brief This method is notified on failing to call \link AWContentController::fetchContent:withIdentifiers: fetchContent:withIdentifiers: \endlink method and get error in NSError object.
 @param contentController The responsible content controller.
 @param error An error describing the cause of failure.
 */
- (void)contentController:(AWContentController *)contentController failedToReceiveContent:(NSError *)error;

- (void)contentController:(AWContentController *)contentController receivedSearchContent:(NSArray *)contentEntities;


- (void)contentController:(AWContentController *)contentController failedToDownloadContent:(AWContentVersion *)contentVersion withError:(NSError *)error;
- (void)contentController:(AWContentController *)contentController didReceiveResponse:(NSURLResponse *)response forContentDownload:(AWContentVersion*)contentVersion;
- (void)contentController:(AWContentController *)contentController downloadedData:(NSData*)data forContent:(AWContentVersion *)contentVersion;
- (void)contentController:(AWContentController *)contentController didFinishDownloading:(AWContentVersion*)contentVersion;
- (void)contentController:(AWContentController *)contentController invalidateHMACTokenWithError:(NSError *)error;
@end

/**
 @brief		
 @version 5.2
 */
@interface AWContentController : NSObject
{    
@private
    NSOperationQueue *_networkingOperationQueue;
}

/** The currently authenticated enrollment account used for handling authentication challenges. */
@property (nonatomic, strong) AWEnrollmentAccount *authenticatedEnrollmentAccount;

/** An encryption key corresponding witht he currently authenticated enrollment account used for storing/fetching url credentials from the keychain for challenges */
@property (nonatomic, strong) NSData *encryptionKey;

/** The object that acts as the delegate of the receiving content controller. This delegate notify to caller class for different operation. */
@property (nonatomic, unsafe_unretained) id <AWContentControllerDelegate> delegate;

/**
 Creates a content controller with the supplied session.
 
 @param session A session used to authenticate to AirWatch.
 @return A newly initialized content controller.
 */
- (id)initWithSession:(AWSession *)session;

/**
 @brief Use this method to set a block to be executed to determine whether the connection should be able to respond to a protection space's form of authentication, where a protection space represents a server or realm that requires authentication.
 
 @param block A block object to be executed to determine whether the connection should be able to respond to a protection space's form of authentication. The block has a `BOOL` return type and takes two arguments: the URL connection object, and the protection space to authenticate against.
 */
- (void)setAuthenticationAgainstProtectionSpaceBlock:(BOOL (^)(AWURLConnectionOperation *operation, NSURLProtectionSpace *protectionSpace))block;

/**
 @brief Use this method to set a block to be executed when the connection must authenticate a challenge in order to download its request.
 
 @param block A block object to be executed when the connection must authenticate a challenge in order to download its request. The block has no return type and takes two arguments: the URL connection object, and the challenge that must be authenticated.
 */
- (void)setAuthenticationChallengeBlock:(void (^)(AWURLConnectionOperation *operation, NSURLAuthenticationChallenge *challenge))block;

/** 
 Retrieves an enrollment account's content.
 
 @brief By using this method user can fetch available content and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receievedAvailableContent: contentController:receievedAvailableContent:  \endlink delegate method notify and get categories in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveAvailableContent: contentController:failedToReceiveAvailableContent: \endlink delegate method notify and get error in NSError object.
 @param enrollmentAccount The enrollment account of whose content should be retrieved.
 */
- (void)fetchAvailableContent:(AWEnrollmentAccount *)enrollmentAccount;

/**
 Retrieves homeView and homeViewShortcuts.
 @param enrollmentAccount The associated enrollment account.
 */
- (void)fetchHomeViewShortcuts:(AWEnrollmentAccount *)enrollmentAccount
                withCompletion:(void (^)(BOOL success,
                                         NSError *error,
                                         NSMutableDictionary *homeViewShortcutPairs,
                                         NSMutableArray *homeViews))completion;

/**
 Retrieves the categories contained with the category with the identifier of `parentIdentifier`. 
 
 @brief  By using this method user can fetch available content and onSuccessfully fetching 
 \link AWContentControllerDelegate::contentController:receivedCategories: contentController:receivedCategories:  \endlink delegate method notify and get categories in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveCategories: contentController:failedToReceiveCategories: \endlink delegate method notify and get error in NSError object.
 @param parentIdentifier The parent identifier of the category to fetch. If 0 is supplied, the root categories will be retrieved.
 */
- (void)fetchCategories:(AWEnrollmentAccount *)enrollmentAccount parentCategoryIdentifier:(NSInteger)parentIdentifier all:(BOOL)all;

/**
 Retrieves all the categories, only on AirWatch 5.17+
 
 @brief By using this method user can fetch available content and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receivedCategories: contentController:receivedCategories:  \endlink delegate method notify and get categories in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveCategories: contentController:failedToReceiveCategories: \endlink delegate method notify and get error in NSError object.
 */
- (void)fetchCategoryTree:(AWEnrollmentAccount *)enrollmentAccount;

/**
 Updates the status of a content entity.
 
 @brief By using this method user can update content of user account and onSuccessfully updating  \link AWContentControllerDelegate::contentController:content: contentController:content: \endlink delegate method notify . On failing to updating user account \link AWContentControllerDelegate::contentController:failedToUpdateContentStatus:error: contentController:failedToUpdateContentStatus:error: \endlink delegate method notify.
 @param content The content entity to be updated.
 @param account The enrollment account of whose content should be updated.
 @param status The new status of the content entity.
 */
- (void)updateContent:(AWContentEntity *)content account:(AWEnrollmentAccount *)account status:(AWContentStatus)status;

/**
 Retrieves an enrollment account's available content updates.
 
 @brief By using this method user can fetch updated content of Airwatch enrollmented account,  and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receivedContentUpdate: contentController:receivedContentUpdate: \endlink delegate method notify and get updated content in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveContentUpdates: contentController:failedToReceiveContentUpdates: \endlink delegate method notify and get error in NSError object.
 @param enrollmentAccount The enrollment account of whose content updates should be retrieved.
 */
- (void)fetchContentUpdate:(AWEnrollmentAccount *)enrollmentAccount;

/**
 Retrieves all forced content. 
 
 @brief By using this method user can fetch forced content, and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receivedForcedContent: contentController:receivedForcedContent: \endlink delegate method notify and get categories in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveForcedContent:  contentController:failedToReceiveForcedContent: \endlink delegate method notify and get error in NSError object.
 @param enrollmentAccount The associated enrollment account.
 */
- (void)fetchForcedContent:(AWEnrollmentAccount *)enrollmentAccount;

/**
 Retreives all available content within a specified category.
 
 @brief By using this method user can fetch all available content, and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receievedAvailableContent: contentController:receievedAvailableContent: \endlink delegate method notify and get available content in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveAvailableContent:  contentController:failedToReceiveAvailableContent: \endlink delegate method notify and get error in NSError object.
 @param enrollmentAccount The enrollment account associated with the content.
 @param parentIdentifier The top-most category identifier to get content from.
 */
- (void)fetchAllAvailableContent:(AWEnrollmentAccount *)enrollmentAccount parentCategoryIdentifier:(NSInteger)parentIdentifier;

/**
 Retreives a content entity for every element in identifiers.
 
 @brief By using this method user can fetch all available content, and onSuccessfully fetching \link AWContentControllerDelegate::contentController:receivedContent: contentController:receivedContent: \endlink delegate method notify and get available content entity in NSArray object. On failing to fetching category \link AWContentControllerDelegate::contentController:failedToReceiveContent:  contentController:failedToReceiveContent: \endlink delegate method notify and get error in NSError object.
 @param enrollmentAccount The enrollment account associated with the content.
 @param identifiers An array of content identifiers.
 */
- (void)fetchContent:(AWEnrollmentAccount *)enrollmentAccount withIdentifiers:(NSArray *)identifiers;

/**
 Searches the server for available content using the given search query.
 
 @brief By using this method user can fetch searchContent as per the query, and on successfully fetching data \link AWContentControllerDelegate::contentController:receivedSearchContent:  contentController:receivedSearchContent: \endlink delegate method notify and get searched content in NSArray object.
 @param query The search query to use for the search. 
 @param resultStart The index to start retrevial. Result sets will consist of 25 results as of now so start should almost always be a multiple of 25.
 */
- (void)searchContent:(AWEnrollmentAccount *)enrollmentAccount
	  searchQuery:(NSString *)query 
	  resultStart:(NSInteger)start;

/**
 Retrieves all the repository entities
 
 @brief By using this method user can fetch available repositories and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *repositories))completion \endlink block gets notified and get repositories in NSArray object. On failing to fetching repositories \link (void(^)(BOOL success, NSError *error, NSArray *repositories))completion \endlink block gets notified and get error in NSError object.
 */
- (void)fetchRepositoriesWithCompletion:(void(^)(BOOL success, NSError *error, NSArray *repositories))completion;

/**
 Retrieves the quota information for a user's personal repository
 */
- (void)fetchRepositoriesStorageQuotaInfo:(void (^)(BOOL success, NSError *error, AWRepositoryQuotaInfo *quotaInfo))completion;

/**
 Retrieves all the folders of a repository entity
 
 @brief By using this method user can fetch available folders of a repository and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *repositories))completion  \endlink block gets notified and get folders in NSArray object. On failing to fetching folders \link (void(^)(BOOL success, NSError *error, NSArray *repositories))completion \endlink block gets notified and get error in NSError object.
 @param syncRequired Determines if force sync needs to be done.
 */
- (void)fetchFoldersForRepository:(NSInteger)identifier
                        forceSync:(BOOL)syncRequired
                   withCompletion:(void(^)(BOOL success, NSError *error, NSArray *folders))completion;

/**
 Retrieves all the available content of a folder entity
 
 @brief By using this method user can fetch available content of a folder and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *contentEntities))completion  \endlink block gets notified and get content in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *contentEntities))completion \endlink block gets notified and get error in NSError object.
 @param folderId The folder id used to identify the folder.
 @param repositoryId The respository id used to identify the repository.
 */
- (void)fetchAvailableContentForFolder:(NSInteger)folderId
                          inRepository:(NSInteger)repositoryId
                        withCompletion:(void(^)(BOOL success, NSError *error, NSArray *folderEntities, NSArray *contentEntities))completion;

/**
 Retrieves the full tree content under a repository
 
 @brief By using this method user can fetch full tree under a repository and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *contentEntities))completion  \endlink block gets notified and get content in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *contentEntities))completion \endlink block gets notified and get error in NSError object.
 @param repositoryId The respository id used to identify the repository.
 */
- (void)fetchFulltreeForRepository:(NSInteger)identifier
                      syncRequired:(BOOL)syncRequired
                    withCompletion:(void(^)(BOOL success, NSError *error, NSArray *folderEntities, NSArray *contentEntities))completion;

/**
 Retrieves an enrollment account's content.
 
 @brief By using this method user can fetch available content and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion  \endlink block notify and get content entities in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion; \endlink block notify and get error in NSError object.
 @param enrollmentAccount The enrollment account of whose content should be retrieved.
 */
- (void)fetchAvailableContent:(AWEnrollmentAccount *)enrollmentAccount 
               withCompletion:(void(^)(BOOL success, NSError *error, NSArray *availableContent))completion;

/**
 Retrieves the categories contained with the category with the identifier of `parentIdentifier`.
 
 @brief  By using this method user can fetch categories contained within the category with identifier `parentIdentifier` and onSuccessfully fetching
 \link (void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion  \endlink block notify and get categories in NSArray object. On failing to fetching category \link (void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion \endlink block notify and get error in NSError object.
 @param parentIdentifier The parent identifier of the category to fetch. If 0 is supplied, the root categories will be retrieved.
 */
- (void)fetchCategories:(AWEnrollmentAccount *)enrollmentAccount parentCategoryIdentifier:(NSInteger)parentIdentifier all:(BOOL)all
         withCompletion:(void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion;

/**
 Retrieves all the categories, only on AirWatch 5.17+
 
 @brief By using this method user can fetch all categories and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion  \endlink block notify and get categories in NSArray object. On failing to fetching category \link (void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion \endlink block notify and get error in NSError object.
 */
- (void)fetchCategoryTree:(AWEnrollmentAccount *)enrollmentAccount
           withCompletion:(void(^)(BOOL success, NSError *error, NSArray *receivedCategories))completion;

/**
 Updates the status of a content entity.
 
 @brief By using this method user can update content of user account and onSuccessfully updating  \link (void(^)(BOOL success, NSError *error))completion \endlink  block notify . On failing to updating user account \link (void(^)(BOOL success, NSError *error))completion \endlink  block notify.
 @param content The content entity to be updated.
 @param account The enrollment account of whose content should be updated.
 @param status The new status of the content entity.
 */
- (void)updateContent:(AWContentEntity *)content account:(AWEnrollmentAccount *)account status:(AWContentStatus)status
       withCompletion:(void(^)(BOOL success, NSError *error))completion;

/**
 Retrieves an enrollment account's available content updates.
 
 @brief By using this method user can fetch updated content of Airwatch enrollmented account,  and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *content))completion \endlink  block notify and get updated content in NSArray object. On failing to fetch \link (void(^)(BOOL success, NSError *error, NSArray *content))completion \endlink  block notify and get error in NSError object.
 @param enrollmentAccount The enrollment account of whose content updates should be retrieved.
 */
- (void)fetchContentUpdate:(AWEnrollmentAccount *)enrollmentAccount
            withCompletion:(void(^)(BOOL success, NSError *error, NSArray *content))completion;

/**
 Retrieves all forced content.
 
 @brief By using this method user can fetch forced content, and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *content))completion \endlink block notify and get content in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *content))completion \endlink  block notify and get error in NSError object.
 @param enrollmentAccount The associated enrollment account.
 */
- (void)fetchForcedContent:(AWEnrollmentAccount *)enrollmentAccount
            withCompletion:(void(^)(BOOL success, NSError *error, NSArray *content))completion;

/**
 Retreives all available content within a specified category.
 
 @brief By using this method user can fetch all available content, and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion \endlink  block notify and get available content in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion \endlink  block notify and get error in NSError object.
 @param enrollmentAccount The enrollment account associated with the content.
 @param parentIdentifier The top-most category identifier to get content from.
 */
- (void)fetchAllAvailableContent:(AWEnrollmentAccount *)enrollmentAccount parentCategoryIdentifier:(NSInteger)parentIdentifier 
                  withCompletion:(void(^)(BOOL success, NSError *error, NSArray *availableContent))completion;

/**
 Retreives a content entity for every element in identifiers.
 
 @brief By using this method user can fetch all available content, and onSuccessfully fetching \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion \endlink  block notify and get available content entity in NSArray object. On failing to fetching content \link (void(^)(BOOL success, NSError *error, NSArray *availableContent))completion \endlink  block notify and get error in NSError object.
 @param enrollmentAccount The enrollment account associated with the content.
 @param identifiers An array of content identifiers.
 */
- (void)fetchContent:(AWEnrollmentAccount *)enrollmentAccount withIdentifiers:(NSArray *)identifiers
      withCompletion:(void(^)(BOOL success, NSError *error, NSArray *availableContent))completion;

/**
 Searches the server for available content using the given search query.
 
 @brief By using this method user can fetch searchContent as per the query, and on successfully fetching data \link (void(^)(BOOL success, NSError *error, NSArray *searchContent))completion \endlink  block notify and get searched content in NSArray object.
 @param query The search query to use for the search.
 @param resultStart The index to start retrevial. Result sets will consist of 25 results as of now so start should almost always be a multiple of 25.
 */
- (void)searchContent:(AWEnrollmentAccount *)enrollmentAccount
          searchQuery:(NSString *)query
          resultStart:(NSInteger)start
       withCompletion:(void(^)(BOOL success, NSError *error, NSArray *searchContent))completion;

/*!
 @brief Convenient method to mapped out the errors for different response code of each operation
 @param response The response returned from a network operation
 @param operation The network operation for retrieving content
 @return an NSError object with the error domain as decription and error code
 */
- (NSError *)handleServerResponse:(NSURLResponse *)response forOperation:(AWHTTPRequestOperation *)operation;

/*!
 @brief Fetching the SEG key from device services to decrypt secured attachment
 */
- (void)retrieveSEGKeyWithCompletion:(void(^)(BOOL success, NSError *error, NSString *returnedSEGkey))completion;

/*!
 @brief Remove all current network fetching operations and their callbacks 
 */
- (void)removeAllRemoteOperation;

/*!
 @brief Downloads a content version.
 @param contentVersion the content the receiver should download.
 @discussion be sure to implement the informal delgate for downloading content
 contentController:failedToDownloadContent:withError:
 contentController:didReceiveResponse:forContentDownload:
 contentController:downloadedData:forContent:
 contentController:didFinishDownloading:
 */
- (void)downloadContentVersion:(AWContentVersion *)contentVersion;

/*!
    @brief Determines if the receiver can upload personal content.
    @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canUploadPersonalContent;

/*!
 @brief Determines if the receiver can delete personal content.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canDeletePersonalContent;

/*!
 @brief Determines if the receiver can move personal content.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canMovePersonalContent;

/*!
 @brief Determines if the receiver can rename personal content.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canRenamePersonalContent;

- (BOOL)canSharePersonalContent;

/*!
 @brief Determines if the receiver can create personal folders.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canCreatePersonalFolder;

/*!
 @brief Determines if the receiver can rename personal folders.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canRenamePersonalFolder;

/*!
 @brief Determines if the receiver can delete personal folders.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canDeletePersonalFolder;

/*!
 @brief Determines if the receiver can move personal folders.
 @return YES if the operation can be performed, NO otherwise.
 */
- (BOOL)canMovePersonalFolder;

#pragma mark - Personal Folders

/*!
    @brief Creates a folder on the AirWatch Console.
    @param folderName The name of the folder.
    @param repositoryID The identifier of the AWContentRepository where the parent folder is located.
    @param parentFolderID The identifier of the AWContentFolder where the new folder will be
    located.
    @param completion The block to executed when once operation completes.
 */
- (void)createPersonalFolder:(NSString*)folderName
                inRepository:(NSInteger)repositoryID
                parentFolder:(NSInteger)parentFolderID
              withCompletion:(void(^)(BOOL success,
                                      NSError *error,
                                      AWContentFolder *createdFolder))completion;

/*!
 @brief Updates the name of a folder on the AirWatch Console.
 @param folderID The identifier of the parent AWContentFolder.
 @param repositoryID The identifier of the AWContentRepository where the parent folder is located.
 @param newName The name the folder will be given.
 @param completion The block to executed when once operation completes.
 */
- (void)renamePersonalFolder:(NSInteger)folderID
                inRepository:(NSInteger)repositoryID
                    withName:(NSString *)newName
              withCompletion:(void(^)(BOOL success, NSError *error,
                                      AWContentFolder *updatedFolder))completion;

/*!
 @brief Deletes a folder from the AirWatch Console.
 @param folderID The identifier of the AWContentFolder to be deleted.
 @param repositoryID The identifier of the AWContentRepository where the folder is located.
 @param completion The block to executed when once operation completes.
 */
- (void)deletePersonalFolder:(NSInteger)folderID
                inRepository:(NSInteger)repositoryID
              withCompletion:(void(^)(BOOL success, NSError *error))completion;
/*!
 @brief Moves an AWContentFolder to a new folder on the AirWatch Console.
 @param folderID The identifier of the folder to be moved.
 @param repositoryID The identifier of the AWContentRepository where the parent folder is located.
 @param parentFolderID the identifier of another folder where the first folder will be moved to.
 @param completion The block to executed when once operation completes.
 */
- (void)movePersonalFolder:(NSInteger)folderID
              inRepository:(NSInteger)repositoryID
                  toFolder:(NSInteger)parentFolderID
            withCompletion:(void(^)(BOOL success, NSError *error,
                                    AWContentFolder *folder))completion;

#pragma mark - Personal Content Activity Feed

- (void)fetchAllActivityFeedsOfPersonalContentWithOffset:(int)offset
                                       withMaxActivities:(int)maxActivities
                                          withCompletion:(void (^)(BOOL success,
                                                                   NSError *error,
                                                                   NSMutableArray *activityFeedResults))completion;

- (void)fetchActivityBadgeValueswithCompletion:(void (^)(BOOL success,
                                                         NSError *error,
                                                         NSInteger badgeValue,
                                                         NSMutableDictionary *activityTypeBadgeValues))completion;


#pragma mark - Personal Content

/*!
 @brief Uploads personal content to the AirWatch Console.
 @param filename The name of the content to be uploaded.
 @param contentData The data to be uploaded to the server.
 @param folderID The folder where the content will be located.
 @param repositoryID the repository where the content will be located.
 @param completion The block to executed when once operation completes.
 */
- (void)uploadPersonalContent:(NSString *)filename
                  contentData:(NSData *)contentData
                     toFolder:(NSInteger)folderID
                 inRepository:(NSInteger)repositoryID
               withCompletion:(void(^)(BOOL success,
                                       NSError *error,
                                       AWContentEntity *content))completion;
/*!
 @brief Update personal content located on the AirWatch Console.
 @param contentEntityID The identifier of the content to be updated.
 @param contentData The data to be uploaded to the server.
 @param folderID The folder where the content is located.
 @param repositoryID the repository where the content is located.
 @param completion The block to executed when once operation completes.
 */
- (void)updatePersonalContent:(NSInteger)contentEntityID
                  contentData:(NSData *)contentData
                     toFolder:(NSInteger)folderID
                 inRepository:(NSInteger)repositoryID
               withCompletion:(void(^)(BOOL
                                       success,
                                       NSError *error,
                                       AWContentEntity *content))completion;

/*!
 @brief Delete personal content located on the AirWatch Console.
 @param contentEntityID The identifier of the content to be deleted.
 @param folderID The folder where the content is located.
 @param repositoryID the repository where the content is located.
 @param completion The block to executed when once operation completes.
 */
- (void)deletePersonalContent:(NSInteger)contentEntityID
                   fromFolder:(NSInteger)folderID
                 inRepository:(NSInteger)repositoryID
               withCompletion:(void(^)(BOOL success, NSError *error))completion;

/*!
 @brief Retrieve an array of AWContentVersions for content.
 @param contentEntityID The identifier of the content to retrieve revisions for.
 @param folderID The folder where the content is located.
 @param repositoryID the repository where the content is located.
 @param completion The block to executed when once operation completes.
 */
- (void)revisionListForPersonalContent:(NSInteger)contentEntityID
                              inFolder:(NSInteger)folderID
                          inRepository:(NSInteger)repositoryID
                        withCompletion:(void(^)(BOOL success,
                                                NSError *error, NSArray *contentVersions))completion;

/*!
 @brief Move content to a specific folder.
 @param contentEntityID The identifier of the content to move.
 @param repositoryID the repository where the content is located.
 @param folderID The folder to move the content to.
 @param completion The block to executed when once operation completes.
 */
- (void)movePersonalContent:(NSInteger)contentEntityID
              inRespository:(NSInteger)repositoryID
                   toFolder:(NSInteger)folderID
             withCompletion:(void(^)(BOOL success,
                                     NSError *error,
                                     AWContentEntity *content))completion;

/*!
 @brief Rename content located on the AirWatch Console.
 @param contentEntityID The identifier of the content to rename.
 @param repositoryID the repository where the content is located.
 @param filename The string used to rename the content.
 @param completion The block to executed when once operation completes.
 */
- (void)renamePersonalContent:(NSInteger)contentEntityID
                 inRepository:(NSInteger)repositoryID
                         name:(NSString *)filename
               withCompletion:(void (^)(BOOL success,
                                        NSError *error,
                                        AWContentEntity *content))completion;

- (void)performContentShareInfoOperationForContent:(NSInteger)contentEntityID
                                      inRepository:(NSInteger)repositoryID
                                          inFolder:(NSInteger)folderID
                                      isGetRequest:(BOOL)isGetRequest
                              withContentShareInfo:(AWContentShareInfo *)contentShareInfo
                                      withPassword:(NSString *)contentLinkPassword
                                    withCompletion:(void (^)(BOOL success,
                                                             NSError *error,
                                                             AWContentShareInfo *contentShareInfo))completion;

- (void)performRequestForFolderShareOperationWithFolder:(NSInteger)folderID
                                           inRepository:(NSInteger)repositoryID
                                            requestType:(NSString *)requestType
                                   withContentShareInfo:(AWContentFolderShareDetails *)folderShareDetails
                                         withCompletion:(void (^)(BOOL success,
                                                                  NSError *error,
                                                                  AWContentFolderShareDetails *sharedFolderDetails))completion;
- (void)performUnshareFolderShareOperationForFolder:(NSInteger)folderID
                                       inRepository:(NSInteger)repositoryID
                                     withCompletion:(void (^)(BOOL success,
                                                              NSError *error,
                                                              AWContentFolderShareDetails *sharedFolderDetails))completion;
- (void)performDeleteCollaboratorOperationForFolder:(NSInteger)folderID
                                       inRepository:(NSInteger)repositoryID
                                   withCollaborator:(AWContentFolderCollaboratorInfo *)collaboratorInfo
                                     withCompletion:(void (^)(BOOL success,
                                                              NSError *error,
                                                              AWContentFolderShareDetails *sharedFolderDetails))completion;

- (void)performUserSearchBasedOnSearchString:(NSString *)userSearchText
                              withCompletion:(void (^)(BOOL success,NSError *error,NSMutableArray *userDetails, NSString *returnedSearchString))completion;
/*!
 @brief Update metadata of content located on the AirWatch Console.
 @param contentEntityID The identifier of the content to update.
 @param repositoryID The repository where the content is located.
 @param folderID The folder where the content is located.
 @param subject The string used to update the subject of the content.
 @param description The string used to update the comments/description of the content.
 @param notes The string used to update the notes of the content.
 @param completion The block to executed when once operation completes.
 */
- (void)updateMetadataForPersonalContent:(NSInteger)contentEntityID
                            inRepository:(NSInteger)repositoryID
                                inFolder:(NSInteger)folderID
                             withSubject:(NSString *)subject
                             description:(NSString *)description
                                   notes:(NSString *)notes
                          withCompletion:(void (^)(BOOL success,
                                                   NSError *error,
                                                   AWContentEntity *content))completion;

#pragma mark - Content Check Out / Check In

/*!
 @brief Check out the content
 @param contentEntityID The identifier of the content to check out.
 @param repositoryID The repository where the content is located.
 @param folderID The folder where the content is located.
 @param completion The block to executed when once operation completes.
 */
- (void)checkOutContent:(NSInteger)contentEntityID
           inRepository:(NSInteger)repositoryID
               inFolder:(NSInteger)folderID
         withCompletion:(void (^)(BOOL success,
								  AWContentEntity *entity,
                                  NSError *error))completion;

/*!
 @brief Discard check out of content
 @param contentEntityID The identifier of the content to check out.
 @param repositoryID The repository where the content is located.
 @param folderID The folder where the content is located.
 @param completion The block to executed when once operation completes.
 */
- (void)discardCheckOutOfEntity:(NSInteger)contentEntityID
				   inRepository:(NSInteger)repositoryID
					   inFolder:(NSInteger)folderID
				 withCompletion:(void (^)(BOOL success,
										  NSError *error))completion;

- (void)fetchCommentsForEntity:(NSInteger)entityID
                    withFolder:(NSInteger)folderID
                withRepository:(NSInteger)repositoryID
                    withOffset:(NSInteger)offset
          withMaxCommentsLimit:(NSInteger)maxComments
                withCompletion:(void (^)(BOOL success, NSError *error, AWContentComment *contentCommentInfo))completion;

- (void)postCommentForEntity:(NSInteger)entityID
                  withFolder:(NSInteger)folderID
              withRepository:(NSInteger)repositoryID
          withContentComment:(NSString *)postedComment
              withCompletion:(void (^)(BOOL success, NSError *error, AWContentComment *contentCommentInfo))completion;

- (void)deleteCommentForEntity:(NSInteger)entityID
                  withFolder:(NSInteger)folderID
              withRepository:(NSInteger)repositoryID
                 withCommentID:(NSInteger)commentID
              withCompletion:(void (^)(BOOL success, NSError *error, AWContentComment *contentCommentInfo))completion;

@end
