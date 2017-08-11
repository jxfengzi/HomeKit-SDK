package com.oycf.rxwifi.receivers;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.support.annotation.CheckResult;
import android.support.annotation.NonNull;
import android.util.Log;

import com.f2prateek.rx.receivers.RxBroadcastReceiver;
import com.oycf.rxwifi.hide.WifiManagerHidden;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import rx.Observable;
import rx.functions.Func1;

import static android.net.wifi.WifiManager.EXTRA_WIFI_STATE;
import static com.f2prateek.rx.receivers.internal.Preconditions.checkNotNull;

public class RxWifiManagerExt {

    private static final String TAG = "RxWifiManagerExt";

    private RxWifiManagerExt() {
        throw new AssertionError("no instances");
    }

    @CheckResult
    @NonNull
    public static Observable<Integer> wifiApStateChanges(@NonNull final Context context) {
        checkNotNull(context, "context == null");
        IntentFilter filter = new IntentFilter(WifiManagerHidden.WIFI_AP_STATE_CHANGED_ACTION);
        return RxBroadcastReceiver.create(context, filter).map(new Func1<Intent, Integer>() {
            @Override public Integer call(Intent intent) {
                return intent.getIntExtra(EXTRA_WIFI_STATE, -1);
            }
        });
    }

    @CheckResult
    @NonNull
    public static Observable<Boolean> wifiScanResultAvailable(@NonNull final Context context) {
        checkNotNull(context, "context == null");
        IntentFilter filter = new IntentFilter(WifiManager.SCAN_RESULTS_AVAILABLE_ACTION);
        return RxBroadcastReceiver.create(context, filter).map(new Func1<Intent, Boolean>() {
            @Override public Boolean call(Intent intent) {
                Log.d(TAG, "Action: " + intent.getAction());
                readAccessPointsOnce(context);
                return true;
            }
        });
    }

    private static void readAccessPointsOnce(Context context) {
        Log.e(TAG, "---------- readAccessPointsOnce -----------");

        WifiManager wifiManager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);

        List<ScanResult> results = wifiManager.getScanResults();
        for (ScanResult r : results) {
            Log.d(TAG, "ssid: " + r.SSID);
        }
    }
}