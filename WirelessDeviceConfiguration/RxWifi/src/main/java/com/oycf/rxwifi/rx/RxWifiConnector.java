package com.oycf.rxwifi.rx;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.WifiConnector;

import rx.Observable;
import rx.Subscriber;

public class RxWifiConnector {

    private static final String TAG = "RxWifiConnector";

    private RxWifiConnector() {
    }

    @NonNull
    public static Observable<Object> connect(final Context context, final String ssid, final String password, final int timeout) {
        return Observable.create(new Observable.OnSubscribe<Object>() {
            @Override
            public void call(final Subscriber<? super Object> subscriber) {
                WifiConnector connector = new WifiConnector(context);
                connector.connect(ssid, password, false, timeout, new WifiConnector.OperateListener() {
                    @Override
                    public void onSuccess() {
                        Log.e(TAG, "connect: onSuccess");
                        subscriber.onCompleted();
                    }

                    @Override
                    public void onFailed(Throwable e) {
                        Log.e(TAG, "connect: onFailed");
                        subscriber.onError(e);
                    }
                });
            }
        });
    }
}
