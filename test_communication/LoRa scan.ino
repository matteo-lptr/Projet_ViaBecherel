#include <SPI.h>
#include <LoRa.h>

#define SS 5
#define RST 14
#define DIO0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Scanner");

  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(868E6)) {
    Serial.println("Erreur d'initialisation LoRa!");
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Paquet reçu '");

    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    Serial.print(message);
    Serial.print("' avec RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
