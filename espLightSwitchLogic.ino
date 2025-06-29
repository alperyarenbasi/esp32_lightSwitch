#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// WiFi credentials - CHANGE THESE TO YOUR NETWORK
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);
Servo myServo;

const int servoPin = 18; // Changed to GPIO 18 (commonly used for servos)
const int ledPin = 2;    // Built-in LED for status indication

// HTML page with improved styling
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 Light Switch</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, sans-serif; text-align: center; margin: 50px; background-color: #f0f0f0; }
        .container { max-width: 400px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 4px 6px rgba(0,0,0,0.1); }
        h1 { color: #333; margin-bottom: 30px; }
        .button { background-color: #4CAF50; border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 10px; cursor: pointer; border-radius: 5px; width: 120px; }
        .button:hover { background-color: #45a049; }
        .off-button { background-color: #f44336; }
        .off-button:hover { background-color: #da190b; }
        .status { margin-top: 20px; padding: 10px; background-color: #e7f3ff; border-radius: 5px; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Light Switch</h1>
        <p>Control your servo-operated light switch</p>
        
        <form action="/on" method="POST" style="display: inline;">
            <button type="submit" class="button">Turn ON</button>
        </form>
        
        <form action="/off" method="POST" style="display: inline;">
            <button type="submit" class="button off-button">Turn OFF</button>
        </form>
        
        <div class="status">
            <p><strong>Device Status:</strong> Online</p>
            <p><strong>IP Address:</strong> %IP_ADDRESS%</p>
        </div>
    </div>
</body>
</html>
)rawliteral";

void handleRoot() {
  String page = String(htmlPage);
  page.replace("%IP_ADDRESS%", WiFi.localIP().toString());
  server.send(200, "text/html", page);
}

void handleOn() {
  Serial.println("Turning light ON - Servo to 90°");
  myServo.write(90);
  digitalWrite(ledPin, HIGH);
  delay(500); // Give servo time to move
  
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Light turned ON");
}

void handleOff() {
  Serial.println("Turning light OFF - Servo to 0°");
  myServo.write(0);
  digitalWrite(ledPin, LOW);
  delay(500); // Give servo time to move
  
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "Light turned OFF");
}

void handleNotFound() {
  server.send(404, "text/plain", "404: Not Found");
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("\n=== ESP32 Light Switch Starting ===");
  
  // Initialize pins
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Initialize servo
  myServo.attach(servoPin);
  myServo.write(0); // Start in OFF position
  Serial.println("Servo initialized on pin " + String(servoPin));
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected successfully!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Access the web interface at: http://");
    Serial.println(WiFi.localIP());
    
    // Blink LED to indicate successful connection
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
    }
  } else {
    Serial.println("\nFailed to connect to WiFi!");
    Serial.println("Please check your credentials and try again.");
    return;
  }
  
  // Setup web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_POST, handleOn);
  server.on("/off", HTTP_POST, handleOff);
  server.onNotFound(handleNotFound);
  
  // Start the server
  server.begin();
  Serial.println("Web server started!");
  Serial.println("=== Setup Complete ===\n");
}

void loop() {
  server.handleClient();
  
  // Optional: Add a small delay to prevent watchdog issues
  delay(10);
}
