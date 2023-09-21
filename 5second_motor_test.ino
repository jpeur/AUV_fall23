#include <Servo.h>

const int MAX_FORWARD = 180;
const int NEUTRAL = 90;

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
  Serial.println("Running motors 2 and 3");
  runTwoMotors(ESC2, ESC3, 5 * 1000); // Run motors 2 and 3 for 5 seconds
  
  delay(1000); // Optional delay between the motor groups
  
  Serial.println("Running motors 4 and 5");
  runTwoMotors(ESC4, ESC5, 5 * 1000); // Run motors 4 and 5 for 5 seconds

  delay(10000); // Delay 10 seconds before running the motors again
}

void runTwoMotors(Servo motor1, Servo motor2, int duration) {
  motor1.write(MAX_FORWARD); // Set motor1 to full forward
  motor2.write(MAX_FORWARD); // Set motor2 to full forward
  
  delay(duration); // Run motors for the specified duration
  
  motor1.write(NEUTRAL); // Stop motor1
  motor2.write(NEUTRAL); // Stop motor2
}
