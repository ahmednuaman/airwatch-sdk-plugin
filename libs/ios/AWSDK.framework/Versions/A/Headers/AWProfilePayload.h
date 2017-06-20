
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWProfilePayload.h */

#import <Foundation/Foundation.h>

/**
 @brief		An abstract class that is used to represent profile payloads.
 @details	Abstract class used for subclasses to inherit from. Subclasses must implement all methods.
 @version 5.9.3.3
 */
@interface AWProfilePayload : NSObject
{
	
}

/**
 The designated intializer to create a profile payload.
 
 @param dictionary A dictionary representation of a profile payload.
 @return A newly initialized profile payload.
 */
- (id)initWithDictionary:(NSDictionary *)dictionary;

/**
 The profile type in the format of a string.
 
 @return Profile type text.
 */
+ (NSString *)payloadType;

/**
 The version 2 profile type in the format of a string.
 
 @return Profile type text.
 */
+ (NSString *)payloadTypeV2;

- (NSDictionary *)toDictionary;
- (NSString *)stringFromDictionaryForKey:(NSString *)key;

@end