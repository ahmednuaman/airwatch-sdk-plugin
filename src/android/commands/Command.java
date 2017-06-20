package com.airwatch.cordova.sdkplugin.commands;

import com.airwatch.cordova.sdkplugin.AirwatchBridge;
import com.airwatch.sdk.AirWatchSDKException;

import org.apache.cordova.CallbackContext;
import org.json.JSONArray;

/**
 * Created by josephben on 1/30/2017.
 */

public interface Command {

    String GROUP_ID="groupId";
    String USERNAME="username";
    String CUSTOM_SETTINGS="customSettings";
    String SERVER_NAME="serverName";
    String ALLOW_COPY_PASTE="allowCopyPaste";

    void execute(CallbackContext callbackContext, JSONArray args, AirwatchBridge bridge) throws AirWatchSDKException;
}
