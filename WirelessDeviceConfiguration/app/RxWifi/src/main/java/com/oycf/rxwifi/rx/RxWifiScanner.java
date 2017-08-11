package com.oycf.rxwifi.rx;

import android.content.Context;
import android.net.wifi.ScanResult;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.WifiScanner;

import java.util.List;

import rx.Observable;
import rx.Subscriber;

public class RxWifiScanner {

    private static final String TAG = "RxWifiScanner";

    private RxWifiScanner() {
    }

    @NonNull
    public static Observable<List<ScanResult>> startScan(final Context context) {
        return Observable.create(new Observable.OnSubscribe<List<ScanResult>>() {
            @Override
            public void call(final Subscriber<? super List<ScanResult>> subscriber) {
                WifiScanner scanner = new WifiScanner(context);

                scanner.startScan(new WifiScanner.OperateListener() {
                    @Override
                    public void onSuccess(List<ScanResult> scanResults) {
                        Log.e(TAG, "start: onSuccess");
                        subscriber.onNext(scanResults);
                        subscriber.onCompleted();
                    }

                    @Override
                    public void onFailed(Throwable e) {
                        Log.e(TAG, "startScan: onFailed");
                        subscriber.onError(e);
                    }
                });
            }
        });
    }
}