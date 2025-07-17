#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <ESPAsyncTCP.h>

#define HOST "192.168.4.1"
#define PORT 21

//AsyncClient client;

#include <WiFiUdp.h>

WiFiUDP udp;

void setup() {

  Serial.begin(9600); // Initialize Serial with a baud rate of 9600
  Serial.setTimeout(5);

  pinMode(2, OUTPUT); //Builtin LED

  WiFi.begin("Turret", "idonthateyou"); // Connect to Wi-Fi

  bool led = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500); // Wait for 1 second
    digitalWrite(2, led = !led);
    Serial.println("Connecting to WiFi...");
  }
  digitalWrite(2, 1);

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the local IP address

}

char buffer[100];


void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) { // Check if data is available on Serial
    int bytesRead = Serial.readBytes(buffer, sizeof(buffer) - 1); // Read data into buffer
    buffer[bytesRead] = '\0'; // Null-terminate the string
    Serial.println(buffer); // Print the received data to Serial 
    
    udp.beginPacket("255.255.255.255", 21);
    udp.write(buffer);
    udp.endPacket();
  }
}



