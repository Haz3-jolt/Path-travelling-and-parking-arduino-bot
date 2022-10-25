//All pin declarations
int IRL=0;
int IRR=2;
int trigpinL=4;
int echopinL=5;
int trigpinR=6;
int echopinR=7;
int L_enb=13;
int L1=8;
int L2=9;
int R_ena=12;
int R1=10;
int R2=11;
//Variables for ultrasonic sensor
long durationL,durationR;
int distanceL,distanceR;
//Setting up all the pins
void setup() 
{
  pinMode(IRL,INPUT);
  pinMode(IRR,INPUT);
  pinMode(trigpinL,OUTPUT);
  pinMode(echopinL,INPUT);
  pinMode(trigpinR,OUTPUT);
  pinMode(echopinR,INPUT);
  pinMode(L_enb,OUTPUT);
  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(R_ena,OUTPUT);  
  pinMode(R1,OUTPUT);
  pinMode(R2,OUTPUT);
  
  Serial.begin(9600);
  delay(1500);
 
}
//defining functionsfor movement
void forward()
{
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  analogWrite(L_enb, 150);
  analogWrite(R_ena, 150);
}
void turnleft()
{
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  analogWrite(L_enb, 255);
  analogWrite(R_ena, 255);
 
}
void turnright()
{
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  analogWrite(L_enb, 255);
  analogWrite(R_ena, 255);
}
void stop()
{
  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  
}
//functiom to stop after hitting parking line
void parking()
{
    forward();
    delay(700);
    stop();
    delay(3000);
}
//main loop
void loop() 
{
  //Calibrating ultrasonic sensor
  digitalWrite(trigpinL, LOW);
  delayMicroseconds(5);
  digitalWrite(trigpinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinL, LOW);

  durationL = pulseIn(echopinL, HIGH);
 
  distanceL = (durationL/2) / 29.1; 
  
  digitalWrite(trigpinR, LOW);
  delayMicroseconds(5);
  digitalWrite(trigpinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinR, LOW);

  durationR = pulseIn(echopinR, HIGH);
  
  distanceR = (durationR/2) / 29.1;
  //Main Algorithim 
  if ((digitalRead(IRL) == HIGH)&&(digitalRead(IRR) == HIGH))
   {
    if((distanceL<10)){turnright();}
    if((distanceL>10)&&(distanceR>10)){forward();}
    if((distanceR<10)){turnleft();}
   }
  if ((digitalRead(IRL) == LOW)&&(digitalRead(IRR) == HIGH))
   {
    turnright();
    }
   
  if ((digitalRead(IRL) == HIGH)&&(digitalRead(IRR) == LOW))
   {
    turnleft();
  }
  if ((digitalRead(IRL) == LOW)&&(digitalRead(IRR) == LOW))
  {
   parking();
  }
}
