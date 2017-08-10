package com.oycf.rxwifi.state;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.oycf.rxwifi.hide.WifiManagerHidden;
import com.oycf.rxwifi.reflector.TelephonyManagerReflector;
import com.oycf.rxwifi.reflector.WifiManagerReflector;

public class WifiStateManager {

    private static final String TAG = "WifiStateManager";
    private static WifiStateManager instance = null;
    private static final Object classLock = WifiStateManager.class;
    private boolean saved;
    private boolean wifiEnabled;
    private boolean wifiApEnabled;
    private boolean dataEnabled;
    private boolean saveMobileData;
    private int networkId = -1;
    private WifiManager wfManager;
    private TelephonyManager tpyManger;

    public static WifiStateManager getInstance(Context context) {
        synchronized (classLock) {
            if (instance == null) {
                instance = new WifiStateManager(context);
            }

            return instance;
        }
    }

    private WifiStateManager(Context context) {
        this.wfManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        this.tpyManger = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
    }

    public void save() {
        save(false);
    }

    private void save(boolean saveMobileData) {
        Log.d(TAG, "save");

        wifiEnabled = (wfManager.getWifiState() == WifiManager.WIFI_STATE_ENABLED);
        wifiApEnabled = (WifiManagerReflector.getWifiApState(wfManager) == WifiManagerHidden.WIFI_AP_STATE_ENABLED);

        if (wifiEnabled && wfManager.getConnectionInfo() != null) {
            networkId = wfManager.getConnectionInfo().getNetworkId();
        }

        this.dataEnabled = isMobileEnable();
        this.saveMobileData = saveMobileData;
        this.saved = true;

        Log.d(TAG, "save wifiEnabled:" + wifiEnabled);
        Log.d(TAG, "save wifiApEnabled:" + wifiApEnabled);
        Log.d(TAG, "save mobile data:" + dataEnabled);
    }

    private boolean isMobileEnable() {
        return TelephonyManagerReflector.isMobileEnabled(tpyManger);
    }

    public void restore() {
        Log.d(TAG, "restore");

        if (! saved) {
            return;
        }

        if (wfManager.isWifiEnabled() != wifiEnabled) {
            wfManager.setWifiEnabled(wifiEnabled);
        }
        if (networkId >= 0) {
            wfManager.enableNetwork(networkId, true);
        }

        /**
         * enable mobile data
         */
        if (saveMobileData && dataEnabled && !isMobileEnable()) {
            TelephonyManagerReflector.setMobileEnabled(tpyManger, true);
            Log.d(TAG, "restore data:" + dataEnabled);
        }

        WifiManagerReflector.setWifiApEnabled(wfManager, null, false);

        Log.d(TAG, "restore wifiEnabled:" + wifiEnabled);
        Log.d(TAG, "restore wifiApEnabled:" + wifiApEnabled);

        instance = null;
        wfManager = null;
        tpyManger = null;
    }
}
