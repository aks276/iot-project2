#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <ArduinoJson.h>

ESP8266WebServer server;
uint8_t pin_led = 2;
char* ssid = "OnePlusNord";
char* password = "6080273227369";

void setup()
{
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/",[](){server.send(200,"text/plain","Hello World!");});
  server.on("/led",toggleLED);
//  server.on("/ledoff",jBlinkLED);
//  server.on("/qblink",qBlinkLED);
  server.begin();
}

void loop()
{
  server.handleClient();
}

void toggleLED()
{
  digitalWrite(pin_led,!digitalRead(pin_led));
  server.send(204,"");
}
