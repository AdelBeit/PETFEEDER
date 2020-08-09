#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//------------------------------ webserver
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

MDNSResponder mdns;
ESP8266WebServer server(1337);
String webPage;


//------------------------------ ota code


const char* ssid = "loading...";
const char* password = "youtellme";

void setup() {

  //------------------------------ wifi
  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  //------------------------------ OTA 
  
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");
  ArduinoOTA.setHostname("Pepe");
  
  // No authentication by default
  // ArduinoOTA.setPassword("admin");
  
  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //------------------------------ code

  pinMode(LED_BUILTIN, OUTPUT);

  //------------------------------ webserver

//  webPage += "<h1>EA Server</h1><p>Socket #1 ";
//  webPage += "<a href=\"socket1On\"><button>ON</button></a>&nbsp;";
//  webPage += "<a href=\"socket1Off\"><button>OFF</button></a></p>";
//
//  if (mdns.begin("esp8266", WiFi.localIP())) 
//    Serial.println("MDNS responder started");
// 
//  server.on("/", [](){
//    server.send(200, "text/html", webPage);
//  });
//  server.on("/socket1On", [](){
//    server.send(200, "text/html", webPage);
//    // Turn off LED
//    digitalWrite(LED_BUILTIN, LOW);
//    delay(500);
//  });
//  server.on("/socket1Off", [](){
//    server.send(200, "text/html", webPage);
//    //Turn on LED
//    digitalWrite(LED_BUILTIN, HIGH      );
//    delay(500); 
//  });
//
//  server.begin();
}

void loop() {
  ArduinoOTA.handle();

  //------------------------------ code 
//  digitalWrite(4, HIGH);
//  delay(500);
//  digitalWrite(4, LOW);
//  delay(200);

  server.handleClient();
  
  //------------------------------ webserver
}
