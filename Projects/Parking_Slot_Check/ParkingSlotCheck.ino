// Author: Sharit Sundar


// Pin definitions for ultrasonic sensors (trigger and echo)
struct UltrasonicSensor {
  const int triggerPin;
  const int echoPin;
  const char* slotName;
};

const UltrasonicSensor sensors[] = {
  {7, 9, "slot1"},
  {2, 3, "slot2"},
  {4, 5, "slot3"},
  {8, 6, "slot4"}
};

const int sensorCount = sizeof(sensors) / sizeof(sensors[0]);

// Switch pins
const int entrySwitchPin = 10;
const int exitSwitchPin = 11;

// Distance threshold in cm to determine if slot is occupied
const int occupancyThresholdCm = 15;

// Function to initialize pins
void initializePins() {
  pinMode(entrySwitchPin, INPUT_PULLUP);
  pinMode(exitSwitchPin, INPUT_PULLUP);

  for (int i = 0; i < sensorCount; i++) {
    pinMode(sensors[i].triggerPin, OUTPUT);
    pinMode(sensors[i].echoPin, INPUT);
  }
}

// Function to measure distance from ultrasonic sensor in cm
long measureDistance(const UltrasonicSensor& sensor) {
  digitalWrite(sensor.triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor.triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor.triggerPin, LOW);

  long duration = pulseIn(sensor.echoPin, HIGH, 30000); // timeout 30ms
  if (duration == 0) {
    // No echo received (object might be out of range)
    return -1;
  }
  long distanceCm = (duration / 2) / 29.1;
  return distanceCm;
}

// Function to check each slot and print occupancy status
void checkSlots() {
  for (int i = 0; i < sensorCount; i++) {
    long distance = measureDistance(sensors[i]);
    if (distance > 0 && distance < occupancyThresholdCm) {
      Serial.print(sensors[i].slotName);
      Serial.println(" is occupied");
    }
    delay(50); // brief delay between sensor measurements to avoid interference
  }
}

// Function to check entry and exit switches
void checkSwitches() {
  int entryState = digitalRead(entrySwitchPin);
  int exitState = digitalRead(exitSwitchPin);

  if (entryState == LOW) {
    Serial.println("ENTRY");
    delay(500);  // debounce delay
  }
  if (exitState == LOW) {
    Serial.println("EXIT");
    delay(500);  // debounce delay
  }
}

void setup() {
  Serial.begin(9600);
  initializePins();
}

void loop() {
  checkSlots();
  checkSwitches();
}
