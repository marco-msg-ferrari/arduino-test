//Inclusione delle librerie
#include <Arduino.h>
#include <AccelStepper.h>

//Definizione costanti relative ai PIN
const int PIN_X_STEP = 2;
const int PIN_X_DIR = 5;

//Imposta velocità del motore durante la fase di reset della posizione
const double SPEED_HOMING = 1600.0;

//istanzia il motore
AccelStepper motore(AccelStepper::DRIVER, PIN_X_STEP, PIN_X_DIR);

void setup() {
    motore.setMaxSpeed(SPEED_HOMING);
    motore.setSpeed(SPEED_HOMING);
    motore.setAcceleration(SPEED_HOMING * 3);
}

void loop() {
    if (motore.distanceToGo() == 0)
    {
      delay(1000);
      motore.move(1600);
    }

    motore.run();
}
