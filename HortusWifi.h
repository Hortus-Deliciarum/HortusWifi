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

    // HortusWifi(const char* ssid, const char* password, const char* ip);
    HortusWifi(Connection conn = Connection::BARETTI, int ip = 0);

private:
    Connection _conn;
    const* char _ssid;
    const* char _password;
    const IPAddress _ip;
};

#endif
