/*
This file only contains the code to make the bot define basic movements liek front and right and left
More functionalities like self correcting path will be added in soon
The maze solving algo will be stored as a seperate file.

Please refer to: https://docs.arduino.cc/learn/contributions/arduino-creating-library-guide
on more info about storing code in multiple files.


*/


// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

//Sensor connections
int ftrig = A0;
int fecho = A1;
int rtrig = A2;
int recho = A3;
int ltrig = A4;
int lecho = A5;

void setup() {

  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  //Printing only for debugging purposes
  Serial.begin(115200);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);

  pinMode(ftrig,OUTPUT);
  pinMode(ltrig,OUTPUT);
  pinMode(rtrig,OUTPUT);
  pinMode(fecho,INPUT);
  pinMode(lecho,INPUT);
  pinMode(recho,INPUT);

}


/*
Time delays in the following functions are just for testing purposes.
As we progress this delay timer will be altered according to the dimentions
of the robot.
*/
void front(){
  //Bot goes front
  //Automatic PWM adjustments yet to be added
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
}

void uTurn(){
  //Bot takes U-Turn
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  delay(2000);
  front();
}
void right(){
  //Bot turns right
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  delay(2000);
  front();
}

void left(){
  //Bot turns left
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  delay(2000);
  front();
}


float distance(int trigPin, int echoPin){
  //To find the distance of wall from each ultrasonic sensor
  float duration,distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
}

void direction(float fdist,float rdist,float ldist){
  //Temporary direction finding algo
  //Left wall algo + pledge will soon replace this function
  if(fdist < 30){
    if(ldist > 30){
      Serial.println("left");
      left();
    }
    else if(rdist > 30){
      Serial.println("right");
      right();
    }
    else{
      Serial.println("uturn");
      uTurn();
    }
  }
  else{
    Serial.println("forward");
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  //More stuff to be added soom:tm:

  //Below two lines make the motors turn at max speed
  //Mostly no changes required as the max speed of motors is quite low
  analogWrite(enA,255);
  analogWrite(enB,255);
  front();

  direction(distance(ftrig,fecho),distance(rtrig,recho),distance(ltrig,lecho));

}
