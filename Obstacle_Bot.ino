//Motor Connections
//Right
int enableR = 3;
int in1R = 6;
int in2R = 7;
//Left
int enableL = 5;
int in1L = 8;
int in2L = 10;
//Sensor
int trig_pin = 2;//Trigger pin of the ultrasonic sensor
int echo_pin = 4;//Echo pin of the ultrasonic sensor

void setup()
{
  pinMode(enableR, OUTPUT);
  pinMode(in1R,OUTPUT);
  pinMode(in2R,OUTPUT);
  pinMode(enableL, OUTPUT);
  pinMode(in1L,OUTPUT);
  pinMode(in2L,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(trig_pin,OUTPUT);
}
void loop()
{
  long distance,duration,right_distance,left_distance;
  digitalWrite(trig_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin,HIGH);//Sending an ultrasonic pulse with the trigger pin
  delayMicroseconds(10);
  digitalWrite(trig_pin,LOW);
  duration = pulseIn(echo_pin,HIGH);//Using the inbuilt pulseIn function to get the time of when the echo 
  distance = (duration/2)/29.1;     //pulse was recieved. The echo pulse is recieved every 1x10^(-5) seconds  
  // The 29.1 is to convert the time recieved to centimeters 
  if (distance<20){// Checking for obstacle
    stop();
    delay(250);
    reverse();
    delay(250);
    sharp_right();//Turns right
    digitalWrite(trig_pin,LOW);
    delay(10);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    duration = pulseIn(echo_pin,HIGH);
    right_distance = (duration/2)/29.1;//Calculates the distance for the next obstacle on the right side
    sharp_left();//Returns to orginal position
    delay(250);
    sharp_left();//Turns left
    digitalWrite(trig_pin,LOW);
    delay(10);
    digitalWrite(trig_pin,HIGH);
    delayMicroseconds(10);
    duration = pulseIn(echo_pin,HIGH);
    left_distance = (duration/2)/29.1;//Calculates the distance for the next obstacle on the left side
    delay(250);
    sharp_right();//Returns to orginal position
    if(right_distance<=20 && left_distance<=20){//For a dead end
      reverse();
      delay(250);
      about_turn();//180 degree turn
      delay(250);
      front();
    }else if(right_distance<=left_distance){//Giving preference to right side if bothe the values are equal
      reverse();
      delay(250);
      sharp_right();
      delay(250);
      front();
    }else if(left_distance<right_distance){
      reverse();
      delay(250);
      sharp_left();
      delay(250);
      front();
    }
  }else if (distance>=20){//No obstacle
    front();
  }
}
void about_turn()
{
  digitalWrite(enableR,255);
  digitalWrite(enableL,255);
  digitalWrite(in1R,LOW);
  digitalWrite(in2R,HIGH);
  digitalWrite(in1L,HIGH);
  digitalWrite(in2L,LOW);
  delay(1200);
  hault();
  delay(1200);
}
void sharp_left()
{
  digitalWrite(enableR,255);
  digitalWrite(enableL,255);
  digitalWrite(in1R,LOW);
  digitalWrite(in2R,HIGH);
  digitalWrite(in1L,HIGH);
  digitalWrite(in2L,LOW);
  delay(500);
  hault();
  delay(500);
}
void sharp_right()
{
  digitalWrite(enableR,255);
  digitalWrite(enableL,255);
  digitalWrite(in1R,HIGH);
  digitalWrite(in2R,LOW);
  digitalWrite(in1L,LOW);
  digitalWrite(in2L,HIGH);
  delay(500);
  hault();
  delay(500);
}
void front()
{
  analogWrite(enableR,255);
  analogWrite(enableL,255);
  digitalWrite(in1R,HIGH);
  digitalWrite(in2R,LOW);
  digitalWrite(in1L,HIGH);
  digitalWrite(in2L,LOW);
}
void stop()
{
  analogWrite(enableR,255);
  analogWrite(enableL,255);
  digitalWrite(in1R,LOW);
  digitalWrite(in2R,LOW);
  digitalWrite(in1L,LOW);
  digitalWrite(in2L,LOW);
}
void reverse()
{
  analogWrite(enableR,255);
  analogWrite(enableL,255);
  digitalWrite(in1R,LOW);
  digitalWrite(in2R,HIGH);
  digitalWrite(in1L,LOW);
  digitalWrite(in2L,HIGH);
}
