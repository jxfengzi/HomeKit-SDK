package com.oycf.rxwifi.reflector;

import android.telephony.TelephonyManager;
import android.util.Log;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class TelephonyManagerReflector {

    private static final String TAG = "TMReflector";

    public static boolean setMobileEnabled(TelephonyManager manager, boolean enabled) {
        boolean ret = false;

        do {
            Class<TelephonyManager> clazz = TelephonyManager.class;
            Method method;

            try {
                method = clazz.getMethod(enabled ? "enableDataConnectivity" : "disableDataConnectivity");
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
                break;
            }

            if (method == null) {
                Log.d(TAG, "method not found: setDataEnabled");
                break;
            }

            method.setAccessible(true);

            try {
                method.invoke(manager);
                ret = true;
            } catch (IllegalAccessException | InvocationTargetException | SecurityException e) {
                e.printStackTrace();
            }
        } while (false);

        return ret;
    }

    public static boolean isMobileEnabled(TelephonyManager manager) {
        boolean enable = false;

        do {
            Class<TelephonyManager> clazz = TelephonyManager.class;
            Method method = null;

            try {
                method = clazz.getMethod("isDataConnectivityPossible");
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
                break;
            }

            if (method == null) {
                Log.d(TAG, "method not found: getWifiApState");
                break;
            }

            method.setAccessible(true);

            try {
                enable = (Boolean) method.invoke(manager);
                Log.d(TAG, "mobile data enable:" + enable);
            } catch (IllegalAccessException | InvocationTargetException e) {
                e.printStackTrace();
            }

        } while (false);

        return enable;
    }
}
