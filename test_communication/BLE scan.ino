#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 prêt à scanner les périphériques BLE...");

  BLEDevice::init(""); // Initialisation du Bluetooth BLE
  pBLEScan = BLEDevice::getScan(); // Récupérer une instance de scan
  pBLEScan->setActiveScan(true);  // Active le scan actif pour plus de détails
  pBLEScan->setInterval(100);     // Intervalle entre chaque scan (en ms)
  pBLEScan->setWindow(99);        // Durée d'un scan (en ms)
}

void loop() {
  Serial.println("Recherche de périphériques BLE...");

  // Lancer un scan BLE de 5 secondes
  BLEScanResults foundDevices = pBLEScan->start(5, false);

  Serial.printf("Nombre de périphériques trouvés : %d\n", foundDevices.getCount());

  for (int i = 0; i < foundDevices.getCount(); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);

    // Afficher l'adresse, le nom (si disponible) et le RSSI pour chaque périphérique BLE trouvé
    Serial.print("Adresse : ");
    Serial.println(device.getAddress().toString().c_str());  // Adresse MAC
    Serial.print("Nom : ");
    Serial.println(device.getName().c_str());  // Nom du périphérique (si disponible)
    Serial.print("RSSI : ");
    Serial.println(device.getRSSI());  // RSSI du signal
    Serial.println("------------------------");
  }

  pBLEScan->clearResults(); // Nettoyer les résultats pour le prochain scan
  delay(10000); // Pause entre les scans
}
