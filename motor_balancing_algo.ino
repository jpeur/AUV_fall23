void loop() {
  delay(10);


  if (bno08x.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }


  if (!bno08x.getSensorEvent(&sensorValue)) {
    return;
  }


  float accelX = 0.0;
  float accelY = 0.0;


  switch (sensorValue.sensorId) {
  case SH2_ACCELEROMETER:
    // delay(1000);
    Serial.print("Accelerometer - x: ");
    accelX = sensorValue.un.accelerometer.x;
    Serial.println(accelX);
   
    Serial.print("Accelerometer - y: ");
    accelY = sensorValue.un.accelerometer.y;
    Serial.println(accelY);


    if(accelX > 0) {
      s4 = 120;
      s5 = (accelX * 7) + 120;
    }


    if(accelX < 0) {
      s4 = -(accelX * 7) + 120;
      s5 = 120;
    }


    if(accelY > 0) {
      s2 = 120;
      s3 = (accelY * 7) + 120;
    }


    if(accelY < 0) {
      s2 = -(accelY * 7) + 120;
      s3 = 120;
    }


    Serial.println(s2);
    Serial.println(s3);
    Serial.println(s4);
    Serial.println(s5);


    moveMotor(ESC4, s2, TIME_TO_MOVE);
    moveMotor(ESC4, s3, TIME_TO_MOVE);
    moveMotor(ESC4, s4, TIME_TO_MOVE);
    moveMotor(ESC5, s5, TIME_TO_MOVE);
    break;
  }
}


void moveMotor(Servo motor, int targetSpeed, int timeLeft) {
  int startSpeed = motor.read();
  if(targetSpeed == startSpeed) return;


  int newSpeed;
  if(targetSpeed > startSpeed) {
    newSpeed = startSpeed + 1;
  } else if(targetSpeed < startSpeed) {
    newSpeed = startSpeed - 1;
  }
  motor.write(newSpeed);


  int timeInterval = abs(timeLeft/(targetSpeed - startSpeed));
  int shortDelay = max(SHORTEST_DELAY, timeInterval);
  int longDelay = max(MAGIC_DELAY, timeInterval);


  delay(shortDelay);
  timeLeft -= shortDelay;
  if(newSpeed == NEUTRAL && targetSpeed < NEUTRAL) {
    motor.write(MAGIC_SPEED);
    delay(longDelay);
    timeLeft -= longDelay;
    motor.write(NEUTRAL);
  }
  moveMotor(motor, targetSpeed, timeLeft);
}
