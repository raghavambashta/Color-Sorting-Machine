#include<Servo.h>
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Variables for Color Pulse Width Measurements
Servo topServo;
Servo bottomServo;

int R = 0;
int G = 0;
int B = 0;
bool isempty=false;

void setup() {
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  topServo.attach(2);
  bottomServo.attach(10);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);
}

void loop() {
  
  topServo.write(90);
  for(int i = 90; i >=30; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  for(int i=0;i<6;i++)
  {
    // Read Red Pulse Width
  R = getRedPW();
  // Delay to stabilize sensor
  delay(200);

  // Read Green Pulse Width
  G = getGreenPW();
  // Delay to stabilize sensor
  delay(200);

  // Read Blue Pulse Width
  B = getBluePW();
  // Delay to stabilize sensor
  delay(200);

  // Print output to Serial Monitor
  if(i<5)
  {
    Serial.print("R = ");
    Serial.print(R);
    Serial.print(" - G = ");
    Serial.print(G);
    Serial.print(" - B = ");
    Serial.println(B);
  }
  else
  {
    if(R<=120 && R>=110 && B>=300 && B<=310)
       {
          Serial.println("Orange");
          bottomServo.write(30);
       }
    else if(R<=140 && R>=130 && G>=380 && G<=400)
      {
            Serial.println("Pink");
            bottomServo.write(0); 
      }
    else if(R<=360 && R>=340 && B<=170 && B>=150)
     {
      Serial.println("Blue");
          bottomServo.write(90);
     }
     else if(R>=390 && R<=400 && G<=645 && G>=620)
     {
      Serial.println("Violet);
        bottomServo.write(60);
     }
    else if(R<250 && B<250 && G<250)
      {
        Serial.println("Empty");
        isempty=true;
      }
     else
     {
       bottomServo.write(90);
     }
  }
  }

  if(!isempty)
  {
    delay(500);
  for(int i = 30; i >=0; i--) {
    topServo.write(i);
    delay(4);
  } 
  
  delay(200);
  for(int i =0; i <=90; i++) {
    topServo.write(i);
    delay(2);
  }
    delay(500);
  }
  else
  {
    for(int i=30;i<=90;i++)
      {
        topServo.write(i);
        delay(4);
      }
     exit(0);
  }
}

// Function to read Red Pulse Widths
int getRedPW() {
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
}
