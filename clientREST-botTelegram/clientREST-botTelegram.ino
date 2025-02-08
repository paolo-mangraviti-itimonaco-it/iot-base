#include "R4WiFi_secrets.h"
#include <R4HttpClient.h>

WiFiSSLClient hostClient;
R4HttpClient botClient;

const char* _SSID = SECRET_SSID;
const char* _PASS = SECRET_PASS;
const char* _APISEND = APISEND;
const char* _USERID = USERID;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    Serial.println("Please upgrade the firmware");

  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  WiFi.begin(_SSID, _PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Successfully connected to WiFi!");

  String requestBody = "{\"text\":\"Nuova prova con Arduino R4\",\"chat_id\":\"";
  requestBody.concat(USERID); requestBody.concat("\"}"); 

  botClient.begin(hostClient, _APISEND, 443);
  //botClient.setTimeout(3000);
  botClient.addHeader("User-Agent: Arduino UNO R4 WiFi");
  botClient.addHeader("Content-Type: application/json");

  int responseNum = botClient.POST(requestBody);
  Serial.println(requestBody);
  if (responseNum > 0) // OR if (responseNum == HTTP_CODE_OK) // 200 OK
  {
    String responseBody = botClient.getBody();
    Serial.println(responseBody);
    Serial.println("Response code: " + String(responseNum));
  } else { Serial.println("Request Failed: " + String(responseNum));  }

  botClient.close();
}

void loop()
{
}
