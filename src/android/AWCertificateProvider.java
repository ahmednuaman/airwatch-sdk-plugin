//
//  AWCertificateProvider.java
//  Airwatch Plugin
//
//  Copyright (C) 2016 VMWare AirWatch. All rights reserved.
//  This product is protected by copyright and intellectual property laws in the
//  United States and other countries as well as by international treaties.
//  AirWatch products may be covered by one or more patents listed at
//  http://www.vmware.com/go/patents.
//

package com.airwatch.cordova.sdkplugin;

import android.app.Application;
import android.content.Context;
import android.util.Log;

import com.airwatch.bizlib.model.CertificateDefinition;
import com.airwatch.sdk.AirWatchSDKException;
import com.airwatch.sdk.SDKManager;
import com.airwatch.sdk.profile.ApplicationProfile;
import com.sap.smp.client.android.certificateprovider.CertificateProvider;
import com.sap.smp.client.android.certificateprovider.CertificateProviderException;
import com.sap.smp.client.android.certificateprovider.CertificateProviderListener;

import java.util.List;
import java.util.Map;

import javax.net.ssl.X509KeyManager;

public class AWCertificateProvider implements CertificateProvider {

    private static final String TAG = AWCertificateProvider.class.getSimpleName();

    private static final Object sync = new Object();
    private static final Object threadSync = new Object();
    private static AWPKCS12KeyManager manager;

    private Context context;
    private X509KeyManager cert;
    private SDKManager awSDKManager;
    private boolean serviceError;
    private CertificateProviderListener certificateProviderListener;

    //** This is likely not needed, but works and exists as a safety measure **/
    private static Application getApplicationUsingReflection() throws Exception {
        return (Application) Class.forName("android.app.AppGlobals")
                .getMethod("getInitialApplication").invoke(null, (Object[]) null);
    }

    private Context getContext() {
        return context;
    }

    /** Initialize the AW SDK and then create the certificate manager **/
    private void startSDK(final CertificateProviderListener listener, boolean background) {
        synchronized (sync) {
            if (certificateProviderListener == null && listener != null) {
                certificateProviderListener = listener;
            }

            if (cert != null) {
                if (certificateProviderListener != null) {
                    Log.i(TAG, "ASYNC returning cert " + cert);
                    certificateProviderListener.initializationComplete();
                }
                return;
            }

            // ideally the context was set in setParameters already when this is called
            if (context == null) {
                try {
                    Log.i(TAG, "Getting context from reflection");
                    context = getApplicationUsingReflection();
                } catch (Exception err) {
                    Log.e(TAG, "Could not guess application context");
                }
            }

            if (context != null && manager == null) {
                if (background) {
                    Log.i(TAG, "Starting in Background");
                    new Thread(new SDKStarter(certificateProviderListener)).start();
                } else {
                    Log.i(TAG, "Starting in Foreground");
                    new SDKStarter(certificateProviderListener).run();
                }
            } else {
                Log.e(TAG, "Did not start SDK, either it was already started or we have no context");
            }
        }
    }

    /*****************************************************
     * BEGIN CertificateProvider implementation
     *****************************************************/

     /**
      *     From: "Kinzie, Alan" <alan.kinzie@sap.com>
      *     The initialize function is asynchronous.  It is intended that the certificate provider
      *     will do everything it has to do to get ready to provide a certificate (including showing
      *     UI if it has to).  When it is ready to provide a certificate in a synchronous fashion,
      *     the provider should call certificateProviderListener.initializationComplete(). 
      */
    public void initialize(CertificateProviderListener listener) throws CertificateProviderException {
        Log.i(TAG, "Called initialize");
        startSDK(listener, true);
    }

    // If SDK not initialized do it synchronously
    public X509KeyManager getStoredCertificate() {
        if (cert == null) {
            startSDK(this.certificateProviderListener, false);
        }
        return cert;
    }

    // do nothing
    public void deleteStoredCertificate() {
    }

    /**
     * From: "Sethi, Raman" <ra.sethi@sap.com>
     * getCertificate() is a asynchronous call invoked from our side on CertificateProvider when
     * you initially provision the certificate. I wish the name was more like provisionCertificate()
     * to better indicate that it gets the certificate for the first time.
      */
    public void getCertificate(CertificateProviderListener listener) {
        Log.i(TAG, "Get Certificate");
        startSDK(listener, true);
    }

    // this SHOULD always get called before cert retrieval
    public void setParameters(Map<Object, Object> map) {
        final String contextKey = "androidContext";
        if ( map != null && map.size() > 0 && map.containsKey(contextKey) ) {
            try {
                Context context = (Context)map.get(contextKey);
                context = context;
                startSDK(null, true);
            } catch (ClassCastException cce) {
                Log.e(TAG, "Could not cast to context", cce);
            }
        }
    }

    /*****************************************************
     * END CertificateProvider implementation
     *****************************************************/

    private class SDKStarter implements Runnable {

        private SDKManager awSDKManager;
        private final CertificateProviderListener cpListener;

        public SDKStarter(final CertificateProviderListener listener) {
            this.cpListener = listener;
        }

        @Override
        public void run() {
            synchronized (threadSync) {
                try {
                    if (cert == null) {
                        awSDKManager = SDKManager.init(getContext());

                        ApplicationProfile appProfile = awSDKManager.getApplicationProfile();
                        List<CertificateDefinition> certificates = appProfile.getCertificates();

                        if (certificates.size() > 0) {
                            CertificateDefinition firstCert = certificates.get(0);
                            AWPKCS12KeyManager certMgr = new AWPKCS12KeyManager(firstCert);
                            cert = certMgr.getX509KeyManager();
                        }
                    }

                    if (serviceError)
                        fireErrorCallback(1, "Failure initializing SDK");
                    else
                        fireSuccessCallback();

                } catch (AirWatchSDKException e) {
                    serviceError = true;
                    fireErrorCallback(0, "Exception thrown initializing SDK", e);
                }
            }
        }

        private void fireSuccessCallback() {
            Log.i(TAG, "SDK initialization complete");
            if (cpListener != null)
                cpListener.initializationComplete();
        }

        private void fireErrorCallback(int errorCode, String errorMsg) {
            Log.e(TAG, errorMsg);
            if (cpListener != null)
                cpListener.onGetCertificateFailure(errorCode, errorMsg);
        }

        private void fireErrorCallback(int errorCode, String errorMsg, Throwable t) {
            Log.e(TAG, errorMsg, t);
            if (cpListener != null)
                cpListener.onGetCertificateFailure(errorCode, errorMsg + ": " + t.getMessage());
        }
    }
}
