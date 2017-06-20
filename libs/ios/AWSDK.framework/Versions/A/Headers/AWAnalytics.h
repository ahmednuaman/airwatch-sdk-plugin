
/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */

/*! \file AWAnalytics.h */

#import <Foundation/Foundation.h>
#if	TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif
#import "AWMacro.h"

/**
 @enum  AWAnalyticsEvent
 @brief Valid event type.
 */
typedef enum
{
	AWAnalyticsCustomEvent = 0,     /**< Signals a custom event has occured */
	AWAnalyticsSessionStarted,      /**< Signals the start of an AWAnalytics Session */
	AWAnalyticsSessionEnded,        /**< Signals the end of an AWAnalytics Session */
	AWAnalyticsViewDidAppear,       /**< Signals that a view appeared */
	AWAnalyticsViewDidDisappear     /**< Signals that a view has disappeared */
}
AWAnalyticsEvent;

/**
 @enum  valueTypeEnum
 @brief Valid event values.
 */
typedef enum
{
    AWAnalyticsValueNone = 0,   /**< Use when there is no value associated with an event */
    AWAnalyticsValueInteger,    /**< Use when the value associated with an event is an integer */
    AWAnalyticsValueLong,       /**< Use when the value associated with an event is a long */
    AWAnalyticsValueString      /**< Use when the value associated with an event is a long */
}
AWAnaltyicsEventValueType;

/**
 @brief		Analytics for an application.
 @details	Track useful statistical data concerning your application.
 @version 5.9.3.3
 */
@interface AWAnalytics : NSObject

@property (nonatomic, assign) BOOL enabled;     /**< Boolean used to represent the state of the AWAnalytics module */

/**
 @brief     Disable the AW_AppSession(Start/End) from logging.
 @details   By setting disableAppSessionLog, AW_AppSessionStart and AW_AppSessionEnd is disabled when the app enters to and/or from background, or if recordEvent:eventName:eventValue:valueType: is called.
 */
@property (nonatomic, assign) BOOL disableAppSessionLog;

/** 
 The bundleVersion object will contain the value from "CFBundleShortVersionString" out of the Info.plist by default and can be overridden
 if desired.
 */
@property (nonatomic, strong) NSString *bundleVersion;


/** 
 The bundleName object will contain the value from "CFBundleName" out of the Info.plist by default and can be overridden
 if desired.
 */
@property (nonatomic, strong) NSString *bundleName;


/** 
 Returns the singleton Instance of the Analytics class.
 Method should be called when you need to access an instantiated analytics singleton.
 @return A shared AWAnalytics singleton object.
 */
+ (AWAnalytics*)mAnalytics;


/**
 Records an analytics event.
 
 @param event The type of event.
 @param name The name of the event.
 @param eventValue The value associated with the event.
 @param valueType The type of value being recorded.
 */
- (void)recordEvent:(AWAnalyticsEvent)event
          eventName:(NSString *)name
         eventValue:(NSString *)eventValue
          valueType:(AWAnaltyicsEventValueType)value;

@end