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

int L_Brake_Strength = 0, R_Brake_Strength = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(lmp, OUTPUT);
  pinMode(lmn, OUTPUT);
  pinMode(rmp, OUTPUT);
  pinMode(rmn, OUTPUT);
  
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  
  pinMode(L_Potentio, INPUT);
  pinMode(R_Potentio, INPUT);
  
  pinMode(2,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  L_Brake_Strength = analogRead(L_Potentio);
  R_Brake_Strength = analogRead(R_Potentio);

  L_Brake_Strength = map(L_Brake_Strength, 0, 1023, 0, 255);
  R_Brake_Strength = map(R_Brake_Strength, 0, 1023, 0, 255);

 if(digitalRead(2) == HIGH)
 {
  lows(L_Brake_Strength, R_Brake_Strength);
  delay(50);
 }

  if(digitalRead(3) == HIGH)
 {
  highs(L_Brake_Strength,R_Brake_Strength);
  delay(50);
 }

  else
  {
    loose();
  }

  //lows(L_Brake_Strength, R_Brake_Strength);
  //highs(L_Brake_Strength,R_Brake_Strength);
  //loose();
  delay(10);
}

int highs(int L_Brake, int R_Brake)
{
  digitalWrite(lmp, HIGH);
  digitalWrite(lmn, HIGH);
  digitalWrite(rmn, HIGH);
  digitalWrite(rmp, HIGH);

  analogWrite(L_EN, L_Brake);
  analogWrite(R_EN, R_Brake);

  Serial.println("Highs");
}

int lows(int L_Brake, int R_Brake)
{
  digitalWrite(lmp, LOW);
  digitalWrite(lmn, LOW);
  digitalWrite(rmn, LOW);
  digitalWrite(rmp, LOW);

  analogWrite(L_EN, L_Brake);
  analogWrite(R_EN, R_Brake);

  Serial.println("Lows");
}

void loose()
{
  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);
  Serial.println("Brakes_Released");
}

