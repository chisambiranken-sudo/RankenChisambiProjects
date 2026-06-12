#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD at default I2C address 0x27, 20 columns and 4 rows
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int pumpPin = 10;   // Pump control
const int valveInflate = 12; // Valve 1 (inflate)
const int valveDeflate = 13; // Valve 2 (deflate)

void setup() {
  // Pin modes
  pinMode(pumpPin, OUTPUT);
  pinMode(valveInflate, OUTPUT);
  pinMode(valveDeflate, OUTPUT);

  // Start Serial Monitor
  Serial.begin(9600);

  // Start LCD
  lcd.init();
  lcd.backlight();

  // Initial messages
  lcd.setCursor(0, 0);
  lcd.print("Compression Device");
  Serial.println("System Initialized...");
  delay(2000);
}

void loop() {
  // Step 1: Inflate
  digitalWrite(pumpPin, HIGH);      // Turn pump ON
  digitalWrite(valveInflate, HIGH); // Open inflate valve
  digitalWrite(valveDeflate, LOW);  // Ensure deflate valve is closed

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inflating...");
  Serial.println("Inflating...");

  delay(5000); // Inflate for 5 seconds

  // Step 2: Deflate
  digitalWrite(pumpPin, LOW);       // Turn pump OFF
  digitalWrite(valveInflate, LOW);  // Close inflate valve
  digitalWrite(valveDeflate, HIGH); // Open deflate valve

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deflating...");
  Serial.println("Deflating...");

  delay(5000); // Deflate for 5 seconds

  // Step 3: Rest
  digitalWrite(valveDeflate, LOW); // Close all valves
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cycle Complete");
  Serial.println("Cycle Complete");

  delay(3000); // Rest before repeating
}
