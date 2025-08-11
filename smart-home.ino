#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 6
#define DHTTYPE    DHT11    

#define ldrPin A0
#define ledPin1 3
//#define ledPin2 A6
#define greenled A3

#define dcMotorPin 9
#define pushbutton 4

#define normalThreshold 28.0
#define alarmThreshold 30.1

#define OutIRSensor A1
#define inIRSensor A2

#define buzzer 5
#define tembuzzer 8

int a,i,j,s,l,k,c; //CHANGE
int count = 0; 
float temperature;
#define servoPin 7
#define servoPin2 2

const byte ROWS = 2;
const byte COLS = 2;
char keys[ROWS][COLS] =
{
 {'1', '2'},
 {'4', '5'}
};
int passcorrect = 0;
Servo sg90;
Servo sg90out;

char password[]= {'5','5','5','5'};
char pass[4],pass1[4];

char customKey = 0, key =0;
int ldrValue;
int o;
int brightnessLevel;
int sensorStatus1 =1;
int sensorStatus2 =1;
byte rowPins[ROWS] = {10,11};
byte colPins[COLS] = {12,13};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27, 16, 2);  
DHT_Unified dht(DHTPIN, DHTTYPE);


void setup(){
 Serial.begin(9600); 
 pinMode(buzzer, OUTPUT);
 pinMode(tembuzzer, OUTPUT);
 pinMode(greenled, OUTPUT);
 
  
   dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
 lcd.backlight();
 lcd.clear();
 sg90.attach(servoPin);  //Declare pin 5 for servo
 sg90out.attach(servoPin2);
 sg90.write(90);// Set initial position at 0 degrees
 sg90out.write(90);
  pinMode(servoPin, OUTPUT);
  pinMode(dcMotorPin, OUTPUT);
 pinMode(servoPin2, OUTPUT);
 pinMode(pushbutton, INPUT);
 pinMode(OutIRSensor, INPUT);
 pinMode(inIRSensor, INPUT);
 mhcho();

}

void loop(){
  digitalWrite(tembuzzer,LOW);
       digitalWrite(dcMotorPin, LOW);
  delay(1000);
 for(o=0;o<10;o++){
   delay(1000);
  sensorStatus1 = digitalRead(OutIRSensor); // Set the GPIO as Input
   sensorStatus2 = digitalRead(inIRSensor);
  if (sensorStatus1 == 0) // Check if the pin high or not
  {
     lcd.clear();
 lcd.print("Open Door");
   delay(10);
   sg90.write(0);
   delay(5000);
   sg90.write(90);
 lcd.clear();
 lcd.print("Close Door"); 
  }
  if (sensorStatus2 == 0) // Check if the pin high or not
  {
    lcd.clear();
 lcd.print("Open Door");
   delay(10);
   sg90.write(180);
   delay(5000);
   sg90.write(90);
 lcd.clear();
 lcd.print("Close Door"); 
 delay(1000);
  }}
 customKey = keypad.getKey();      
 if(!passcorrect){
  if(count!=0){
    digitalWrite(buzzer,HIGH);
  
  }
 }
 pressedPassword();
  checkPassword();
}


void OpenDoor(){             
 lcd.clear();
 lcd.print("Open Door");
 delay(10);
 sg90out.write(0);
 delay(5000);
 sg90out.write(90);
 lcd.clear();
 lcd.print("Close Door");   
         
 }
void mhcho(){
  j=0;
 lcd.init();
 lcd.clear();
 lcd.print("Wellcome...");
 lcd.setCursor(0,1);
 lcd.print("Have a good day");
 lcd.setCursor(1,0); 
}

/*void keypadEvent(KeypadEvent eKey){
 switch (keypad.getState()){
   case PRESSED:
   Serial.print("Pressed: ");
   Serial.println(eKey);

 }
}*/

void pressedPassword(){
 j=0;a=0;i=0;
 lcd.clear();
 lcd.print("Enter Password");
 lcd.setCursor(0,1);
 while(j<4){
   key=keypad.getKey();
   if(key != NO_KEY ){
     lcd.setCursor(j,1);                                   
     lcd.print("*");
     j++;
     if(key == password[i]&& i<4){ 
       a++;
       i++;
     }
     else{
       a--;
     }
   }
   key= NO_KEY;
 }
}

void checkPassword(){
 if(a==4){
  digitalWrite(buzzer,LOW);
   lcd.clear();
   lcd.print("Welcome home"); 
   delay(700);
    lcd.clear();
 lcd.print("Open Door");
 delay(10);
  sg90out.write(0);
  delay(10);
  digitalWrite(greenled,HIGH);
  delay(5000);
  digitalWrite(greenled,LOW);
  delay(10);
  sg90out.write(90);
  delay(10);
 lcd.clear();
 lcd.print("Close Door"); 
 delay(1000);
for(o=0;o<20;o++){
  lcd.clear();
  temp();
  delay(1000);}
  for(o=0;o<10;o++){
  ldr();
  delay(1000);}
   a=0;count=1;
   passcorrect=1;
  
 }else{
       digitalWrite( buzzer, HIGH);    
     lcd.clear();
     lcd.print("Passkey Wrong");
     delay(1000);  
      count++;
   }
 }
void OpenOutDoor1(){             
 lcd.clear();
 lcd.print("Open Door");
   delay(10);
   sg90.write(0);
   delay(5000);
   sg90.write(90);
 lcd.clear();
 lcd.print("Close Door");          
 }
 void OpenOutDoor2(){             
 lcd.clear();
 lcd.print("Open Door");
   delay(10);
   sg90.write(180);
   delay(5000);
   sg90.write(90);
 lcd.clear();
 lcd.print("Close Door");          
 }
void temp(){
  c=digitalRead(pushbutton);
  if(c==0){
        digitalWrite(tembuzzer, LOW);
        delay(1000);
      }
   sensors_event_t event;
  dht.temperature().getEvent(&event);
   lcd.setCursor(0, 0);

   if (event.temperature> normalThreshold) {
   lcd.print(F("Tmperat: "));
    lcd.print((event.temperature));
    lcd.println("C");
      digitalWrite(dcMotorPin, HIGH);
      delay(1000);
    }else {
      lcd.print(F("Tmperat: "));
    lcd.print((event.temperature));
    lcd.println("C");
       digitalWrite(dcMotorPin, LOW);
      delay(1000);
    }
    if(event.temperature> alarmThreshold) {
   lcd.print(F("Tmperat: "));
    lcd.print((event.temperature));
    lcd.println("C");
      digitalWrite(tembuzzer, HIGH);
      delay(1000);
    }
}
void ldr(){
     ldrValue = analogRead(ldrPin);
     lcd.setCursor(1, 1);
     lcd.print("Brightness: ");
     lcd.print(ldrValue);
     delay(2000);
     brightnessLevel = map(ldrValue, 0, 1023, 0, 255);
    analogWrite(ledPin1, brightnessLevel);
    delay(2000);

    
}