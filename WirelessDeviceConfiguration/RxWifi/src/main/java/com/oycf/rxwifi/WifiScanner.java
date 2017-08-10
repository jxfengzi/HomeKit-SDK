package com.oycf.rxwifi;

import android.content.Context;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.util.Log;

import com.oycf.rxwifi.receivers.RxWifiManagerExt;

import java.util.List;

import rx.Observer;
import rx.Subscription;
import rx.subscriptions.CompositeSubscription;

public class WifiScanner {

    private static final String TAG = "WifiScanner";
    private final CompositeSubscription subscriptions = new CompositeSubscription();
    private final Context context;
    private final WifiManager manager;

    public interface OperateListener {
        void onSuccess(List<ScanResult> scanResults);
        void onFailed(Throwable e);
    }

    public WifiScanner(Context context) {
        this.context = context;
        this.manager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
    }

    public void startScan(final OperateListener listener) {
        Subscription subscription = RxWifiManagerExt.wifiScanResultAvailable(context)
                .subscribe(new Observer<Boolean>() {
                    @Override
                    public void onCompleted() {
                        Log.d(TAG, "onCompleted");
                    }

                    @Override
                    public void onError(Throwable e) {
                        Log.e(TAG, "onError: " + e.toString());
                        listener.onFailed(e);
                    }

                    @Override
                    public void onNext(Boolean b) {
                        Log.d(TAG, "onNext: " + b);

                        subscriptions.unsubscribe();
                        subscriptions.clear();

                        listener.onSuccess(manager.getScanResults());
                    }
                });

        subscriptions.add(subscription);

        if (! manager.startScan()) {
            Log.d(TAG, "startScan failed");
        }
    }

    public void stopScan() {
        subscriptions.unsubscribe();
        subscriptions.clear();
    }
}