#include "HortusWifi.h"
#include "Arduino.h"

#define SUBDOMAIN   0
#define SEND_PORT   10000

const* char bar_ssid = "FASTWEB-2yurFq";
const* char bar_password = "yBqCDXC6w8";
const* char gal_ssid = "FASTWEB-DAB6F7";
const* char gal_password = "1NJYRZE2T4";
const* char hortus_ssid = "francesco";
const* char hortus_password = "francesco";
const IPAddress _gateway(192, 168, SUBDOMAIN, 1);
const IPAddress _subnet(255, 255, 255, 0);
const IPAddress _host(192, 168, SUBDOMAIN, 10);

HortusWifi::HortusWifi(Connection conn, int ip, const char* awake_address)
{
#ifdef ESP_PLATFORM
    WiFi.disconnect(true, true); // disable wifi, erase ap info
    delay(1000);
#endif
    _conn = conn;
    _awake = awake_address;

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

    if (ip) {
        _ip = IPAddress ip(192, 168, SUBDOMAIN, ip);
        WiFi.config(_ip, gateway, subnet);
    }

    Serial.print("Connecting to WiFi ..");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }

    Serial.println(WiFi.localIP());
}

int HortusWifi::send_awake_alert()
{
    OscWiFi.publish(_host, SEND_PORT, _awake, 1)  
        ->setIntervalMsec(5000.f);  
}
