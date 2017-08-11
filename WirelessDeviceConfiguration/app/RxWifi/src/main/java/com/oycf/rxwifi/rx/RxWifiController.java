package com.oycf.rxwifi.rx;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.WifiController;

import rx.Observable;
import rx.Subscriber;

public class RxWifiController {

    private static final String TAG = "RxWifiController";

    private RxWifiController() {
    }

    @NonNull
    public static Observable<Object> setWifiEnabled(final Context context, final boolean enabled, final int timeout) {
        return Observable.create(new Observable.OnSubscribe<Object>() {
            @Override
            public void call(final Subscriber<? super Object> subscriber) {
                WifiController controller = new WifiController(context);
                controller.setWifiEnabled(enabled, timeout, new WifiController.OperateListener() {
                    @Override
                    public void onSuccess() {
                        Log.e(TAG, "setWifiEnabled: onSuccess");
                        subscriber.onCompleted();
                    }

                    @Override
                    public void onFailed(Throwable e) {
                        Log.e(TAG, "setWifiEnabled: onFailed");
                        subscriber.onError(e);
                    }
                });
            }
        });
    }
}