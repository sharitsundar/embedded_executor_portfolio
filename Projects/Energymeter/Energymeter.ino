//Author: Sharit Sundar

#include <LiquidCrystal.h>

#define PULSE_PIN 13
#define PULSES_PER_UNIT 1000
#define COST_PER_UNIT 7.0
#define PULSE_VALUE 0.3125   // energy per pulse in watt-seconds (or appropriate unit)

// Initialize LiquidCrystal object with pins (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Global pulse count
volatile unsigned long pulseCount = 0;

// Function prototypes
void sendEnergyUsageSMS(float units, float cost);
void updateLCD(float units, float cost);

void setup() {
  Serial.begin(9600);
  pinMode(PULSE_PIN, INPUT);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   SMART    ");
  lcd.setCursor(0, 1);
  lcd.print(" ENERGY METER");
  delay(2000);
  lcd.clear();
}

void loop() {
  static int pulseBatchCount = 0;
  static unsigned long lastPulseState = LOW;

  float unitsConsumed = (pulseCount * PULSE_VALUE) / PULSES_PER_UNIT;
  float cost = unitsConsumed * COST_PER_UNIT;

  // Read current pulse state
  int currentPulseState = digitalRead(PULSE_PIN);

  // Detect rising edge on pulse input to count pulses
  if (lastPulseState == LOW && currentPulseState == HIGH) {
    pulseCount++;
    pulseBatchCount++;
  }
  lastPulseState = currentPulseState;

  // Send SMS after every 3 pulses counted
  if (pulseBatchCount >= 3) {
    sendEnergyUsageSMS(unitsConsumed, cost);
    pulseBatchCount = 0;
  }

  updateLCD(unitsConsumed, cost);
  delay(50);  // small delay to reduce flicker and debouncing
}

// Function to send SMS with energy usage info via GSM module commands
void sendEnergyUsageSMS(float units, float cost) {
  Serial.write("AT+CMGF=1\r\n");        // Set SMS to text mode
  delay(1000);
  Serial.write("AT+CMGS=\"*phone_number*\"\r\n"); // Replace with actual phone number
  delay(1000);

  Serial.print("Unit: ");
  Serial.print(units, 3);  // print with 3 decimal places
  Serial.print(" kWh\n");

  Serial.print("Rupee: ");
  Serial.print(cost, 2);   // print with 2 decimal places
  Serial.print(" Rs\n");

  Serial.write((char)26); // ASCII code for Ctrl+Z to send SMS
  delay(1000);
}

// Function to update LCD display with current cost and units
void updateLCD(float units, float cost) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rupee: ");
  lcd.print(cost, 2);

  lcd.setCursor(0, 1);
  lcd.print("Unit: ");
  lcd.print(units, 3);
}
