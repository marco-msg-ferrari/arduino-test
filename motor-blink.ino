//Inclusione delle librerie
#include <Arduino.h>
#include <AccelStepper.h>

//Definizione costanti relative ai PIN
const int PIN_X_STEP = 2;
const int PIN_Y_STEP = 3;
const int PIN_Z_STEP = 4;
const int PIN_X_DIR = 5;
const int PIN_Y_DIR = 6;
const int PIN_Z_DIR = 7;

//Imposta velocità del asseX durante la fase di reset della posizione
const double MAX_SPEED = 1000.0; // Velocita rotazione

const int jX = 0;
const int jY = 1;
const int jZ = 2;

AccelStepper asseX(AccelStepper::DRIVER, PIN_X_STEP, PIN_X_DIR);
AccelStepper asseY(AccelStepper::DRIVER, PIN_Y_STEP, PIN_Y_DIR);
AccelStepper asseZ(AccelStepper::DRIVER, PIN_Z_STEP, PIN_Z_DIR);

long valX, mapX, valY, mapY, valZ, mapZ;

void setup() {
    asseX.setMaxSpeed(MAX_SPEED);
    asseX.setSpeed(MAX_SPEED);
    asseX.setAcceleration(MAX_SPEED * 3);

    asseY.setMaxSpeed(MAX_SPEED);
    asseY.setSpeed(MAX_SPEED);
    asseY.setAcceleration(MAX_SPEED * 3);
    
    asseZ.setMaxSpeed(MAX_SPEED);
    asseZ.setSpeed(MAX_SPEED);
    asseZ.setAcceleration(MAX_SPEED * 3);
}

void loop() {
    valX = analogRead(jX);
    mapX = map(valX, 0, 1023, MAX_SPEED, -1 * MAX_SPEED);

    valY = analogRead(jY);
    mapY = map(valY, 0, 1023, MAX_SPEED, -1 * MAX_SPEED);

    valZ = analogRead(jZ);
    mapZ = map(valZ, 0, 1023, MAX_SPEED, -1 * MAX_SPEED);

    if (abs(mapX) > 500) {
      asseX.setSpeed(mapX);
      asseX.run();
    } else {
      asseX.stop();
    }

    if (abs(mapY) > 500) {
      asseY.setSpeed(mapY);
      asseY.run();
    } else {
      asseY.stop();
    }

    if (abs(mapZ) > 500) {
      asseZ.setSpeed(mapZ);
      asseZ.run();
    } else {
      asseZ.stop();
    }
}
