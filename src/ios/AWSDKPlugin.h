#import <Cordova/CDV.h>
#import "AWSDKBridge.h"

@interface AWSDKPlugin : CDVPlugin <AWSDKBridgeDelegate>

- (void) setPersistentCallback: (CDVInvokedUrlCommand *) command;

// Connection information

- (void) groupId: (CDVInvokedUrlCommand *) command;

- (void) username: (CDVInvokedUrlCommand *) command;

- (void) serverName: (CDVInvokedUrlCommand *) command;

// Restrictions payload

- (void) allowCopyPaste: (CDVInvokedUrlCommand *) command;

- (void) allowOffline: (CDVInvokedUrlCommand *) command;

- (void) restrictDocumentToApps: (CDVInvokedUrlCommand *) command;

- (void) allowedApplications: (CDVInvokedUrlCommand *) command;

// Custom settings payload

- (void) customSettings: (CDVInvokedUrlCommand *) command;

// Uncategorized

- (void) isCompliant: (CDVInvokedUrlCommand *) command;

- (void) isCompromised: (CDVInvokedUrlCommand *) command;

@end
