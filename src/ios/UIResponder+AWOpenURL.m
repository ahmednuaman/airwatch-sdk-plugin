//
//  UIResponder+AWOpenURL.m
//
//  Created by Jeff Jones on 8/22/16.
//
// Copyright © 2016 VMware, Inc. All rights reserved.
// This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
// AirWatch products may be covered by one or more patents listed at http:www.vmware.com/go/patents.
//

#import "UIResponder+AWOpenURL.h"
#import <objc/runtime.h>
#import <Foundation/Foundation.h>
#import <AWSDK/AWController.h>

@implementation UIResponder (AWOpenURL)

+ (void) load {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{

        Class class = [UIResponder getAppDelegateClass];
        if (!class) {
            NSLog(@"Swizzle failed, couldn't find AppDelegate");
            return;
        }

        SEL originalSelector = NSSelectorFromString(@"application:openURL:options:");
        SEL swizzledSelector = @selector(swizzled_application:openURL:options:);

        Method originalMethod = class_getInstanceMethod(class, originalSelector);
        Method swizzledMethod = class_getInstanceMethod([self class], swizzledSelector);

        BOOL didAddMethod = class_addMethod(class,
                                            originalSelector,
                                            method_getImplementation(swizzledMethod),
                                            method_getTypeEncoding(swizzledMethod));

        if (didAddMethod) {
            class_replaceMethod(class,
                                swizzledSelector,
                                method_getImplementation(originalMethod),
                                method_getTypeEncoding(originalMethod));
        } else {
            method_exchangeImplementations(originalMethod, swizzledMethod);
        }
    });

}

- (BOOL) swizzled_application: (UIApplication *) app
                      openURL: (NSURL *) url
                      options: (NSDictionary<NSString*, id> *) options {

    NSLog(@"In swizzled openURLViaAirWatch: method for URL: %@", [url absoluteString]);
    return [[AWController clientInstance] handleOpenURL: url
                                        fromApplication: @""] ||   // try this first...
            [self swizzled_application: app
                               openURL: url
                               options: options];                  // then fall back to this
}

+ (Class) getAppDelegateClass {
    unsigned int numberOfClasses = 0;
    Class *classes = objc_copyClassList(&numberOfClasses);
    Class appDelegateClass = nil;
    for (unsigned int i = 0; i < numberOfClasses; ++i) {
        if (class_conformsToProtocol(classes[i], @protocol(UIApplicationDelegate))) {
            appDelegateClass = classes[i];
        }
    }
    return appDelegateClass;
}



@end
