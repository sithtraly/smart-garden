#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define sensorPin A5

int rx = 0;
int tx = 1;
SoftwareSerial mySerial(rx, tx); // RX, TX
char command;
int ledPin = 10;
int relayPin = 2;
bool isRemoteByPhone = false;
OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  Serial.println("Enter AT commands:");
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);    //
  digitalWrite(relayPin, LOW); // not wattering by default
}

void startWattering() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(relayPin, HIGH);
}

void stopWattering() {
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, LOW);
}

void loop() {
  if (mySerial.available() > 0) {
    command = mySerial.read();
    if (command == '1') {
      isRemoteByPhone = true;
      startWattering();
    } else {
      isRemoteByPhone = false;
      stopWattering();
    }
    Serial.println(command);
  }
  int soilMoistureValue = analogRead(sensorPin);

  // Convert soil moisture value to percentage (adjust the mapping based on your sensor)
  float moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
  if (!isRemoteByPhone) {
    if (moisturePercentage >= 25) {
      startWattering();
    } else if (moisturePercentage <= 18) {
      stopWattering();
    }
  }
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");
  mySerial.print("Soil Moisture: ");
  mySerial.print(moisturePercentage);
  mySerial.println("%");

  delay(100);
}
