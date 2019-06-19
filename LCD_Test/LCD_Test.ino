#define disply_time 1000
#define Rs 7
#define En 6
#define D4 5
#define D5 4
#define D6 3
#define D7 2


#include <LiquidCrystal.h>
LiquidCrystal lcd(Rs,En,D4,D5,D6,D7);

int duration,cm;

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
lcd.print("Hello,");

 // Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  //disply
  lcd.print("Hello,");
  lcd.setCursor(2,1);
  lcd.print("I am a robot");
  delay(disply_time);
  lcd.clear();

}
