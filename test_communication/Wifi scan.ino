#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  
  // Configure le WiFi en mode station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.println("Scan WiFi démarré");
}

void loop() {
  int n = WiFi.scanNetworks();
  Serial.println("Scan terminé");
  
  if (n == 0) {
    Serial.println("Aucun réseau trouvé");
  } else {
    Serial.print(n);
    Serial.println(" réseaux trouvés");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm)");
      delay(10);
    }
  }
  
  Serial.println("");
  delay(50000000); // Attendre 5 secondes avant le prochain scan
}
