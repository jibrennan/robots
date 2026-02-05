//Basic meccanoid function, rotates the servo leds and holds the arms at 90 degrees, even if the user moves them. 

#include <Meccanoid.h>

/* typedefs for convenience */
typedef MeccanoServo Servo;
typedef MeccanoLed   Led;

/* Note that their needs to be a 22k ohm pull-up resistor on chain input,
 * See http://www.meccano.com/meccanoid-opensource Smart Module Protocol 
 * (bottom of PDF) for more details. */
 
/* PWM pin for chain */
int pinL = 8; //left servo chain
int pinR = 7; //right servo chain
int pinD = 6; //LED servo chain

int currentPosition; 

//
bool servoIsConnected = false;

/* define chain and PWM pin for it */
Chain chain1(pinL);  // left chain
Chain chain2(pinR);  // right chain
Chain chain3(pinD);  // LED chain

/* define modules to use and their positions */
Servo servo1 = chain1.getServo(0); // first on chain 1  (0)
Servo servo2 = chain1.getServo(1); // second on chain 1 (1)
Servo servo3 = chain2.getServo(0); // first on chain 2 (0)
Servo servo4 = chain2.getServo(1); // second on chain 2 (1)
Led led =      chain3.getLed(0);   // first on chain 3 (0)

int step = 0;

void setup() {
  // startup serial
  Serial.begin(9600);

  // seed random number generator for led
  randomSeed(analogRead(0));
 
  Serial.println("MECCANOID_JB V1.0.0 8-16-2025");
  Serial.println("I need a 5V 2A power supply connectd to me, I cannot operate over USB power!"); 
  Serial.println("Setup is complete.");
}

void loop() {
  // update chain to poll for input
  chain1.update();
  chain2.update();
  chain3.update();

  // invoke our local servo updator method
  updateServo(servo1, 1, 180);
  updateServo(servo2, 2, 0);
  updateServo(servo3, 3, 0);
  updateServo(servo4, 4, 180);
  updateLed(step);
  
  delay(200);
  
  step++;
}

void updateServo(Servo servo, int servoNum, int angle) {
  if (servo.justConnected()) {

    // log status
    Serial.print("Servo ");
    Serial.print(servoNum);
    Serial.print(" : ");
    Serial.println("Servo connected!");

    servo.setPosition(angle); 

    // let servo reach position
    delay(500);
    
    // make servo floppy
    servo.setLim(true);
  }

  if (servo.isConnected()) {

    // log status
    Serial.print("Servo ");
    Serial.print(servoNum);
    Serial.print(" : ");
    currentPosition = servo.getPosition();
    Serial.print(currentPosition);
    if (servoNum == 4){
      Serial.println(".");
    }
    if ((currentPosition <= angle-5) || (currentPosition >= angle +5)){ 
      servo.setPosition(angle); 
      // let servo reach position
    delay(200);
    }
    // change colors every 10 steps
    if (step % 10 == 0) {
      int c = (step / 10) % 8;
      servo.setColor(c, c >> 1, c >> 2);
    }
  }
    // make servo floppy
    servo.setLim(true);
}

void updateLed(int stepCount){
   if (led.justConnected()) {
    Serial.println("LEDs connected! Setting the color...");
    led.setColor(0x07, 0x01, 0x01, 0x00);
  }

  if (led.isConnected()) {
    // change to random color every 15 steps
    if (stepCount % 15 == 0) {
      led.setColor(random(8), random(8), random(8), 0);
    }
  }
}
