
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

#import <Foundation/Foundation.h>

/*!
 @enum AWCommandStatus
 @brief A type definition for commands
 
 Details.
 */
typedef enum {
	UNKNOWN = 0,
	ACKNOWLEDGED,
	ERROR,
	COMMANDFORMATERROR,
	IDLE,
	NOTNOW
} AWCommandStatus;

/** 
 *   AWCommandTypes a Singleton class used to hold command types and get their string representations
 * @version 5.9.3.3
 */
@interface AWCommandTypes : NSObject {
	
}

/** 
 *   Return a singleton of AWCommandTypes
 */
+ (AWCommandTypes *)sharedInstance;

/** 
 *  Return a command's status in NSString format
 * 
 *  @param type An AWCommandStatus type to be convert to NSString type name
 */
- (NSString *)commandStatusTypeName:(AWCommandStatus)type;

@end