```cpp
/*
--------------------------------------------------------
SMART NEO BABY INCUBATOR
Author: Ranken Chisambi

Features:
- Temperature Monitoring
- LCD Display (16x2)
- Ceramic Heater Control
- Cooling Fan Control
- Audible Alarm
- Adjustable Temperature Setpoint
- Safety Monitoring
--------------------------------------------------------
*/

#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin Definitions
const int tempSensorPin = A0;
const int setpointPin   = A1;

const int heaterPin     = 8;
const int fanPin        = 9;
const int buzzerPin     = 10;

// Temperature Variables
float temperature = 0.0;
float setPoint = 37.0;

// Safety Limits
const float HIGH_TEMP_LIMIT = 39.0;
const float LOW_TEMP_LIMIT  = 35.0;

// Timing Variables
unsigned long previousMillis = 0;
const long lcdInterval = 1000;

void setup()
{
    pinMode(heaterPin, OUTPUT);
    pinMode(fanPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);

    digitalWrite(heaterPin, LOW);
    digitalWrite(fanPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.begin(16, 2);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SMART NEO");
    lcd.setCursor(0, 1);
    lcd.print("INCUBATOR");

    delay(3000);

    lcd.clear();

    Serial.begin(9600);
}

void loop()
{
    readTemperature();
    readSetpoint();

    temperatureControl();
    safetyMonitoring();

    updateLCD();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C | Setpoint: ");
    Serial.println(setPoint);

    delay(500);
}

void readTemperature()
{
    int sensorValue = analogRead(tempSensorPin);

    float voltage = sensorValue * (5.0 / 1023.0);

    temperature = voltage * 100.0;
}

void readSetpoint()
{
    int potValue = analogRead(setpointPin);

    setPoint = map(potValue, 0, 1023, 350, 380);

    setPoint = setPoint / 10.0;
}

void temperatureControl()
{
    if (temperature < setPoint - 0.5)
    {
        digitalWrite(heaterPin, HIGH);
        digitalWrite(fanPin, LOW);
    }
    else if (temperature > setPoint + 0.5)
    {
        digitalWrite(heaterPin, LOW);
        digitalWrite(fanPin, HIGH);
    }
    else
    {
        digitalWrite(heaterPin, LOW);
        digitalWrite(fanPin, LOW);
    }
}

void safetyMonitoring()
{
    if (temperature >= HIGH_TEMP_LIMIT)
    {
        digitalWrite(heaterPin, LOW);

        tone(buzzerPin, 1000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WARNING!");
        lcd.setCursor(0,1);
        lcd.print("HIGH TEMP");

        delay(2000);
    }
    else if (temperature <= LOW_TEMP_LIMIT)
    {
        tone(buzzerPin, 800);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WARNING!");
        lcd.setCursor(0,1);
        lcd.print("LOW TEMP");

        delay(2000);
    }
    else
    {
        noTone(buzzerPin);
    }
}

void updateLCD()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= lcdInterval)
    {
        previousMillis = currentMillis;

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print("Temp:");
        lcd.print(temperature,1);
        lcd.print((char)223);
        lcd.print("C");

        lcd.setCursor(0,1);
        lcd.print("Set:");
        lcd.print(setPoint,1);
        lcd.print((char)223);
        lcd.print("C");
    }
}
```
