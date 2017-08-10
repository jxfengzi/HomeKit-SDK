package com.oycf.rxwifi.rx.hotspot;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.rx.RxWifiConnector;
import com.oycf.rxwifi.rx.RxWifiController;

import rx.Observable;
import rx.Subscriber;
import rx.functions.Func1;

public class RxWifiStation {

    private static final String TAG = "RxWifiStation";
    private static final int TIMEOUT = 15;

    private RxWifiStation() {
    }

    @NonNull
    public static Observable<Object> connect(final Context context, final String ssid, final String password) {
        return Observable.create(new Observable.OnSubscribe<Object>() {

            @Override
            public void call(final Subscriber<? super Object> subscriber) {

                Observable<Object> opener = RxWifiController.setWifiEnabled(context, true, TIMEOUT);
                Observable<Object> connector = RxWifiConnector.connect(context, ssid, password, TIMEOUT);

                Observable.concat(opener, connector)
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
                                Log.d(TAG, "onError: " + e.toString());
                                subscriber.onError(e);
                            }

                            @Override
                            public void onNext(Object value) {
                                Log.d(TAG, "onNext: " + value);
                            }
                        });
            }
        });
    }
}