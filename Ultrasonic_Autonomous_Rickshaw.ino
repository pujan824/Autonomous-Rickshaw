// defines pins numbers

// ultrasonic sensor
const int trigPin = 11;
const int echoPin = 12;

//L298N motor controller
const int enA = 9;
const int in1 = 4;
const int in2 = 5;
const int enB = 10;
const int in3 = 6;
const int in4 = 7;

// defines variables
long duration;
int distance;

void setup() {
  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

//motor 1 setup as outputs
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);

// initializes direction of motor 1
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

//motor 2 setup as output
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);

// inititializes direction of motor 2
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

}

void loop() {
  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds (sends signal)
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);

// checks if it is too close to an object then backs up and turns around it 
if(distance<7){
  Stop(); // stops motor 1
  reverse(); // reverses the rickshaw
  delay(5000); // delays nect instruction
  Stop(); // stops motor 1
  turnRight(); // steers cart right until hardstop
  delay(1000); 
  stopTurning(); // stops motor 2
  forward(); // moves rickshaw forward
  delay(15000); 
  Stop(); // stops motor 1
  returnToStraight(); // moves steering to straight
  delay(1100);
  stopTurning(); // stops turning

}
// if there is no object directly in front, rickshaw moves forward
else{
  forward();
}


}
// method to move forward
void forward(){
  analogWrite(enA,200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.print("walking forward");
}
// method to stop motor 1
void Stop(){
  analogWrite(enA,0);
}
// reverses the rickshaw
void reverse(){
  analogWrite(enA,200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.print("reversing");
}
// steers the rickshaw to the right
void turnRight(){
  analogWrite(enB,200);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.print("turning right");
}
//returns steering to straight
void returnToStraight(){
  analogWrite(enB, 200);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.print("returning to straigt orientation");
}
// stops turning
void stopTurning(){
  analogWrite(enB, 0);
}
