//Inclusione delle librerie
#include <Arduino.h>
#include <AccelStepper.h>
#include <Bounce2.h>

//Definizione costanti relative ai PIN
const int PIN_X_STEP = 2;
const int PIN_X_DIR = 5;
const int PIN_UP_BTN = 8;
const int PIN_DOWN_BTN = 9;

//Imposta velocità del motore durante la fase di reset della posizione
const double SPEED_HOMING = 3000.0;

const unsigned long DEBOUNCE_DELAY = 10;

const int jX = 0;

//istanzia il motore
AccelStepper motore(AccelStepper::DRIVER, PIN_X_STEP, PIN_X_DIR);
Bounce btnUp = Bounce();  //Scelta risoluzione step
Bounce btnDown = Bounce();  //Scelta risoluzione step

int btnUpState = 0; 
int btnDownState = 0; 
long valX, mapX;

void setup() {
    Serial.begin(9600);
    pinMode(PIN_UP_BTN, INPUT_PULLUP);
    btnUp.attach(PIN_UP_BTN);
    btnUp.interval(DEBOUNCE_DELAY);
    
    pinMode(PIN_DOWN_BTN, INPUT_PULLUP);
    btnDown.attach(PIN_DOWN_BTN);
    btnDown.interval(DEBOUNCE_DELAY);

    motore.setMaxSpeed(SPEED_HOMING);
    motore.setSpeed(SPEED_HOMING);
    motore.setAcceleration(SPEED_HOMING * 3);
}

void loop() {
    valX = analogRead(jX);

    mapX = map(valX, 0, 1023, -1 * SPEED_HOMING, SPEED_HOMING);
  
    btnUpState = digitalRead(PIN_UP_BTN);
    btnDownState = digitalRead(PIN_DOWN_BTN);

    if (btnUpState == HIGH && btnDownState == HIGH) {
      motore.stop();
    } else if (btnUpState == LOW && btnDownState == LOW) {
        if (abs(mapX) > 500) {
          motore.setSpeed(mapX);
          motore.run();
        } else {
          motore.stop();
        }
    } else if (btnUpState == HIGH) {
      motore.setSpeed(SPEED_HOMING);
      motore.run();
    } else {
      motore.setSpeed(-1 * SPEED_HOMING);
      motore.run();
    }
}
