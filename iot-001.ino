#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library
#include "frames.h"               // Include a header file containing some custom icons
#include "WiFiS3.h"
//#include "WiFiSSLClient.h"
//#include <WiFiNINA.h>
#include "secrets.h" 
//#include <WiFiClientSecure.h>



ArduinoLEDMatrix matrix;          // Create an instance of the ArduinoLEDMatrix class
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
//IPAddress server(192,168,111,199);
//IPAddress server(94,32,111,10);
char server[] = "www.nesea.eu";    // name address (using DNS)

WiFiSSLClient client;
//WiFiClient client;
//WiFiClientSecure client;

char simbolo = 'c';
void setup() {
  Serial.begin(115200);
  matrix.begin();
   while (!Serial) { ; }

   // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  
  printWifiStatus();

}

void loop() {

  if (simbolo == 's') { matrix.loadFrame(happy); }
  if (simbolo == 'c') { matrix.loadFrame(LEDMATRIX_HEART_BIG); }
  if (simbolo == 'p') { matrix.loadFrame(danger); }

  delay(3000);
  matrix.clear();
  delay(3000);
  
  //client.setCACert(nesea_ca);
  if (client.connect(server,443)) {
    Serial.println("connected to server");
    client.println("GET /iot001/simbolo.txt HTTP/1.1");
    client.println("Host: www.nesea.eu");
    client.println("Connection: close");
    client.println("");
  }
  else
    { Serial.println("Errore di connessione al server"); }

  char c = 'n';
  Serial.println("attendo risposta");
  while (client.connected()) {
    while (client.available()) {
      // read an incoming byte from the server and print it to serial monitor:
      Serial.print((c = client.read()));
    }
  }
  if (!client.connected()) { Serial.println("disconnecting from server."); client.stop(); }
  
  /*
  unsigned long t1 = millis();
    while (client.available() == 0) {
      if ((millis() - t1) > 5000) {
         Serial.println("timeout");
         client.stop();
         while(true);
      }
    }
    
    //ricezione dati 
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    
    client.stop();
*/

}

void printWifiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}