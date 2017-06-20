//
//  AirwatchBridge.java
//  Airwatch Plugin
//
//  Copyright (C) 2016 VMWare AirWatch. All rights reserved.
//  This product is protected by copyright and intellectual property laws in the
//  United States and other countries as well as by international treaties.
//  AirWatch products may be covered by one or more patents listed at
//  http://www.vmware.com/go/patents.
//

package com.airwatch.cordova.sdkplugin;

import android.content.Context;
import android.util.Log;

import com.airwatch.sdk.AirWatchSDKException;
import com.airwatch.sdk.SDKManager;
import com.airwatch.sdk.profile.RestrictionPolicy;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by josephben on 3/8/2016.
 */
public class AirwatchBridge {

    private static final String LOG_TAG = AirwatchBridge.class.getSimpleName();
    private static AirwatchBridge instance = new AirwatchBridge();
    private SDKManager awSDKManager;


    public void initAirwatchSDKManager(final Context context, final AirwatchSDKPlugin.InitializationListener initListener) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    awSDKManager = SDKManager.init(context.getApplicationContext());
                    initListener.initSuccess();
                } catch (AirWatchSDKException awse) {
                    Log.e(LOG_TAG, "Exception initializing AirWatch SDK", awse);
                    initListener.initFailure();
                }
            }
        }).start();
    }

    public SDKManager getSDKManagerInstance() {
        return awSDKManager;
    }

    public static AirwatchBridge getInstance() {
        return instance;
    }

    public boolean isInitialized() throws AirWatchSDKException {
        return (awSDKManager != null);
    }

    // Connection information

    public String getUserName() throws AirWatchSDKException {
        return awSDKManager.getSecureAppInfo().getEnrollmentUsername();
    }

    public String getGroupId() throws AirWatchSDKException {
        return awSDKManager.getGroupId();
    }

    public String getServerName() throws AirWatchSDKException {
        return awSDKManager.getServerName();
    }
    
    // Restrictions methods

    public boolean allowCopyPaste() throws AirWatchSDKException {
        RestrictionPolicy restrictionPolicy = awSDKManager.getRestrictionPolicy();
        return (restrictionPolicy == null) || !restrictionPolicy.preventCopyAndCutActions();
    }

    public boolean isOfflineAllowed() throws AirWatchSDKException {
        RestrictionPolicy restrictionPolicy = awSDKManager.getRestrictionPolicy();
        return (restrictionPolicy == null) || restrictionPolicy.allowOfflineMode();
    }

    public boolean restrictDocumentToApps() throws AirWatchSDKException {
        return false;
    }

    public List<String> allowedApplications() throws AirWatchSDKException {
        return new ArrayList<String>();
    }

    // Custom settings

    public String getCustomSettings() throws AirWatchSDKException {
        return awSDKManager.getCustomSettings();
    }

    // Uncategorized

    public boolean isCompliant() throws AirWatchSDKException {
        return awSDKManager.isCompliant();
    }

    public boolean isCompromised() throws AirWatchSDKException {
        return awSDKManager.isCompromised();
    }

}
