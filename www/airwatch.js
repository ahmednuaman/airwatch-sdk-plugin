module.exports = {
    setSDKEventListener: function (eventListener) {
        this.sdkEventListener = eventListener;
        cordova.exec(this.eventListenerSuccessCallback.bind(this), this.eventListenerErrorCallback.bind(this), "AirwatchSDK", "setPersistentCallback", []);
    },

    // Connection information

    groupId: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "groupId", []);
    },

    username: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "username", []);
    },

    serverName: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "serverName", []);
    },

    // Restrictions payload

    allowCopyPaste: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "allowCopyPaste", []);
    },

    allowOffline: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "allowOffline", []);
    },

    restrictDocumentToApps: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "restrictDocumentToApps", []);
    },

    allowedApplications: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "allowedApplications", []);
    },

    // Custom settings payload

    customSettings: function (successCallback, errorCallback) {
        cordova.exec(successCallback, errorCallback, "AirwatchSDK", "customSettings", []);
    },

    // Internal

    eventListenerSuccessCallback: function(event) {
        this.sdkEventListener(event.eventName, event.eventData);
    },

    eventListenerErrorCallback: function(error) {
        alert("Event listener error: " + error);
    }

}
