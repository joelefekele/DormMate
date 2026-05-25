#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String firstName = "";
String lastName = "";
int state = 0; // 0 = waiting for first name, 1 = waiting for last name

//Automatic Nightlight
const int YLED=7;        //Red LED on pin 9 (PWM)
const int LIGHT=0;       //Lght Sensor on analog pin 0
int val = 0;             //variable to hold the analog reading
int val1=0;
// TIMER CONTROL
const unsigned long SECONDS = 60000;// 1 MINUTE
unsigned long previousTime= 0;
int H =4;// HOURS
int M = 12;//MINUTES


void setup() {
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 // initialize the serial communications:
 Serial.begin(9600);
 //lcd.print("Enter First Name");
 pinMode(YLED, OUTPUT); //Set LED pin as output
}
void loop() {
unsigned long currentTime = millis();// timer
val = analogRead(LIGHT); //Read the light sensor
 // when characters arrive over the serial port...
 if (val<500) {
 digitalWrite(YLED,1);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("TIME ");lcd.print(H);lcd.print(":");lcd.print(M);
 lcd.setCursor(0, 1);
 lcd.print("Room dark");
 /*lcd.setCursor(0, 1);
 lcd.print(val);

 delay(100);*/
 }
 
  else{
    digitalWrite(YLED,0);
     lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print("TIME ");lcd.print(H);lcd.print(":");lcd.print(M);
    lcd.setCursor(0, 1);
    lcd.print("Room bright");
     /*lcd.setCursor(0, 1);
      lcd.print(val);

      delay(100);*/
  }
  delay(1000);
    if(currentTime - previousTime >= SECONDS ){

    M=M+1;
    previousTime=currentTime;

  }
  if(M== 60){
    H=H+1;
    M=0;
  }
}

