#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 10; // Durée du scan en secondes
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.println("------------------------------------");
      Serial.printf("Adresse MAC: %s\n", advertisedDevice.getAddress().toString().c_str());
      
      if (advertisedDevice.haveName()) {
        Serial.printf("Nom: %s\n", advertisedDevice.getName().c_str());
      } else {
        Serial.println("Nom: Non disponible");
      }
      
      Serial.printf("RSSI: %d\n", advertisedDevice.getRSSI());
      
      if (advertisedDevice.haveManufacturerData()) {
        std::string manufacturerData = advertisedDevice.getManufacturerData().c_str();
        Serial.print("Données fabricant: ");
        for (int i = 0; i < manufacturerData.length(); i++) {
          Serial.printf("%02X", (uint8_t)manufacturerData[i]);
        }
        Serial.println();
      }
      
      if (advertisedDevice.haveTXPower()) {
        Serial.printf("TX Power: %d\n", advertisedDevice.getTXPower());
      }
      
      Serial.println("------------------------------------");
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Démarrage du scan des appareils Bluetooth...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  Serial.println("Début du scan...");
  BLEScanResults* foundDevices = pBLEScan->start(scanTime, false);
  Serial.print("Appareils trouvés: ");
  Serial.println(foundDevices->getCount());
  Serial.println("Scan terminé!");
  pBLEScan->clearResults();
  delay(20000000000);
}
