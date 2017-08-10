package com.oycf.rxwifi.rx;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;


import com.oycf.rxwifi.WifiAccessPoint;

import rx.Observable;
import rx.Subscriber;

public class RxWifiAccessPoint {

    private static final String TAG = "RxWifiAccessPoint";

    private RxWifiAccessPoint() {
    }

    @NonNull
    public static Observable<Object> start(final Context context, final String ssid, final String password, final int channel, final int timeout) {
        return Observable.create(new Observable.OnSubscribe<Object>() {
            @Override
            public void call(final Subscriber<? super Object> subscriber) {
                WifiAccessPoint ap = new WifiAccessPoint(context);

                ap.start(ssid, password, channel, timeout, new WifiAccessPoint.OperateListener(){

                    @Override
                    public void onSuccess() {
                        Log.e(TAG, "start: onSuccess");
                        subscriber.onCompleted();
                    }

                    @Override
                    public void onFailed(Throwable e) {
                        Log.e(TAG, "start: onFailed");
                        subscriber.onError(e);
                    }
                });
            }
        });
    }

    @NonNull
    public static Observable<Object> stop(final Context context, final int timeout) {
        return Observable.create(new Observable.OnSubscribe<Object>() {
            @Override
            public void call(final Subscriber<? super Object> subscriber) {
                WifiAccessPoint ap = new WifiAccessPoint(context);

                ap.stop(timeout, new WifiAccessPoint.OperateListener(){

                    @Override
                    public void onSuccess() {
                        Log.e(TAG, "stop: onSuccess");
                        subscriber.onCompleted();
                    }

                    @Override
                    public void onFailed(Throwable e) {
                        Log.e(TAG, "stop: onFailed");
                        subscriber.onError(e);
                    }
                });
            }
        });
    }
}
