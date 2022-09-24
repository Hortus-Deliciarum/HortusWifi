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

    HortusWifi(Connection conn = Connection::BARETTI, int ip = 0, const char* awake = "/default");
    static const int RECV_PORT = 8000;
    static const int SEND_PORT = 10000;
    static const int AWK_PORT = 12000;
    constexpr static const char* HOST = "192.168.0.10";

private:
    Connection _conn;
    const char* _ssid;
    const char* _password;
    IPAddress _ip();
};

#endif
