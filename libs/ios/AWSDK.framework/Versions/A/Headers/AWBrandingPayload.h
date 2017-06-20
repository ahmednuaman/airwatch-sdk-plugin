/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWBrandingPayload.h */

#import "AWProfilePayload.h"
#import <UIKit/UIKit.h>

/**
 @brief		Branding payload that is contained in an `AWProfile`.
 @details	A profile payload that represents the branding group of an SDK profile.
 @version 5.9.3.3
 */
@interface AWBrandingPayload : AWProfilePayload


/** A boolean indicating if Branding is enabled. */
@property (nonatomic, readonly) BOOL enableBranding;
@property (nonatomic, readonly) BOOL customBranding;

/** The Organization Name. */
@property (nonatomic, copy, readonly) NSString *organizationName;


#pragma mark - Colors

/** The primary highlight color. */
@property (nonatomic, readonly) UIColor *primaryHighlightColor;
@property (nonatomic, readonly) UIColor *primaryColor;

/** The secondary highlight color. */
@property (nonatomic, readonly) UIColor *secondaryHighlightColor;
@property (nonatomic, readonly) UIColor *secondaryColor;

/** The navigation bar and toolbar color. */
@property (nonatomic, readonly) UIColor *toolbarColor;


#pragma mark - Text Colors

/** The primary text color. */
@property (nonatomic, readonly) UIColor *primaryTextColor;

/** The secondary text color. */
@property (nonatomic, readonly) UIColor *secondaryTextColor;
 
/**
 The login title text color. 
 */
@property (nonatomic, readonly) UIColor *loginTitleTextColor;
/** The tertiary text color. */
@property ( nonatomic, readonly) UIColor *tertiaryTextColor;
/** The toolbar text color. */
@property (nonatomic, readonly) UIColor *toolbarTextColor;


#pragma mark - Background Images

/** The background image for non-retina iPhones & iPod touches. */
@property (nonatomic, readonly) NSURL *iPhoneBackgroundImageURL;

/** The background image for retina iPhones & iPod touches. */
@property (nonatomic, readonly) NSURL *iPhone2xBackgroundImageURL;

@property (nonatomic, readonly) NSURL *iPhone52xBackgroundImageURL;

/** The background image for non-retina iPads. */
@property (nonatomic, readonly) NSURL *iPadBackgroundImageURL;

/** The background image for retina iPads. */
@property (nonatomic, readonly) NSURL *iPad2xBackgroundImageURL;


#pragma mark - Company Logo

/** The company image logo for non-retina iPhones & iPod touches. */
@property (nonatomic, readonly) NSURL *iPhoneCompanyLogoURL;

/** The company image logo for non-retina iPhones & iPod touches. */
@property (nonatomic, readonly) NSURL *iPhone2xCompanyLogoURL;

/** The company image logo for non-retina iPads. */
@property (nonatomic, readonly) NSURL *iPadCompanyLogoURL;

/** The company image logo for non-retina iPads. */
@property (nonatomic, readonly) NSURL *iPad2xCompanyLogoURL;

@end