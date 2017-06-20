
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! @file AWCommandManager.h */

#import <Foundation/Foundation.h>
#import "AWProfile.h"
#import "AWCommand.h"
#import "AWCommandResponse.h"

/** @name AWCommandCompletion */
//@{
/* A callback block used to return success/failure of request
 //@return success : success or failure of the operation
 //@return error: details of error in case of failure of operation
 **/
typedef void (^AWCommandCompletion)(BOOL success, NSError *error);
//@}

@class AWCommandManager;

/**
 @brief		The delegate of a `AWCommandManager`.
 @version 5.9.3.3
 */
@protocol AWCommandManagerDelegate <NSObject>

@required
/**
 *  This will test to see if your handler object is of the correct type to execute an incoming command request.
 *
 *  @param commandType A Command type of AWCommandTypes.
 *
 *  @return Returns the result of the delegate executing the command.
 */
- (BOOL)canHandleCommandType:(AWCommandType)commandType;


/*!
 @method
 @param command An AWCommand from the console to be processed by the delegate.
 @return Returns an AWCommandResponse object based on the execution status of the command.
 */
- (AWCommandResponse*)responseForCommand:(AWCommand *)command;

@optional

/**
 *  Notifies the delegate that the command processor failed to process a command.
 *
 *  @param processor The command processor.
 *  @param error Details of the error
 */
- (void)commandManager:(AWCommandManager *)proccessor failedWithError:(NSError *)error;

/**
 *  Notifies the delegate of an empty command queue. There's no or no more command to process.
 *
 *  @param processor The command processor.
 *
 */
- (void)commandManagerFinishedReceivingCommands:(AWCommandManager *)processor;

/**
 *  Notifies the delegate of the start of command processing.
 *
 *  @param processor The command processor.
 *
 */
- (void)commandManagerStartedReceivingCommands:(AWCommandManager *)processor;

@end

extern NSString *const AWNotificationCommandManagerInstalledNewProfile;
extern NSString *const AWNotificationCommandManagerRemovedApplicationProfiles;



/**
 @brief		Command manager is used to query the command queue.
 @details	Manager for the command processor. Allows a device to query the command queue for commands to execute.
 @version 5.9.3.3
 */
@interface AWCommandManager : NSObject <AWCommandManagerDelegate>

/**
 *  The object that acts as the delegate of the receiving command processor.
 *
 *  The delegate must adopt the AWCommandManagerDelegate protocol. The delegate object is not retained.
 */
@property (nonatomic, unsafe_unretained) id <AWCommandManagerDelegate>delegate;

/**
 *  Returns the singleton instance of the CommandManager class.
 *
 *  Method should be called when you need to access an instantiated CommandManager singleton.
 *
 *  @return the shared AWCommandManager object instantiated in the singleton.
 */
+ (AWCommandManager *)sharedManager;

/**
 *  This will register a handler object with the CommandManager to be used when an incoming command is to be processed.
 *
 *  @param handler A handler that can process a command and responds to the AWCommandManagerDelegate protocols.
 *
 */
- (void)registerForCommands:(id <AWCommandManagerDelegate>)handler;

/**
 *  This will remove a handler from the CommandManager registration list.
 *
 *  @param handler An object to be removed from the registration list.
 *
 */
- (void)unregisterForCommands:(id <AWCommandManagerDelegate>)handler;

/**
 Starts loading commands from AirWatch with the command processor.
 */
- (void)loadCommands;

/**
 * Request the console to republish any configuration profiles available to the command processor endpoint.
 * @param Completion block with success of requst and/or Error of why it failed.
 */
- (void)requestRepublishingOfConfigurationCommandsWithCompletion:(AWCommandCompletion)completion;

/** Returns the SDK profile that was saved upon the last Install Profile Command
 @return the AWProfile stored locally
 */
- (AWProfile *) sdkProfile;

/** Returns the app profile that was saved upon the last Install Profile Command
 @return the AWProfile stored locally
 */
- (AWProfile *) appProfile;

/**
 This method returns all stored profiles.
 @return an NSArray containing all stored AWProfile objects.
 */
- (NSArray *) allProfiles;

/**
 This method is used to obtain a specific Profile. The method find all profiles that contain a
 payload where the value for PayloadType matches the passed parameter.
 
 @param key NSString used to find specific payloads
 @return    an array of AWProfile objects containing a payload that matches provided key for
            Payload Type
 */
- (NSArray *) profilesWithPayloadType:(NSString*)type;

@end