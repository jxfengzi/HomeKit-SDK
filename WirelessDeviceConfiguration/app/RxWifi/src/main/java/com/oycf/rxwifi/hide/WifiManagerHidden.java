package com.oycf.rxwifi.hide;

import android.net.wifi.WifiManager;

public class WifiManagerHidden {

    public static final String WIFI_AP_STATE_CHANGED_ACTION = "android.net.wifi.WIFI_AP_STATE_CHANGED";
//    public static final String EXTRA_WIFI_AP_STATE = "wifi_state";

    public static final int WIFI_AP_STATE_DISABLING = 10;
    public static final int WIFI_AP_STATE_DISABLED = 11;
    public static final int WIFI_AP_STATE_ENABLING = 12;
    public static final int WIFI_AP_STATE_ENABLED = 13;
    public static final int WIFI_AP_STATE_FAILED = 14;

    public static String getString(int state) {
        String value = "undefined";

        switch (state) {
            case WIFI_AP_STATE_DISABLING:
                value = "WIFI_AP_STATE_DISABLING";
                break;

            case WIFI_AP_STATE_DISABLED:
                value = "WIFI_AP_STATE_DISABLED";
                break;

            case WIFI_AP_STATE_ENABLING:
                value = "WIFI_AP_STATE_ENABLING";
                break;

            case WIFI_AP_STATE_ENABLED:
                value = "WIFI_AP_STATE_ENABLED";
                break;

            case WIFI_AP_STATE_FAILED:
                value = "WIFI_AP_STATE_FAILED";
                break;

            case WifiManager.WIFI_STATE_DISABLING:
                value = "WIFI_STATE_DISABLING";
                break;

            case WifiManager.WIFI_STATE_DISABLED:
                value = "WIFI_STATE_DISABLED";
                break;

            case WifiManager.WIFI_STATE_ENABLING:
                value = "WIFI_STATE_ENABLING";
                break;

            case WifiManager.WIFI_STATE_ENABLED:
                value = "WIFI_STATE_ENABLED";
                break;
        }

        return value;
    }
}
