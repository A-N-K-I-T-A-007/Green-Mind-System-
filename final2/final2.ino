#include <ESP32Servo.h>
#include <Stepper.h>

// --- Physical Pin Configuration ---
const int metalSensorPin = 32;   // Inductive Proximity Metal Sensor (Digital IN, active LOW)
const int moisturePin    = 35;   // Make sure your physical wire is moved to Pin 34!
const int irSensorPin    = 33;   // IR Drop Zone Sensor (Digital IN)
const int servoPin       = 13;
const int buzzerPin      = 12;

// --- Stepper Motor Settings (28BYJ-48) ---
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 19, 21, 18, 17);
const int stepsToMove = 1365; // ~240 degrees

// --- Servo Settings ---
Servo lidServo;
const int lidClosedAngle = 35;
const int lidOpenAngle   = 180;

// --- MOISTURE CALIBRATION VALUES ---
int dryRaw = 4000;   // Set this based on your empty/dry air reading
int wetRaw = 1500;   // Set this based on your wet test reading
const int wetThresholdPercent = 20;

int readMoisturePercent() {
  long total = 0;
  for (int i = 0; i < 5; i++) {
    total += analogRead(moisturePin);
    delay(20);
  }
  int raw = total / 5;
  raw = constrain(raw, wetRaw, dryRaw);
  int percent = map(raw, dryRaw, wetRaw, 0, 100);
  
  Serial.print("Raw Analog ADC: "); Serial.print(raw);
  Serial.print(" | Calculated Moisture: "); Serial.print(percent); Serial.println("%");
  return percent;
}

void openCloseLid() {
  Serial.println("Opening Lid...");
  lidServo.write(lidOpenAngle);
  delay(2000);
  Serial.println("Closing Lid...");
  lidServo.write(lidClosedAngle);
  delay(1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(metalSensorPin, INPUT_PULLUP);
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  ESP32PWM::allocateTimer(0);
  lidServo.setPeriodHertz(50);
  lidServo.attach(servoPin, 500, 2400);

  lidServo.write(180);
  delay(2000);
  lidServo.write(lidClosedAngle);
  delay(1000);

  myStepper.setSpeed(15);
  Serial.println("    ESP32 CORE-CORRECTED WASTESYS V5    ");
}

void loop() {
  int isMetal = (digitalRead(metalSensorPin) == LOW);
  int moisturePercent = readMoisturePercent();

  // --- 1. METAL SEQUENCE ---
  if (isMetal) {
    Serial.println("\n[!] TARGET MATCH: METAL");
    tone(buzzerPin, 1000, 1000);
    
    Serial.println("Rotating tray to Metal Bin...");
    myStepper.step(-stepsToMove);
    delay(1000);
    
    Serial.println("Waiting for Drop Zone IR sensor to confirm alignment...");
    while (digitalRead(irSensorPin) == HIGH) delay(50);
    
    openCloseLid();
    
    Serial.println("Returning to Home...");
    myStepper.step(stepsToMove);
    delay(1000);
    Serial.println("[SYSTEM] Reset complete.");
  }
  
  // --- 2. WET WASTE SEQUENCE ---
  else if (moisturePercent > wetThresholdPercent) {
    Serial.println("\n[!] TARGET MATCH: WET WASTE");
    tone(buzzerPin, 1000, 500);
    
    Serial.println("Rotating tray to Wet Bin...");
    myStepper.step(stepsToMove);
    delay(1000);
    
    Serial.println("Waiting for Drop Zone IR sensor to confirm alignment...");
    while (digitalRead(irSensorPin) == HIGH) delay(50);
    
    openCloseLid();
    
    Serial.println("Returning to Home...");
    myStepper.step(-stepsToMove);
    delay(1000);
    Serial.println("[SYSTEM] Reset complete.");
  }
  
  // --- 3. DRY WASTE ROUTINE (FALLBACK) ---
  // If platform is clear of metal and moisture, but item breaks the IR beam at Home
  else if (digitalRead(irSensorPin) == LOW) {
    Serial.println("\n[!] TARGET MATCH: DRY WASTE (Direct Drop at Home)");
    tone(buzzerPin, 1000, 500);
    openCloseLid();
    Serial.println("[SYSTEM] Reset complete.");
  }

  delay(200); // Prevents serial monitoring flood
}
