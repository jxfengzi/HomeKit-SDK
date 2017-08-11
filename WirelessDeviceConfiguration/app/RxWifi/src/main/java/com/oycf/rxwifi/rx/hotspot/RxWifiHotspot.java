package com.oycf.rxwifi.rx.hotspot;

import android.content.Context;
import android.support.annotation.NonNull;
import android.util.Log;

import com.oycf.rxwifi.rx.RxWifiAccessPoint;
import com.oycf.rxwifi.rx.RxWifiController;

import rx.Observable;
import rx.Subscriber;
import rx.functions.Func1;

public class RxWifiHotspot {

    private static final String TAG = "RxWifiHotspot";
    private static final int TIMEOUT = 15;

    private RxWifiHotspot() {
    }

    @NonNull
    public static Observable<Object> create(final Context context, final String ssid, final String password, final int channel) {
        return Observable.create(new Observable.OnSubscribe<Object>() {

            @Override
            public void call(final Subscriber<? super Object> subscriber) {

                Observable<Object> closer = RxWifiController.setWifiEnabled(context, false, TIMEOUT);
                Observable<Object> destroyer = RxWifiAccessPoint.stop(context, TIMEOUT);
                Observable<Object> creator = RxWifiAccessPoint.start(context, ssid, password, channel, TIMEOUT);

                Observable.concat(closer, destroyer, creator)
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
