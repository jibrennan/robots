

#include <SoftwareSerial.h> //Software Serial Port
SoftwareSerial blueToothSerial(6,7);

//#define DEBUG_ENABLED 1

int pinI1=8;//define I1 interface
int pinI2=11;//define I2 interface 
int speedpinA=9;//enable motor A
int pinI3=12;//define I3 interface 
int pinI4=13;//define I4 interface 
int speedpinB=10;//enable motor B
int spead =95;//define the spead of motor
int i = 0;
char command [64];
 

void setup()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(speedpinB,OUTPUT);
  Serial.begin(9600);
  setupBlueToothConnection();
  clearserialbuffer();
}
void setupBlueToothConnection()
{
blueToothSerial.begin(9600); // Set BluetoothBee BaudRate to default baud rate 38400
blueToothSerial.print("\r\n+STWMOD=0\r\n"); // set the bluetooth work in slave mode
//blueToothSerial.print("\r\n+STNA=HC-05\r\n"); // set the bluetooth name as "SeeedBTSlave"
blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
delay(2000); // This delay is required.
blueToothSerial.print("\r\n+INQ=1\r\n"); // make the slave bluetooth inquirable
Serial.println("The slave bluetooth is inquirable!");
delay(2000); // This delay is required.
blueToothSerial.flush();
} 
 
void forward()
{
     analogWrite(speedpinA,spead);//input a simulation value to set the speed
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
}
void backward()//
{
     analogWrite(speedpinA,spead);//input a simulation value to set the speed
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void left()//
{
     analogWrite(speedpinA,spead);//input a simulation value to set the speed
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void right()//
{
     analogWrite(speedpinA,spead);//input a simulation value to set the speed
     analogWrite(speedpinB,spead);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     digitalWrite(pinI2,LOW);//turn DC Motor A move clockwise
     digitalWrite(pinI1,HIGH);
}
void stop()//
{
     digitalWrite(speedpinA,LOW);// Unenble the pin, to stop the motor. this should be done to avid damaging the motor. 
     digitalWrite(speedpinB,LOW);
     delay(1000);
 
}

void clearserialbuffer()
{
  for (int i= 0; i<64; i++)
  {
    command[i] = NULL;  
  }
}

void loop()
{
  if(blueToothSerial.available())
  {//check if there's any data sent from the remote bluetooth shield
    char command = blueToothSerial.read();
  
  switch (command) 
  { 
  case ' ':
   stop(); 
  break;
  
  case 'w':
  forward();
  break;
  
  case 's':
  backward();
  break;
  
  case 'd':
  right();
  break;
  
  case 'a':
  left();
  break;
  
  }
  
  }
}
