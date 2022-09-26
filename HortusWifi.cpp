#include "HortusWifi.h"
#include "Arduino.h"

#define SUBDOMAIN 0
#define AWAKE_PORT 12000

const char* bar_ssid = "FASTWEB-2yurFq";
const char* bar_password = "yBqCDXC6w8";
const char* gal_ssid = "FASTWEB-DAB6F7";
const char* gal_password = "1NJYRZE2T4";
const char* hortus_ssid = "HORTUS";
const char* hortus_password = "francesco";
const IPAddress _gateway(192, 168, SUBDOMAIN, 1);
const IPAddress _subnet(255, 255, 255, 0);

HortusWifi::HortusWifi(Connection conn, int ip, String& awake)
{
#ifdef ESP_PLATFORM
    WiFi.disconnect(true, true); // disable wifi, erase ap info
    delay(1000);
#endif
    _conn = conn;

    switch (_conn) {
    case Connection::BARETTI:
        _ssid = bar_ssid;
        _password = bar_password;
        break;
    case Connection::GALLIARI:
        _ssid = gal_ssid;
        _password = gal_password;
        break;
    case Connection::HORTUS:
        _ssid = hortus_ssid;
        _password = hortus_password;
        break;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);

    if (ip && _conn == Connection::HORTUS) {
        IPAddress _ip((uint8_t)192, (uint8_t)168, (uint8_t)SUBDOMAIN, (uint8_t)ip);
        WiFi.config(_ip, _gateway, _subnet);
    }

    Serial.print("Connecting to WiFi ..");

    int counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
        counter++;
        if (counter == 10)
            ESP.restart();
    }

    Serial.println(WiFi.localIP());

    OscWiFi.publish(HOST, AWK_PORT, awake, 1)
        ->setIntervalMsec(5000.f);
}
