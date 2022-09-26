#include <HortusWifi.h>

void setup() {
  Serial.begin(115200);
  HortusWifi(HortusWifi::Connection::BARETTI, 0);
}

void loop() {
  delay(1000);
}
