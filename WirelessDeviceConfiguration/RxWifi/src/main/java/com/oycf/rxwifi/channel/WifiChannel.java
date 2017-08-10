package com.oycf.rxwifi.channel;

import android.content.Context;
import android.telephony.TelephonyManager;

public class WifiChannel {

    private static final int DEFAULT_CHANNEL = 6;
    private static final String[] COUNTRIES_TO_USE_CHANNEL_165 = {"BD", "BO", "BZ", "GY", "ID", "IR", "MO", "NG", "PK", "QA", "TW", "TZ"};

    public static int getDefaultChannel() {
        return DEFAULT_CHANNEL;
    }

    public static int get5GChannel(Context context) {
        TelephonyManager tm = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);

        String countryCode = tm.getSimCountryIso();

        for (String country : COUNTRIES_TO_USE_CHANNEL_165) {
            if (countryCode.equalsIgnoreCase(country)) {
                return 149;
            }
        }

        return 48;
    }
}