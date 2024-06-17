#include <SoftwareSerial.h>

// Create a SoftwareSerial object to communicate with SIM800L
SoftwareSerial sim800lSerial(7, 8); // RX, TX pins

void setup() {
  // Set the baud rate for SoftwareSerial
  sim800lSerial.begin(9600);
  
  // Initialize SIM800L
  sendCommand("AT\r\n");
  delay(1000);
  
  // Set SMS text mode
  sendCommand("AT+CMGF=1\r\n");
  delay(1000);
}

void loop() {
  // Send SMS
  sendSMS("+918851305726", "Hello from Arduino Nano!");
  delay(5000); // Delay before sending the next SMS
}

void sendSMS(String phoneNumber, String message) {
  // Set phone number
  sim800lSerial.print("AT+CMGS=\"");
  sim800lSerial.print(phoneNumber);
  sim800lSerial.println("\"");
  delay(1000);
  
  // Set message content
  sim800lSerial.print(message);
  
  // Send Ctrl+Z to indicate end of message
  sim800lSerial.write(0x1A);
  delay(1000);
}

void sendCommand(String command) {
  sim800lSerial.print(command);
  while (!sim800lSerial.available());
  while (sim800lSerial.available()) {
    Serial.write(sim800lSerial.read());
  }
}
