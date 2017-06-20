//
//  AWPKCS12KeyManager.java
//  Airwatch Plugin
//
//  Copyright (C) 2016 VMWare AirWatch. All rights reserved.
//  This product is protected by copyright and intellectual property laws in the
//  United States and other countries as well as by international treaties.
//  AirWatch products may be covered by one or more patents listed at
//  http://www.vmware.com/go/patents.
//

package com.airwatch.cordova.sdkplugin;

import android.util.Log;

import com.airwatch.bizlib.model.CertificateDefinition;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.Principal;
import java.security.PrivateKey;
import java.security.UnrecoverableEntryException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.util.Collections;
import java.util.Enumeration;

import javax.net.ssl.KeyManager;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.X509KeyManager;

public class AWPKCS12KeyManager implements X509KeyManager {

    public static final String TAG = AWPKCS12KeyManager.class.getSimpleName();

    // The file key manager that contains the certificate described in
    // _certSource.
    private X509KeyManager keyManager;
    private char[]  certPassword;
    private String alias; //need to initialize this
    private byte[][] keys;

    KeyStore keystore;

    public AWPKCS12KeyManager(CertificateDefinition definition) {
        try {
            // Step 1 get cert data as bytes (and Base64-decodes)
            byte[] passedData = definition.getCertificateData();

            certPassword = definition.getPassword().toCharArray();

            // Step 2 Initialize keystore and parse certs
            keys = parseCertificates(CertType.PKCS12, passedData, certPassword);

            // Step 3 Initialize alias
            Enumeration<String> aliases = keystore.aliases();
            if ( aliases.hasMoreElements() ) {
                alias = aliases.nextElement(); // there is only one
            }

            // Step 4: Initialize KeyManager
            KeyManagerFactory oKMF = KeyManagerFactory
                    .getInstance(KeyManagerFactory.getDefaultAlgorithm());
            oKMF.init(keystore, certPassword);
            for (KeyManager oKM : oKMF.getKeyManagers()) {
                if (oKM instanceof X509KeyManager) {
                    keyManager = (X509KeyManager) oKM;
                    break;
                }
            }
        } catch (Exception err) {
            Log.e(TAG, err.getMessage(), err);
        }
    }

    // X509KeyManager
    public X509KeyManager getX509KeyManager() {
        return keyManager;
    }

    /*
     * (non-Javadoc)
     *
     * @see javax.net.ssl.X509KeyManager#chooseClientAlias(java.lang.String[],
     * java.security.Principal[], java.net.Socket)
     *
     * @return Return the preselected alias.
     */
    @Override
    public String chooseClientAlias(String[] keyType, Principal[] issuers,
                                    Socket socket) {
        return alias;
    }

    /*
     * (non-Javadoc)
     *
     * @see javax.net.ssl.X509KeyManager#chooseServerAlias(java.lang.String,
     * java.security.Principal[], java.net.Socket) This method is only required
     * for server application.
     */
    @Override
    public String chooseServerAlias(String keyType, Principal[] issuers,
                                    Socket socket) {
        return null;
    }


    @Override
    public X509Certificate[] getCertificateChain(String alias) {
        return keyManager.getCertificateChain(alias);
    }

    @Override
    public String[] getClientAliases(String keyType, Principal[] issuers) {
        return keyManager.getClientAliases(keyType, issuers);
    }

    @Override
    public String[] getServerAliases(String s, Principal[] principals) {
        return new String[0];
    }

    /*
     * (non-Javadoc)
     *
     * @see javax.net.ssl.X509KeyManager#getServerAliases(java.lang.String,
     * java.security.Principal[]) This method is only required for server
     * application.
     */
    @Override
    public PrivateKey getPrivateKey(String s) {
        return getPrivateKey(this.keystore, certPassword);
    }

    // Byte array indices
    private static final int PUBLIC_KEY_IDX = 0;
    private static final int PRIVATE_KEY_IDX = 1;
    private static final int CERT_CHAIN_IDX = 2;

    public enum CertType {
        PKCS12, X509
    }

    /**
     * Parse the cert data and extract private, public keys and cert chain.
     * Currently supports X509 and PKCS12 certs.
     *
     * @param certType
     * @param certData
     * @param certPassword
     * @throws CertificateException
     * @throws IOException
     * @throws NoSuchAlgorithmException
     * @throws KeyStoreException
     * @throws UnrecoverableEntryException
     */
    private byte[][] parseCertificates(CertType certType, byte[] certData,
                                       char[] certPassword) throws CertificateException,
            KeyStoreException, NoSuchAlgorithmException, IOException,
            UnrecoverableEntryException {
        byte[][] keys = new byte[3][1];

        X509Certificate x509Certificate = null;
        PrivateKey privateKey = null;
        X509Certificate[] certChain = null;

        if (CertType.PKCS12 == certType) {
            keystore = initializePKCS12KeyStore(certData, certPassword);
            x509Certificate = getX509Certificate(keystore);
            privateKey = getPrivateKey(keystore, certPassword);
            certChain = getCertificateChain(keystore, certPassword);
        } else {
            // Assume X509
            ByteArrayInputStream bais = new ByteArrayInputStream(certData);
            x509Certificate = (X509Certificate) CertificateFactory.getInstance(
                    "X509").generateCertificate(bais);
        }
        if (x509Certificate != null) {
            keys[PUBLIC_KEY_IDX] = AWPKCS12KeyManager
                    .convertToBytes(x509Certificate);
        }
        if (privateKey != null) {
            keys[PRIVATE_KEY_IDX] = AWPKCS12KeyManager
                    .convertToBytes(privateKey);
        }
        if (certChain != null) {
            keys[CERT_CHAIN_IDX] = AWPKCS12KeyManager
                    .convertToBytes(certChain);
        }
        return keys;
    }

