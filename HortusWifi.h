#ifndef HortusWifi_h
#define HortusWifi_h

#include "Arduino.h"
#include <ArduinoOSCWiFi.h>
#include <WiFi.h>

class HortusWifi {
public:

    enum Connection {
        BARETTI = 0,
        GALLIARI = 1,
        HORTUS = 2
    };

    HortusWifi(Connection conn = Connection::BARETTI, int ip = 0, const char* awake_address);
    int send_awake_alert();

private:
    Connection _conn;
    const char* _ssid;
    const char* _password;
    const IPAddress _ip;
    const char* _awake;
};

#endif
