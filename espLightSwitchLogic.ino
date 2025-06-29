#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid     = ;
const char* password = ;



WebServer server(80);
Servo myServo;

const int servoPin = 8; // Set to your working GPIO

void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
    <html><head><title>Light Switch</title></head><body>
      <h2>Servo Light Switch</h2>
      <form action="/on" method="POST"><button type="submit">Turn ON</button></form>
      <form action="/off" method="POST"><button type="submit">Turn OFF</button></form>
    </body></html>
  )rawliteral");
}

void handleOn() {
  myServo.write(90);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void handleOff() {
  myServo.write(0);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  myServo.attach(servoPin);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_POST, handleOn);
  server.on("/off", HTTP_POST, handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
