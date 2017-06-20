//
//  AWContentCategory.h
//  AWSDKCore
//
//  Created by AirWatch on 8/9/11.
/*
 Copyright © 2014 AirWatch, LLC. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

/*! \file AWContentCategory.h */

#import <Foundation/Foundation.h>

/**
 @brief		Content management category.
 @details	Represents a category to manage content.
 @version 5.2
 */
@interface AWContentCategory : NSObject
{
    
}

/** @name Configuring a Content Category */
//@{

/** The identifier of the category. */
@property (nonatomic, assign) NSInteger identifier;

/** The identifier of the category's parent category. */
@property (nonatomic, assign) NSInteger parentIdentifier;

/** The display name of the category. */
@property (nonatomic, copy) NSString *name;

/** A boolean indicating whether or not the category has child categories. */
@property (nonatomic, assign) BOOL hasSubCategories;

//@}

@end
