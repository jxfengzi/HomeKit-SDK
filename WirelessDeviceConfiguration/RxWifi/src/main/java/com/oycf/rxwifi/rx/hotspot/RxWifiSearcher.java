package com.oycf.rxwifi.rx.hotspot;

import android.content.Context;
import android.net.wifi.ScanResult;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.rx.RxWifiController;
import com.oycf.rxwifi.rx.RxWifiScanner;

import java.util.ArrayList;
import java.util.List;

import rx.Observable;
import rx.Subscriber;
import rx.functions.Func1;

public class RxWifiSearcher {

    private static final String TAG = "RxWifiSearcher";
    private static final int TIMEOUT = 15;

    private RxWifiSearcher() {
    }

    @NonNull
    public static Observable<List<ScanResult>> create(final Context context) {
        return Observable.create(new Observable.OnSubscribe<List<ScanResult>>() {

            @Override
            public void call(final Subscriber<? super List<ScanResult>> subscriber) {

                Observable<Object> opener = RxWifiController.setWifiEnabled(context, true, TIMEOUT);
                Observable<List<ScanResult>> scanner = RxWifiScanner.startScan(context);

                Observable.concat(opener, scanner)
                        .takeFirst(new Func1<Object, Boolean>() {
                            @Override
                            public Boolean call(Object o) {
                                return (o != null);
                            }
                        })
                        .subscribe(new Subscriber<Object>() {
                            @Override
                            public void onCompleted() {
                                Log.d(TAG, "onCompleted");
                                subscriber.onCompleted();
                            }

                            @Override
                            public void onError(Throwable e) {
                                Log.e(TAG, "onError: " + e.toString());
                                subscriber.onError(e);
                            }

                            @Override
                            public void onNext(Object value) {
                                Log.d(TAG, "onNext: " + value.getClass().getSimpleName());

                                if (value instanceof ArrayList) {
                                    subscriber.onNext((List<ScanResult>) value);
                                }
                            }
                        });
            }
        });
    }
}