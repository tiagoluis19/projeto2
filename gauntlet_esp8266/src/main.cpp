#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <ESPAsyncTCP.h>

#define HOST "192.168.4.1"
#define PORT 21

AsyncClient client;

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

  delay(50);
  if (client.connect(HOST, PORT)) { // Connect to the server
    Serial.println("Connected to server");
    client.setNoDelay(true);
    digitalWrite(2, 0); // LED has inverted logic
  } else {
    Serial.println("Connection failed");
    digitalWrite(2, 0); // LED has inverted logic
  }
}

char buffer[100];


void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() && false) { // Check if data is available on Serial
    int bytesRead = Serial.readBytes(buffer, sizeof(buffer) - 1); // Read data into buffer
    buffer[bytesRead] = '\0'; // Null-terminate the string
    Serial.println(buffer); // Print the received data to Serial 
    
    
    // Transmit the data using ESPAsyncTCP
    if (client.canSend()) { // Check if the client can send data
      client.write(buffer, bytesRead); // Write the data to the client
      client.send(); // Send the data
      //delay(10);
    }
  }

  //client.write("anotsolongtestspring", sizeof("anotsolongtestspring"));
  //client.send();
  //delay(10);
}



