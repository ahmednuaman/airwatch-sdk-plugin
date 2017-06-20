package com.airwatch.cordova.sdkplugin;

import android.util.Log;

import com.airwatch.cordova.sdkplugin.commands.AllowCopyPasteCommand;
import com.airwatch.cordova.sdkplugin.commands.Command;
import com.airwatch.cordova.sdkplugin.commands.CustomSettingsCommand;
import com.airwatch.cordova.sdkplugin.commands.GroupIdCommand;
import com.airwatch.cordova.sdkplugin.commands.ServerNameCommand;
import com.airwatch.cordova.sdkplugin.commands.UsernameCommand;
import com.airwatch.sdk.AirWatchSDKException;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import org.apache.cordova.*;
import org.apache.cordova.PluginResult.Status;
import org.json.*;

public class AirwatchSDKPlugin extends CordovaPlugin {

    public interface InitializationListener {
        void initSuccess();
        void initFailure();
    }
    
    public static final String LOG_TAG = AirwatchSDKPlugin.class.getSimpleName();

    private CallbackContext persistedContext;
    private AirwatchBridge bridge;
    private Map<String,Command> commandsMap=new HashMap<String, Command>();

    @Override
    public void initialize(CordovaInterface cordova, CordovaWebView webView) {
        super.initialize(cordova, webView);
        bridge = AirwatchBridge.getInstance();
        initializeCommandMap();
    }

    private void initializeCommandMap(){
        commandsMap.put(Command.GROUP_ID,new GroupIdCommand());
        commandsMap.put(Command.USERNAME,new UsernameCommand());
        commandsMap.put(Command.SERVER_NAME,new ServerNameCommand());
        commandsMap.put(Command.ALLOW_COPY_PASTE,new AllowCopyPasteCommand());
        commandsMap.put(Command.CUSTOM_SETTINGS,new CustomSettingsCommand());
    }

    private InitializationListener initListener = new InitializationListener() {
        @Override
        public void initSuccess() {
            sendEvent("initSuccess");
        }

        @Override
        public void initFailure() {
            sendEvent("initFailure");
        }
    };

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {

        Log.w(LOG_TAG, "Entering execute(), action = " + action);

        if ("setPersistentCallback".equals(action)) {
            persistedContext = callbackContext;
            bridge.initAirwatchSDKManager(cordova.getActivity(), initListener);
            return true;
        }

        Command command = commandsMap.get(action);

        if(command == null) {
            return false;
        }
        try {
            command.execute(callbackContext,args,bridge);
        }catch (AirWatchSDKException e){
            sendError(callbackContext,e.toString());
        }
        return true;
    }

    private void sendError(CallbackContext callbackContext,String error) {
        callbackContext.sendPluginResult(new PluginResult(Status.ERROR,error));
    }

    public void sendEvent(String eventName) {
        sendEvent(eventName, null);
    }

    public void sendEvent(String eventName, JSONObject eventData) {
        if (persistedContext == null) {
            Log.w(LOG_TAG, "No persistent context available, event '" + eventName + "' could not be sent to plugin");
            return;
        }
        PluginResult result = null;
        try {
            JSONObject event = new JSONObject();
            event.put("eventName", eventName);
            if (eventData != null) {
                event.put("eventData", eventData);
            }
            result = new PluginResult(Status.OK, event);
        } catch (JSONException je) {
            result = new PluginResult(Status.ERROR, "JSONException marshalling event data: " + je.getMessage());
        } finally {
            result.setKeepCallback(true);
            persistedContext.sendPluginResult(result);
        }
    }
}
