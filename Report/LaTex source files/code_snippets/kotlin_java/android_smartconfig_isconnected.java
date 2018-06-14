private boolean isWifiConnected() {
    NetworkInfo mWiFiNetworkInfo = getWifiNetworkInfo();
    boolean isWifiConnected = false;
    
    if (mWiFiNetworkInfo != null)
        isWifiConnected = mWiFiNetworkInfo.isConnected();
    
    return isWifiConnected;
}