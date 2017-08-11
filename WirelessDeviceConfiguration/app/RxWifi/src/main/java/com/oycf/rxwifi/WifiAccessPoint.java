package com.oycf.rxwifi;

import android.content.Context;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.util.Log;

import com.oycf.rxwifi.hide.WifiConfigurationHidden;
import com.oycf.rxwifi.hide.WifiManagerHidden;
import com.oycf.rxwifi.receivers.RxWifiManagerExt;
import com.oycf.rxwifi.reflector.WifiManagerReflector;

import java.lang.reflect.Field;
import java.util.concurrent.TimeUnit;

import rx.Observer;
import rx.Subscription;
import rx.schedulers.Schedulers;
import rx.subscriptions.CompositeSubscription;

public class WifiAccessPoint {

    private static final String TAG = "WifiAccessPoint";
    //private static final int MAX_SSID = 32;
    private final CompositeSubscription subscriptions = new CompositeSubscription();
    private Context context;

    public interface OperateListener {
        void onSuccess();
        void onFailed(Throwable e);
    }

    public WifiAccessPoint(Context context) {
        this.context = context;
    }

    public void start(String ssid, String password, int channel, int timeout, final OperateListener listener) {
        final WifiManager manager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);

        int keyPsk = WifiConfigurationHidden.KeyMgmt.WPA2_PSK;

        try {
            Field f = WifiConfiguration.KeyMgmt.class.getField("WPA2_PSK");
            keyPsk = (Integer) f.get(null);
        } catch (NoSuchFieldException e) {
            Log.e(TAG, "NoSuchFieldException", e);
        } catch (IllegalAccessException e) {
            Log.e(TAG, "IllegalAccessException", e);
        }

        WifiConfiguration wifiConfig = new WifiConfiguration();
        wifiConfig.SSID = String.format("%s", ssid);
        wifiConfig.preSharedKey = String.format("%s", password);
        wifiConfig.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.OPEN);
        wifiConfig.allowedProtocols.set(WifiConfiguration.Protocol.RSN);
        wifiConfig.allowedProtocols.set(WifiConfiguration.Protocol.WPA);
        wifiConfig.allowedKeyManagement.set(keyPsk);
        wifiConfig.allowedPairwiseCiphers.set(WifiConfiguration.PairwiseCipher.CCMP);
        wifiConfig.allowedPairwiseCiphers.set(WifiConfiguration.PairwiseCipher.TKIP);
        wifiConfig.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.CCMP);
        wifiConfig.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.TKIP);

        if (channel > 0) {
            Log.d(TAG, "channel: " + channel);
            WifiManagerReflector.setSoftApChannel(wifiConfig, channel);
        }

        if (! WifiManagerReflector.setWifiApEnabled(manager, wifiConfig, true)) {
            listener.onFailed(new Throwable("setWifiApEnabled failed"));
            return;
        }

        Subscription subscription = RxWifiManagerExt.wifiApStateChanges(context)
                .subscribeOn(Schedulers.newThread())
                .timeout(timeout, TimeUnit.SECONDS)
                .subscribe(new Observer<Integer>() {
                    @Override
                    public void onCompleted() {
                        Log.e(TAG, "onCompleted");
                    }

                    @Override
                    public void onError(Throwable e) {
                        Log.e(TAG, "onError: " + e.toString());
                        listener.onFailed(e);
                    }

                    @Override
                    public void onNext(Integer state) {
                        Log.d(TAG, "onNext: " + WifiManagerHidden.getString(state));

                        if (state == WifiManagerHidden.WIFI_AP_STATE_ENABLED) {
                            subscriptions.unsubscribe();
                            subscriptions.clear();
                            listener.onSuccess();
                        }
                    }
                });

        subscriptions.add(subscription);
    }

    public void stop(int timeout, final OperateListener listener) {
        final WifiManager manager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);

        if (WifiManagerReflector.getWifiApState(manager) == WifiManagerHidden.WIFI_AP_STATE_DISABLED) {
            Log.d(TAG, "WIFI AP is disabled");
            listener.onSuccess();
            return;
        }

        if (! WifiManagerReflector.setWifiApEnabled(manager, null, false)) {
            listener.onFailed(new Throwable("setWifiApEnabled failed"));
            return;
        }

        Subscription subscription = RxWifiManagerExt.wifiApStateChanges(context)
                .subscribeOn(Schedulers.newThread())
                .timeout(timeout, TimeUnit.SECONDS)
                .subscribe(new Observer<Integer>() {
                    @Override
                    public void onCompleted() {
                        Log.e(TAG, "onCompleted");
                    }

                    @Override
                    public void onError(Throwable e) {
                        Log.e(TAG, "onError: " + e.toString());
                        listener.onFailed(e);
                    }

                    @Override
                    public void onNext(Integer state) {
                        Log.d(TAG, "onNext: " + WifiManagerHidden.getString(state));

                        if (state == WifiManagerHidden.WIFI_AP_STATE_DISABLED) {
                            subscriptions.unsubscribe();
                            subscriptions.clear();
                            listener.onSuccess();
                        }
                    }
                });

        subscriptions.add(subscription);
    }
}