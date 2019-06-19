#include <Wire.h>
#include<math.h>


//Left Motor Pins
#define lmp 8
#define lmn 9
#define L_EN 10

//Right Motor pins
#define R_EN 11
#define rmp 12
#define rmn 13

//Potentiometers to change Motor speeds
#define L_Potentio A1
#define R_Potentio A3

int L_Speed=0,R_Speed=0; // Stores Potentiometers' data


long accelX, accelY, accelZ;  //Collects the raw data from MPU
float gForceX, gForceY, gForceZ; //The raw data is processes to multiples of 'g'

long gyroX, gyroY, gyroZ; //Raw data from Gyro
float rotX, rotY, rotZ;  //Processed data in degrees/sec

float  Angle=0;

void setup() {
   Serial.begin(9600);
   
  pinMode(lmp,OUTPUT);
  pinMode(lmn,OUTPUT);
  pinMode(rmp,OUTPUT);
  pinMode(rmn,OUTPUT);
  
  pinMode(L_EN,OUTPUT);
  pinMode(R_EN,OUTPUT);
  
  pinMode(L_Potentio,INPUT);
  pinMode(R_Potentio,INPUT);
  
  Wire.begin();
  setupMPU();
}


void loop() {
  recordAccelRegisters();
  //recordGyroRegisters();
 // printData();

 Angle = acos(accelX/16384.00); // In Radians [0,pi]
 Angle = (Angle*180)/PI;  //Converts to angle
 Serial.println(Angle);

  L_Speed = analogRead(L_Potentio);
  R_Speed = analogRead(R_Potentio);

  L_Speed = map(L_Speed, 0, 1023, 60, 255);
  R_Speed = map(R_Speed, 0, 1023, 60, 255);

 if(Angle < 85)
 {
   backward(L_Speed,R_Speed);
 }

 if(Angle > 95)
 {
   forward(L_Speed,R_Speed);
 }

 else
 {
  Brake();
 }
  delay(4);
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
 // processAccelData();
}

void processAccelData(){
  gForceX = (245*accelX) / 4096.00;
  gForceY = (245*accelY) / 4096.00; 
  gForceZ = (245*accelZ) / 4096.00;
}

void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processGyroData();
}

void processGyroData() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
}

int forward(int L_Speed, int R_Speed)
{
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,LOW);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,LOW);
  
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);
  
  Serial.print("Forward");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("     ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  
}

 int backward(int L_Speed, int R_Speed)
  {
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,HIGH);
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);
  
  Serial.print("Backward");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("     ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  
  }    
  int stops()
  {
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,LOW);
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,LOW);
  Serial.println("Stopped");
  }

int left(int L_Speed,int R_Speed)
{
   digitalWrite(lmp,HIGH);
  digitalWrite(lmn,LOW);
   digitalWrite(rmn,LOW);
  digitalWrite(rmp,HIGH);

  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,L_Speed);
  
  Serial.print("Left");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("   ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  
}

int right(int L_Speed,int R_Speed)
{
   digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,LOW);
 
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);
  
  Serial.print("Left");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("   ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
}

int Brake()
{
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,HIGH);
  Serial.println("Brake");
}


