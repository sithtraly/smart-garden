#include <SoftwareSerial.h>

int state = 0;
int rx = 0;
int tx = 1;
SoftwareSerial mySerial(rx, tx); // RX, TX
char command;
int ledPin = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  Serial.println("Enter AT commands:");
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (mySerial.available() > 0) {
    command = mySerial.read();
    command == '1' ? digitalWrite(ledPin, HIGH) : digitalWrite(ledPin, LOW);
    Serial.println(command);
  }
  delay(100);
}
