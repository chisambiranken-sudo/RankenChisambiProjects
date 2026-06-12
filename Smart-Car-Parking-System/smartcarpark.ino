/*
===========================================================
SMART CAR PARKING SYSTEM
Author: Ranken Chisambi
Project Type: IoT & Embedded Systems
Platform: Arduino Uno

Features:
- Vehicle Entry Detection
- Vehicle Exit Detection
- Automatic Gate Control
- Parking Space Counting
- LCD Information Display
- Bluetooth Monitoring
- LED Status Indicators
- Buzzer Alerts
===========================================================
*/

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// =====================
// LCD Configuration
// =====================
LiquidCrystal_I2C lcd(0x27, 16, 2);

// =====================
// Bluetooth Module
// =====================
SoftwareSerial BT(10, 11); // RX, TX

// =====================
// Servo Motor
// =====================
Servo gateServo;

// =====================
// Pin Definitions
// =====================
const int entrySensor = 2;
const int exitSensor  = 3;

const int greenLED = 4;
const int redLED   = 5;

const int buzzer   = 6;
const int servoPin = 9;

// =====================
// Parking Configuration
// =====================
const int MAX_SPACES = 10;

int occupiedSpaces = 0;
int availableSpaces = MAX_SPACES;

// =====================
// Timing Variables
// =====================
unsigned long previousMillis = 0;
const long lcdInterval = 1000;

// =====================================================
// Function Prototypes
// =====================================================
void displayStatus();
void processEntry();
void processExit();
void openGate();
void closeGate();
void updateIndicators();
void sendBluetoothData();

// =====================================================
// Setup Function
// =====================================================
void setup()
{
    Serial.begin(9600);
    BT.begin(9600);

    pinMode(entrySensor, INPUT);
    pinMode(exitSensor, INPUT);

    pinMode(greenLED, OUTPUT);
    pinMode(redLED, OUTPUT);

    pinMode(buzzer, OUTPUT);

    gateServo.attach(servoPin);

    lcd.init();
    lcd.backlight();

    gateServo.write(0);

    lcd.setCursor(0,0);
    lcd.print("SMART PARKING");

    lcd.setCursor(0,1);
    lcd.print("INITIALIZING");

    delay(3000);

    lcd.clear();

    updateIndicators();

    Serial.println("System Started");
}

// =====================================================
// Main Loop
// =====================================================
void loop()
{
    if(digitalRead(entrySensor) == HIGH)
    {
        processEntry();
    }

    if(digitalRead(exitSensor) == HIGH)
    {
        processExit();
    }

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= lcdInterval)
    {
        previousMillis = currentMillis;

        displayStatus();
        sendBluetoothData();
    }
}

// =====================================================
// Vehicle Entry Processing
// =====================================================
void processEntry()
{
    if(occupiedSpaces < MAX_SPACES)
    {
        occupiedSpaces++;
        availableSpaces--;

        Serial.println("Vehicle Entered");

        tone(buzzer, 1000, 200);

        openGate();
        delay(3000);
        closeGate();

        updateIndicators();
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PARKING FULL");

        tone(buzzer, 2000, 1000);

        Serial.println("Parking Full");

        delay(2000);
    }

    delay(500);
}

// =====================================================
// Vehicle Exit Processing
// =====================================================
void processExit()
{
    if(occupiedSpaces > 0)
    {
        occupiedSpaces--;
        availableSpaces++;

        Serial.println("Vehicle Exited");

        tone(buzzer, 800, 200);

        openGate();
        delay(3000);
        closeGate();

        updateIndicators();
    }

    delay(500);
}

// =====================================================
// Open Gate
// =====================================================
void openGate()
{
    for(int pos = 0; pos <= 90; pos++)
    {
        gateServo.write(pos);
        delay(10);
    }
}

// =====================================================
// Close Gate
// =====================================================
void closeGate()
{
    for(int pos = 90; pos >= 0; pos--)
    {
        gateServo.write(pos);
        delay(10);
    }
}

// =====================================================
// LCD Display Function
// =====================================================
void displayStatus()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Occupied:");
    lcd.print(occupiedSpaces);

    lcd.setCursor(0,1);
    lcd.print("Free:");
    lcd.print(availableSpaces);
}

// =====================================================
// LED Status Indicators
// =====================================================
void updateIndicators()
{
    if(availableSpaces > 0)
    {
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
    }
    else
    {
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, HIGH);
    }
}

// =====================================================
// Bluetooth Monitoring
// =====================================================
void sendBluetoothData()
{
    BT.print("Occupied=");
    BT.print(occupiedSpaces);

    BT.print(",");

    BT.print("Available=");
    BT.println(availableSpaces);
}