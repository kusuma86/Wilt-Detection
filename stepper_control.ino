#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h> 


// WIFI
const char* ssid = "Kusuma";
const char* password = "12345678AB!!";

// Create a web server object that listens on port 80
WebServer server(80);

// stepper
#define dirPin1 25 // pin yang terhubung ke DIR+ motor driver pertama
#define stepPin1 26 // pin yang terhubung ke PUL+ motor driver pertama
#define dirPin2 13 // pin yang terhubung ke DIR+ motor driver kedua
#define stepPin2 14 // pin yang terhubung ke PUL+ motor driver kedua

AccelStepper stepper1 = AccelStepper(1, stepPin1, dirPin1);
AccelStepper stepper2 = AccelStepper(1, stepPin2, dirPin2);


// This function will run when the ESP32 receives a POST request
void handlePost() {
  if (server.hasArg("plain")) { // Check if body received
    String message = server.arg("plain");
    Serial.println("Received POST data: " + message);
    
    if (message == "geser1"){
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(0);
      stepper1.runToPosition();
    }
    else if (message == "geser12"){
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(125);
      stepper1.runToPosition();
    }
    else if (message == "geser2") {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(250);
      stepper1.runToPosition();
    }
    else if (message == "geser22") {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(375);
      stepper1.runToPosition();
    }
    else if (message == "geser3") {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(500);
      stepper1.runToPosition();
    }
    else if (message == "geser32") {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(620);
      stepper1.runToPosition();
    }
    else if (message == "naik1") {
      server.send(200, "text/plain", "Data received");
      stepper2.moveTo(900);
      stepper2.runToPosition();
    } 
    else if (message == "naik2") {
      server.send(200, "text/plain", "Data received");
      stepper2.moveTo(1800);
      stepper2.runToPosition();
    }
    else if (message == "turun") {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(0);
      stepper1.runToPosition();
      delay(2000);
      stepper2.moveTo(0);
      stepper2.runToPosition();
    }
    else {
      server.send(200, "text/plain", "Data received");
      stepper1.moveTo(0);
      stepper1.runToPosition();
      delay(2000);
      stepper2.moveTo(0);
      stepper2.runToPosition();
    }  
  
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Define the route for POST request
  server.on("/post-data", HTTP_POST, handlePost);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
  
  // stepper
  stepper1.setMaxSpeed(500); // atur kecepatan motor pertama
  stepper1.setAcceleration(100); // nilai akselerasi motor pertama

  stepper2.setMaxSpeed(500); // atur kecepatan motor kedua
  stepper2.setAcceleration(100); // nilai akselerasi motor kedua
  
}

void loop() {
  server.handleClient();
}
