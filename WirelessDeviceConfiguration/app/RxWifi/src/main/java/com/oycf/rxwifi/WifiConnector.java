package com.oycf.rxwifi;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.support.annotation.NonNull;
import android.util.Log;

import com.f2prateek.rx.receivers.wifi.NetworkStateChangedEvent;
import com.f2prateek.rx.receivers.wifi.RxWifiManager;

import java.util.List;
import java.util.concurrent.TimeUnit;

import rx.Observer;
import rx.Subscription;
import rx.subscriptions.CompositeSubscription;

public class WifiConnector {

    private static final String TAG = "WifiConnector";
    private final CompositeSubscription subscriptions = new CompositeSubscription();
    private Context context;
    private WifiConfiguration config;

    public interface OperateListener {
        void onSuccess();
        void onFailed(Throwable e);
    }

    public WifiConnector(Context context) {
        this.context = context;
    }

    public void connect(String ssid, String password, boolean staticIp, int timeout, final OperateListener listener) {
        final String strSsid = "\"" + ssid + "\"";
        final WifiManager manager = (WifiManager) context.getApplicationContext().getSystemService(Context.WIFI_SERVICE);

        WifiInfo info = manager.getConnectionInfo();
        if (info != null) {
            Log.d(TAG, String.format("current connection is: %s (%s)", info.getSSID(), info.getBSSID()));
            if (strSsid.equals(info.getSSID())) {
                Log.d(TAG, "WIFI is connected");
                listener.onSuccess();
                return;
            }
        }

        if (password == null) {
            config = createWifiConfiguration(manager, strSsid, null, SecurityType.NONE, staticIp);
        }
        else {
            config = createWifiConfiguration(manager, strSsid, password, SecurityType.PSK, staticIp);
        }

        if (config == null) {
            Log.e(TAG, "createWifiConfiguration failed");
            listener.onFailed(new Throwable("createWifiConfiguration failed"));
            return;
        }

        int netId = (config.networkId == -1) ? manager.addNetwork(config) : config.networkId;
        if (netId == -1) {
            Log.e(TAG, "addNetwork failed: -1");
            listener.onFailed(new Throwable("addNetwork failed: -1"));
            return;
        }

        Log.d(TAG, "enableNetwork: " + netId);

        manager.disconnect();
        manager.enableNetwork(netId, true);
        manager.reconnect();

        Log.d(TAG, "reconnect ...");

        Subscription subscription = RxWifiManager.networkStateChanges(context)
                .timeout(timeout, TimeUnit.SECONDS)
                .subscribe(new Observer<NetworkStateChangedEvent>() {
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
                    public void onNext(NetworkStateChangedEvent event) {
                        // log(event);

                        NetworkInfo info = event.networkInfo();
                        if (info.getType() == ConnectivityManager.TYPE_WIFI) {
                            Log.d(TAG, String.format("%s -> %s/%s", info.getExtraInfo(), info.getState(), info.getDetailedState()));

                            if (info.isConnected()) {
                                String ssid = info.getExtraInfo();
                                String configSsid = config.SSID;

                                ssid = removeDoubleQuotes(ssid);
                                configSsid = removeDoubleQuotes(configSsid);

                                if (ssid.equals(configSsid)) {
                                    WifiInfo wifiInfo = event.wifiInfo();
                                    if (wifiInfo != null) {
                                        Log.d(TAG, "ip: " + intToString(wifiInfo.getIpAddress()));
                                    }

                                    subscriptions.unsubscribe();
                                    subscriptions.clear();
                                    listener.onSuccess();
                                }
                            }
                        }
                    }
                });

        subscriptions.add(subscription);
    }

    private static String removeDoubleQuotes(String string) {
        int length = string.length();

        if ((length > 1) && (string.charAt(0) == '"')
                && (string.charAt(length - 1) == '"')) {
            return string.substring(1, length - 1);
        }

        return string;
    }

    @NonNull
    private static String intToString(int a) {
        StringBuilder sb = new StringBuilder();
        int b = (a) & 0xff;
        sb.append(b).append(".");
        b = (a >> 8) & 0xff;
        sb.append(b).append(".");
        b = (a >> 16) & 0xff;
        sb.append(b).append(".");
        b = (a >> 24) & 0xff;
        sb.append(b);
        return sb.toString();
    }

    private enum SecurityType {
        NONE,
        WEP,
        PSK,
    }

    private static WifiConfiguration createWifiConfiguration(WifiManager manager,
                                                             String ssid,
                                                             String password,
                                                             SecurityType securityType,
                                                             boolean staticIp) {
        Log.d(TAG, String.format("createWifiConfiguration SSID: %s, Password: %s, Type: %s",
                ssid, password, securityType));

        WifiConfiguration config = null;

        do {
            List<WifiConfiguration> list = manager.getConfiguredNetworks();
            if (list != null) {
                for (WifiConfiguration c : list) {
                    if (c.SSID != null) {
                        Log.d(TAG, String.format("[%s]", c.SSID));
                        if (c.SSID.equals(ssid)) {
                            Log.d(TAG, String.format("config exist, networkId: %d", c.networkId));
                            config = c;
                            break;
                        }
                    }
                }
            }

            if (config != null) {
                break;
            }

            config = new WifiConfiguration();
            config.allowedAuthAlgorithms.clear();
            config.allowedGroupCiphers.clear();
            config.allowedKeyManagement.clear();
            config.allowedPairwiseCiphers.clear();
            config.allowedProtocols.clear();
            config.SSID = ssid;
            config.networkId = -1;

            switch (securityType) {
                case NONE:
                    config.wepKeys[0] = "\"\"";
                    config.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
                    config.wepTxKeyIndex = 0;
                    break;

                case WEP:
                    config.hiddenSSID = true;
                    config.wepKeys[0] = "\"" + password + "\"";
                    config.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.SHARED);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.CCMP);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.TKIP);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.WEP40);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.WEP104);
                    config.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.NONE);
                    config.wepTxKeyIndex = 0;
                    break;

                case PSK:
                    config.preSharedKey = "\"" + password + "\"";
                    config.hiddenSSID = true;
                    config.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.OPEN);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.TKIP);
                    config.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.WPA_PSK);
                    config.allowedPairwiseCiphers.set(WifiConfiguration.PairwiseCipher.TKIP);
                    config.allowedGroupCiphers.set(WifiConfiguration.GroupCipher.CCMP);
                    config.allowedPairwiseCiphers.set(WifiConfiguration.PairwiseCipher.CCMP);
                    config.status = WifiConfiguration.Status.ENABLED;
                    break;

                default:
                    break;
            }
        } while (false);

//        if (staticIp) {
//            try {
//                config = WifiUtils.configStaticIp(config);
//            } catch (NoSuchMethodError e) {
//                e.printStackTrace();
//            }
//        }

        return config;
    }
}
