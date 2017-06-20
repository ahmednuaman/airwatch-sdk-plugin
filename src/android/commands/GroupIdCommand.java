package com.airwatch.cordova.sdkplugin.commands;

import com.airwatch.cordova.sdkplugin.AirwatchBridge;
import com.airwatch.cordova.sdkplugin.commands.Command;
import com.airwatch.sdk.AirWatchSDKException;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;

/**
 * Created by josephben on 1/30/2017.
 */

public class GroupIdCommand implements Command {
    @Override
    public void execute(CallbackContext callbackContext, JSONArray args, AirwatchBridge bridge) throws AirWatchSDKException {
        String result=bridge.getGroupId();
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, result));
    }
}
