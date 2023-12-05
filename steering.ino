#include <Servo.h>

// assumes motors attaching to 2, 3, 4, 5
// assumes motor 2 is on the left side and helps move forward and backward, or rotate counterclockwise around z-axis
// assumes motor 3 is on the right side and helps move forward and backward, or rotate clockwise around z-axis
// assumes motor 4 is on the top and helps move up and down
// assumes motor 5 is on the top and helps move up and down

const int TIME_TO_MOVE = 500; // Time to move in milliseconds
const int MAX_REVERSE = 16;
const int MAX_FORWARD = 180;
const int NEUTRAL = 90;
const int SHORTEST_DELAY = 5;
const int MAGIC_SPEED = 35;
const int MAGIC_DELAY = 150;

Servo ESC2, ESC3, ESC4, ESC5;
int s2 = NEUTRAL;
int s3 = NEUTRAL;
int s4 = NEUTRAL;
int s5 = NEUTRAL;

void setup() {
  Serial.begin(9600);
  Serial.println("begin");

  ESC2.attach(2,600,2250);
  ESC3.attach(3,600,2250);
  ESC4.attach(4,600,2250);
  ESC5.attach(5,600,2250);

  ESC2.write(s2);
  ESC3.write(s3);
  ESC4.write(s4);
  ESC5.write(s5);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

    if (command == "forward") {
      moveForward(50); // Adjust speed as necessary
    } else if (command == "backward") {
      moveBackward(50); // Adjust speed as necessary
    } else if (command == "rotatecw") { // rotate clockwise
      rotateClockwise(50); // Adjust speed as necessary
    } else if (command == "rotateccw") { // rotate counterclockwise
      rotateCounterclockwise(50); // Adjust speed as necessary
    } else if (command == "stop") {
      stopAllMotors();
    }
    printMotorSpeeds();
  }
}

// move forward
void moveForward(int speed) {
  s2 = s3 = NEUTRAL + speed;
  s4 = s5 = NEUTRAL;
}

// move backward
void moveBackward(int speed) {
  s2 = s3 = NEUTRAL - speed;
  s4 = s5 = NEUTRAL;
}

// rotate clockwise
void rotateClockwise(int speed) {
  s2 = NEUTRAL - speed;
  s3 = NEUTRAL + speed;
  s4 = s5 = NEUTRAL;
}

// rotate counterclockwise
void rotateCounterclockwise(int speed) {
  s2 = NEUTRAL + speed;
  s3 = NEUTRAL - speed;
  s4 = s5 = NEUTRAL;
}

// stops all motors
void stopAllMotors() {
  s2 = s3 = s4 = s5 = NEUTRAL;
}

void printMotorSpeeds() {
    Serial.print("s2: ");
    Serial.println(s2);
    Serial.print("s3: ");
    Serial.println(s3);
    Serial.print("s4: ");
    Serial.println(s4);
    Serial.print("s5: ");
    Serial.println(s5);
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