    /**
     * Initializes and returns PKCS12 keystore loaded with given cert data.
     *
     * @param certData
     * @param certPassword
     * @return
     * @throws KeyStoreException
     * @throws IOException
     * @throws CertificateException
     * @throws NoSuchAlgorithmException
     */
    private KeyStore initializePKCS12KeyStore(byte[] certData,
                                              char[] certPassword) throws KeyStoreException,
            NoSuchAlgorithmException, CertificateException, IOException {
        ByteArrayInputStream bais = null;
        try {
            bais = new ByteArrayInputStream(certData);
            keystore = KeyStore.getInstance("PKCS12");
            keystore.load(bais, certPassword);
            return keystore;
        } catch (Exception err) {
            Log.e(TAG, err.getMessage(), err);
            return null;
        } finally {
            if (bais != null) {
                try {
                    bais.close();
                } catch (IOException e) {
                    // Ignore;
                }
            }
        }
    }

    /**
     * Extract private key from the given keystore.
     *
     * @param ks
     * @param certPassword
     * @return
     * @throws KeyStoreException
     * @throws NoSuchAlgorithmException
     * @throws UnrecoverableKeyException
     */
    private PrivateKey getPrivateKey(KeyStore ks, char[] certPassword) {
        try {
            Enumeration<String> aliases = ks.aliases();
            while (aliases.hasMoreElements()) {
                String alias = aliases.nextElement();
                if (ks.isKeyEntry(alias)) {
                    return (PrivateKey) ks.getKey(alias, certPassword);
                }
            }
        } catch (Exception err) {
            Log.e(TAG, err.getMessage(), err);
        }
        return null;
    }

    /**
     * Extract X509Certificate from given keystore.
     *
     * @param ks
     * @return
     * @throws KeyStoreException
     */
    private X509Certificate getX509Certificate(KeyStore ks)
            throws KeyStoreException {
        Enumeration<String> aliases = ks.aliases();
        while (aliases.hasMoreElements()) {
            String alias = aliases.nextElement();
            if (ks.isCertificateEntry(alias)) {
                return (X509Certificate) ks.getCertificate(alias);
            } else {
                // In case of self-signed certificates, only one alias is
                // returned and it is not associated with a certificate entry.
                // In this case we fetch the certificate directly from the
                // keystore.
                X509Certificate certificate = (X509Certificate) ks
                        .getCertificate(alias);
                if (certificate != null) {
                    return certificate;
                }
            }
        }
        return null;
    }

    /**
     * Extract certificate chain from given keystore
     *
     * @param ks
     * @param certPassword
     * @return
     * @throws KeyStoreException
     * @throws UnrecoverableEntryException
     * @throws NoSuchAlgorithmException
     */
    private X509Certificate[] getCertificateChain(KeyStore ks,
                                                  char[] certPassword) throws KeyStoreException,
            NoSuchAlgorithmException, UnrecoverableEntryException {
        Enumeration<String> aliases = ks.aliases();
        KeyStore.PasswordProtection pp = new KeyStore.PasswordProtection(certPassword);
        for (String alias : Collections.list(aliases)) {
            if (ks.getEntry(alias, pp) instanceof KeyStore.PrivateKeyEntry) {
                java.security.cert.Certificate[] certArray = ks
                        .getCertificateChain(alias);
                if (certArray == null || certArray.length <= 0) {
                    return null;
                }
                if (certArray instanceof X509Certificate[]) {
                    return (X509Certificate[]) certArray;
                } else {
                    X509Certificate[] x509CertArray = new X509Certificate[certArray.length];
                    for (int i = 0; i < certArray.length; i++) {
                        x509CertArray[i] = (X509Certificate) certArray[i];
                    }
                    return x509CertArray;
                }
            }
        }
        return null;
    }

    /**
     * Convenience method to convert a serializable object into a byte array.
     *
     * @param obj object to convert to byte array
     * @return
     * @throws IOException
     */
    public static <T extends Serializable> byte[] convertToBytes(T obj)
            throws IOException {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(obj);
        return baos.toByteArray();
    }

}
