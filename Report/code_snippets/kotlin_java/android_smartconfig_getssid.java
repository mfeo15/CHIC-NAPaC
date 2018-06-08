public String getWifiConnectedSsid() {
    WifiInfo mWifiInfo = this.getConnectionInfo();
    String ssid = null;
    
    // Check if WiFi connection exists
    if (mWifiInfo != null && this.isWifiConnected()) {
        int len = mWifiInfo.getSSID().length();
        
        // Check SSID name format for retrival
        if ( mWifiInfo.getSSID().startsWith("\"")
                && mWifiInfo.getSSID().endsWith("\"") ) 
        {
            ssid = mWifiInfo.getSSID().substring(1, len - 1);
        } else {
            ssid = mWifiInfo.getSSID();
        }
    }
    return ssid;
}