#import "AWSDKPlugin.h"
#import "AWSDKBridge.h"

static NSString * const CALLBACK_SCHEME = @"awsdkcallback";

@interface AWSDKPlugin ()

@property (strong, nonatomic) NSString *persistedCallbackId;
@property (strong, nonatomic) AWSDKBridge *bridge;

- (void) sendEvent: (NSString *) eventName;

- (void) sendEvent: (NSString *) eventName
    withDictionary: (NSDictionary *) eventData;

@end

@implementation AWSDKPlugin

- (void) pluginInitialize {
    self.bridge = [AWSDKBridge sharedInstance];
    self.bridge.bridgeDelegate = self;
    [self.bridge startAirwatchSDK];
}

- (void) setPersistentCallback: (CDVInvokedUrlCommand *) command {
    self.persistedCallbackId = [command callbackId];
}

- (void) allowCopyPaste: (CDVInvokedUrlCommand *) command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                        messageAsBool: [self.bridge allowCopyPaste]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) allowOffline: (CDVInvokedUrlCommand *) command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                        messageAsBool: [self.bridge allowOffline]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) customSettings: (CDVInvokedUrlCommand *) command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsString: [self.bridge customSettings]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}


- (void) restrictDocumentToApps: (CDVInvokedUrlCommand *) command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                        messageAsBool: [self.bridge restrictDocumentToApps]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) allowedApplications: (CDVInvokedUrlCommand *) command {
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                       messageAsArray: [self.bridge allowedApplications]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) groupId: (CDVInvokedUrlCommand *) command {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                       messageAsString: [self.bridge groupId]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) username: (CDVInvokedUrlCommand *) command {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsString: [self.bridge username]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) serverName: (CDVInvokedUrlCommand *) command {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                      messageAsString: [self.bridge serverName]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) isCompliant: (CDVInvokedUrlCommand *) command {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                        messageAsBool: [self.bridge isCompliant]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

- (void) isCompromised: (CDVInvokedUrlCommand *) command {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                        messageAsBool: [self.bridge isCompromised]];

    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: [command callbackId]];
}

#pragma mark AWSDKBridgeDelegateMethods

- (void) initSuccess {
    [self sendEvent: @"initSuccess"];
}

- (void) initFailure {
    [self sendEvent: @"initFailure"];
}

- (void) wipe {
    [self sendEvent: @"wipe"];
}

- (void) lock {
    [self sendEvent: @"lock"];
}

- (void) unlock {
    [self sendEvent: @"unlock"];
}

- (void) stopNetworkActivity: (AWNetworkActivityStatus) networkActivityStatus {
    [self sendEvent: @"stopNetworkActivity"
     withDictionary: @{@"status" : @(networkActivityStatus)}];
}

- (void) resumeNetworkActivity {
    [self sendEvent: @"resumeNetworkActivity"];
}

- (void) sendEvent: (NSString *) eventName {
    [self sendEvent: eventName
     withDictionary: @{}];
}

- (void) sendEvent: (NSString *) eventName
    withDictionary: (NSDictionary *) eventData {

    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus: CDVCommandStatus_OK
                                                  messageAsDictionary: @{@"eventName" : eventName,
                                                                         @"eventData" : eventData}];

    [pluginResult setKeepCallbackAsBool: YES]; // so Cordova keeps this callback ID alive for future use
    [self.commandDelegate sendPluginResult: pluginResult
                                callbackId: self.persistedCallbackId];
    
}


@end
