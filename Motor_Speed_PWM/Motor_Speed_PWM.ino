#define Print_Motors_Speed 1

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
#define M_Potentio A2
#define R_Potentio A3

int L_Speed=0,R_Speed=0;
int data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(lmp,OUTPUT);
  pinMode(lmn,OUTPUT);
  pinMode(rmp,OUTPUT);
  pinMode(rmn,OUTPUT);
  
  pinMode(L_EN,OUTPUT);
  pinMode(R_EN,OUTPUT);
  
  pinMode(L_Potentio,INPUT);
  pinMode(R_Potentio,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  L_Speed = analogRead(L_Potentio);
  R_Speed = analogRead(R_Potentio);
  data = analogRead(M_Potentio);
  
  L_Speed = map(L_Speed, 0, 1023, 60, 255);
  R_Speed = map(R_Speed, 0, 1023, 60, 255);

if( data > 700)
{
  forward(L_Speed,R_Speed);
}

if(data < 400)
{
  backward(L_Speed,R_Speed);  
}

else
{
  Brake();
  
}
}


int forward(int L_Speed, int R_Speed)
{
  //L_Speed = (L_Speed + R_Speed)/2;     L_Speed = R_Speed;
  
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,LOW);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,LOW);
  
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);

  #if Print_Motors_Speed
  Serial.print("Forward");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("     ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  #endif
  
}

 int backward(int L_Speed , int R_Speed)
  {

    //L_Speed = (L_Speed + R_Speed)/2;     L_Speed = R_Speed;
    
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,HIGH);
  
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);

  #if Print_Motors_Speed
  Serial.print("Backward");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("     ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  #endif
}    
  int stops()
  {
    
  digitalWrite(lmp,LOW);
  digitalWrite(lmn,LOW);
  digitalWrite(rmn,LOW);
  digitalWrite(rmp,LOW);
  
  #if Print_Motors_Speed
  Serial.println("Stopped");
  #endif
  }

int left(int L_Speed,int R_Speed)
{
   digitalWrite(lmp,HIGH);
   digitalWrite(lmn,LOW);
   digitalWrite(rmn,LOW);
   digitalWrite(rmp,HIGH);

  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,L_Speed);

  #if Print_Motors_Speed
  Serial.print("Left");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("   ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  #endif
}

int right(int L_Speed,int R_Speed)
{
   digitalWrite(lmp,LOW);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,LOW);
 
  analogWrite(L_EN,L_Speed);
  analogWrite(R_EN,R_Speed);
  
  #if Print_Motors_Speed
  Serial.print("Left");
  Serial.print("   ");
  Serial.print("L_Speed= ");
  Serial.print(L_Speed);
  Serial.print("   ");
  Serial.print("R_Speed= ");
  Serial.println(R_Speed);
  #endif
  
}

int Brake()
{
  digitalWrite(lmp,HIGH);
  digitalWrite(lmn,HIGH);
  digitalWrite(rmn,HIGH);
  digitalWrite(rmp,HIGH);

  digitalWrite(L_EN,HIGH);
  digitalWrite(R_EN,HIGH);
  
  #if Print_Motors_Speed
  Serial.println("Brake");
  #endif
}



