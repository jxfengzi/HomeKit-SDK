package com.oycf.rxwifi.reflector;

import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.support.annotation.Nullable;
import android.util.Log;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class WifiManagerReflector {

    private static final String TAG = "WifiManagerReflector";

    public static boolean setWifiApEnabled(WifiManager manager, WifiConfiguration wifiConfig, boolean enabled) {
        boolean ret = false;

        do {
            Class<WifiManager> clazz = WifiManager.class;
            Method method;

            try {
                Class<?>[] parameterTypes = new Class<?>[2];
                parameterTypes[0] = WifiConfiguration.class;
                parameterTypes[1] = boolean.class;
                method = clazz.getMethod("setWifiApEnabled", parameterTypes);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
                break;
            }

            if (method == null) {
                Log.d(TAG, "method not found: setWifiApEnabled");
                break;
            }

            method.setAccessible(true);

            try {
                ret = (Boolean) method.invoke(manager, wifiConfig, enabled);
            } catch (IllegalAccessException | InvocationTargetException e) {
                e.printStackTrace();
            }
        } while (false);

        return ret;
    }

    public static boolean setWifiApConfiguration(WifiManager manager, WifiConfiguration wifiConfig) {
        boolean ret = false;

        do {
            Class<WifiManager> clazz = WifiManager.class;
            Method method;

            try {
                Class<?>[] parameterTypes = new Class<?>[1];
                parameterTypes[0] = WifiConfiguration.class;
                method = clazz.getMethod("setWifiApConfiguration", parameterTypes);
            } catch (NoSuchMethodException e) {
                e.printStackTrace();
                break;
            }

            if (method == null) {
                Log.d(TAG, "method not found: setWifiApConfiguration");
                break;
            }

            method.setAccessible(true);

            try {
                ret = (Boolean) method.invoke(manager, wifiConfig);
            } catch (IllegalAccessException | InvocationTargetException e) {
                e.printStackTrace();
            }
        } while (false);

        return ret;
    }

    public static int getWifiApState(WifiManager manager) {
        int state = 0;

        do {
            Class<WifiManager> clazz = WifiManager.class;
            Method method;

            try {
                method = clazz.getMethod("getWifiApState");
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
                state = (Integer) method.invoke(manager);
            } catch (IllegalAccessException | InvocationTargetException e) {
                e.printStackTrace();
            }

        } while (false);

        return state;
    }

    public static void setSoftApChannel(WifiConfiguration wifiConfiguration, int channel) {
        do {
            Field field = checkoutChannel("channel");
            if (field == null) {
                field = checkoutChannel("apChannel");
            }

            if (field == null) {
                Log.d(TAG, "channel not found");
                break;
            }

            field.setAccessible(true);

            try {
                field.setInt(wifiConfiguration, channel);
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }

        } while (false);
    }

    @Nullable
    private static Field checkoutChannel(String channelName) {
        Class clazz = WifiConfiguration.class;
        Field field;

        try {
            field = clazz.getDeclaredField(channelName);
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
            return null;
        }

        return field;
    }
}