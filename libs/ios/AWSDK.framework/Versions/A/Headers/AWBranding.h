
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWBranding.h */

#import <Foundation/Foundation.h>
#import "AWMacro.h"
#import "AWBrandingPayload.h"

/** Notification that is posted immediately after a skin is updated. */
extern NSString *const AWBrandingSkinDidUpdateNotification;

/** 
 @brief		Branding controller used to manipulate brand skins.
 @details	AWBranding is an object that can be used for branding of Content Locker. It takes in a dictionary, which should be a set of settings for a specific brand.
 @version 5.9.3.3
 */
@interface AWBranding : NSObject
{
    
}

/**
 @brief Custom branding source bundle
 @details AWBranding can be set to pull branding information from an included Bundle file other than the app's main bundle. The default is source is from the main bundle of the app. If the source branding bundle is not from the app's main bundle, a custom directory will be created in the app's Document directory to store all the branding resources. To set it back to use the app's main bundle, a nil value or main bundle can be set for this property.
 */
@property (nonatomic, strong) NSBundle *sourceBrandingBundle;

@property (nonatomic, strong) UIFont *font;

/** Brand Intializer. 
 
 @brief AWBranding object made by this function. 
 @param configDictionary The dictionary representation of settings to create a brand.
 @return A newly initialized enrollment account. 
 */
+ (AWBranding *) sharedBranding;
//@}

- (NSString *)title;
- (NSString *)organizationName;

- (UIColor *)loginTitleColor;
- (UIColor *)primaryColor;
- (UIColor *)secondaryColor;
- (UIColor *)tertiaryColor;
- (UIColor *)toolbarColor;

- (UIColor *)primaryTextColorForAuthentication;
- (UIColor *)primaryTextColor;
- (UIColor *)secondaryTextColor;
- (UIColor *)tertiaryTextColor;

/*
 Primary image will first see if something was downloaded into the document's folder, if the file exist then the image from console will be returned. If the Image does not exist it will attempt to get the image from the plist.
 */
- (UIImage *)primaryImage;
- (UIImage *)secondaryImage;

/*
 Order of precedence for defining the background color/image from which may or may not come from console or may or may not be defined in skin.plist. If the console does not specify a color/image and the app's skin.plist does not define color/image, then load AWKit.bundle skin.plist will use the Airwatch's default color.
 1. Console PrimaryImage
 2. Console PrimaryColor
 3. skin.plist PrimaryImage
 4. skin.plist PrimaryColor
 */

// AppWrap only
- (UIColor *)backgroundColor;
- (UIColor *)toolbarColor2;
- (UIColor *)toolbarTextColor;
- (UIColor *)textColor;

/*
 This method returns custom image to be shown in the blocker view (Splash screen that is shown when app comes to foreground from background). The image is expected to be present in app's main bundle with the image name specified in app's skin.plist file. The image names should be present with the following keys:
 AWBlockerViewImageiPhonePortrait:      iPhone Portrait image name
 AWBlockerViewImageiPhoneLandscape:     iPhone Landscape image name
 AWBlockerViewImageiPhone5Portrait:     iPhone5 Portrait image name
 AWBlockerViewImageiPhone5Landscape:    iPhone5 Landscape image name
 AWBlockerViewImageiPadPortrait:        iPad Portrait image name
 AWBlockerViewImageiPadLandscape:       iPad Landscape image name
 
 If the image is not found, then branding same as SDK login UI's are applied.
 
 */
- (UIImage *) blockerViewImage;

/** Desired content mode for the blocker view image */
- (UIViewContentMode)blockerViewImageContentMode;

- (BOOL)usePrimaryImage;
- (BOOL)useSecondaryImage;
- (BOOL)enablePoweredBy;
- (BOOL)customBrandingEnabled;

- (void) parseBrandingInfoFromCommand:(NSDictionary *)brandingDictionary;

/*!
 Persists the branding settings contained in a payload. This must be called
 to set any of the branding attributes.
 @param payload The AWBrandingPayload containing the settings to be persisted.
 */

- (void)synchronizeBrandingFormPayload:(AWBrandingPayload *)payload;

- (void)clearAllBrandingImages;
- (void)clearAllBranding;

@end