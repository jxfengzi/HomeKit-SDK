package com.oycf.rxwifi;

import android.content.Context;
import android.net.wifi.WifiManager;
import android.util.Log;

import com.f2prateek.rx.receivers.wifi.RxWifiManager;
import com.oycf.rxwifi.hide.WifiManagerHidden;

import java.util.concurrent.TimeUnit;

import rx.Observer;
import rx.Subscription;
import rx.functions.Action0;
import rx.schedulers.Schedulers;
import rx.subscriptions.CompositeSubscription;

public class WifiController {

    private static final String TAG = "WifiController";
    private final CompositeSubscription subscriptions = new CompositeSubscription();
    private Context context;

    public interface OperateListener {
        void onSuccess();
        void onFailed(Throwable e);
    }

    public WifiController(Context context) {
        this.context = context;
    }

    public void setWifiEnabled(final boolean enabled, int timeout, final OperateListener listener) {
        final WifiManager manager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);

        if (enabled == manager.isWifiEnabled()) {
            Log.d(TAG, String.format("WIFI is %s", enabled ? "enabled" : "disabled"));
            listener.onSuccess();
            return;
        }

        Subscription subscription = RxWifiManager.wifiStateChanges(context)
                .doOnSubscribe(new Action0() {
                    @Override
                    public void call() {
                        Log.d(TAG, "setWifiEnabled: " + enabled);
                        manager.setWifiEnabled(enabled);
                    }
                })
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

                        if (enabled) {
                            if (state == WifiManager.WIFI_STATE_ENABLED) {
                                subscriptions.unsubscribe();
                                subscriptions.clear();
                                listener.onSuccess();
                            }
                        }
                        else {
                            if (state == WifiManager.WIFI_STATE_DISABLED) {
                                subscriptions.unsubscribe();
                                subscriptions.clear();
                                listener.onSuccess();
                            }
                        }
                    }
                });

        subscriptions.add(subscription);
    }
}
