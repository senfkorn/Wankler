#include <Arduino.h>

#define Messungen 10

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>
#include <EEPROM.h>
#include "OneButton.h"

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RotaryEncoder encoder(A2, A3);
OneButton button(A1, true);


void ButtonClick();
void showTopMenu();
void showParameterMenu();
void doMessung();
void showMessung();
void changeThreshold();
void changeTimeout();
void changeFilter();
template <class T> int EEPROM_writeAnything(int ee, const T& value);
template <class T> int EEPROM_readAnything(int ee, T& value);
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
float getValue(int Pin);

bool Init = true;
const int analogInPin = A0;
float sensorValue = 0.0; 
float lowestValue = 0.0;
float highestValue = 0.0;
unsigned long lasttick = 0;
float Max[Messungen];
float lastValue;
unsigned long TimeStamp[Messungen];
int Index= 0;
float Threshold = 2.0;
boolean Clicked = false;
int MenuItem = 0;
int MenuItemOld = 0;
int EncoderAct = 0;
int EncoderOld = 0;
int Filter = 1;
unsigned long StartMessung = 0;
unsigned long TimeoutStamp = 0;
unsigned long Timeout = 60000;

//ISR
ISR(PCINT1_vect) {
  encoder.tick();
  button.tick();
}

void setup() {
  Serial.begin(115200);    // start the serial port
  // You may have to modify the next 2 lines if using other pins than A2 and A3
  PCICR  |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);  // This enables the interrupt for pin 1, pin 2 and 3 of Port C.

  button.attachClick(ButtonClick);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();

}

void loop() {


  lcd.setCursor(0,0);
  unsigned long StartStamp = micros();
  float trash = getValue(analogInPin);
  lcd.print(micros() - StartStamp);
  


}

//button clicked interrupt
void ButtonClick(){
  Clicked = true;

}

void doMessung(){
// init messung
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("Messung laeuft");
  Index = 0;
  for (int i = 0; i < Messungen; i++){
    Max[i] = 0;
    TimeStamp[i] = 0;
  }
  TimeoutStamp = millis();


  
  
  do {

    //wait for positive edge 
    lowestValue =  getValue(analogInPin);
    do{
      sensorValue = getValue(analogInPin);
      if (lowestValue > sensorValue){
        lowestValue = sensorValue;
      }
    }while(sensorValue - lowestValue < Threshold && millis() - TimeoutStamp < Timeout);
    //Serial.println("Pos edge found");
    
    //wait for negative edge 
    highestValue =  getValue(analogInPin);
    do{
      sensorValue = getValue(analogInPin);
      if (highestValue < sensorValue){
        highestValue = sensorValue;
      }
    }while(highestValue - sensorValue < Threshold && millis() - TimeoutStamp < Timeout);
    //Serial.println("Neg edge found");
    //save highest value
    Max[Index] = highestValue;
    TimeStamp[Index] = millis();
    Index++;
  }while (Index < Messungen && millis() - TimeoutStamp < Timeout);

  if (millis() - TimeoutStamp >= Timeout){
    lcd.clear();
    lcd.setCursor(6,2);
    lcd.print("Timeout");
    delay(10000);
    MenuItem = 0;
  }else{
    lcd.clear();
    lcd.setCursor(6,2);
    lcd.print("fertig");
    delay(1000);
    MenuItem = 1;
  }


}

void showTopMenu(){

static unsigned long actTick = 0;
static unsigned long lastTick = 0;

  EncoderAct = encoder.getPosition();
  if (encoder.getPosition() < 0) {
    encoder.setPosition(0);
    EncoderAct = 0;
  }
  if (encoder.getPosition() > 2) {
    encoder.setPosition(2);
    EncoderAct = 2;
  }

  if (EncoderAct != EncoderOld){
    lcd.clear();
    EncoderOld = EncoderAct;
  }

  lcd.setCursor(3,0);
  lcd.print("Wankler");
  lcd.setCursor(3,1);
  lcd.print("starte Messung");
  lcd.setCursor(3,2);
  lcd.print("zeige Messung");
  lcd.setCursor(3,3);
  lcd.print("Parameter");
  lcd.setCursor(0,EncoderAct + 1);
  lcd.print("->");

  //show actual value at the corner
actTick = millis();
if (actTick - lastTick > 100 && MenuItem == 0){
  lastTick = actTick;
  lcd.setCursor(15,0);
  lcd.print("     ");
  lcd.setCursor(15,0);
  lcd.print(getValue(analogInPin), 2);
}
}

void showParameterMenu(){

  EncoderAct = encoder.getPosition();
  if (encoder.getPosition() < 0) {
    encoder.setPosition(0);
    EncoderAct = 0;
  }
  if (encoder.getPosition() > 3) {
    encoder.setPosition(3);
    EncoderAct = 3;
  }

  if (EncoderAct != EncoderOld){
    lcd.clear();
    EncoderOld = EncoderAct;
  }
  lcd.setCursor(0,0);
  lcd.print("Parameter");
  lcd.setCursor(16,0);
  lcd.print("v1.2");
  if (EncoderAct < 3){
    lcd.setCursor(3,1);
    lcd.print("Schwelle aendern");
    lcd.setCursor(3,2);
    lcd.print("Timeout aendern");
    lcd.setCursor(3,3);
    lcd.print("Filter aendern");
    lcd.setCursor(0,EncoderAct + 1);
    lcd.print("->");
  }else{
    lcd.setCursor(3,1);
    lcd.print("Timeout aendern");
    lcd.setCursor(3,2);
    lcd.print("Filter aendern");
    lcd.setCursor(3,3);
    lcd.print("zurueck");
    lcd.setCursor(0,3);
    lcd.print("->");
  }
}

void showMessung(){
      lcd.setCursor(6,0);
      lcd.print("Mes1");
      lcd.setCursor(11,0);
      lcd.print("Mes2");
      lcd.setCursor(16,0);
      lcd.print("Mes3");

      lcd.setCursor(0,1);
      lcd.print("Druck");
      lcd.setCursor(6,1);
      lcd.print(Max[Messungen -3], 1);
      lcd.setCursor(11,1);
      lcd.print(Max[Messungen -2], 1);
      lcd.setCursor(16,1);
      lcd.print(Max[Messungen -1], 1);


      float time1 = TimeStamp[Messungen -2]-TimeStamp[Messungen -3];
      float time2 = TimeStamp[Messungen -1]-TimeStamp[Messungen -2];

      lcd.setCursor(0,2);
      lcd.print("Zeit");
      lcd.setCursor(8,2);
      lcd.print(time1,0);
      lcd.setCursor(14,2);
      lcd.print(time2,0);
      lcd.setCursor(0,3);
      if (time2 > 0){
        lcd.print("rpm");
        lcd.setCursor(11,3);
        lcd.print((1.0 / (time2 / 1000.0))*60.0 ,0);
      }
      

}

void changeTimeout(){
long encoderMovement;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Timeout");
  lcd.setCursor(6,2);
  lcd.print(Timeout/1000);
  lcd.setCursor(15,2);
  lcd.print("sek");
  encoderMovement = encoder.getDirection();
  do{
  encoderMovement = encoder.getDirection();
    if (encoderMovement != 0){
      Timeout += encoderMovement * 1000;
      if (Timeout > 20000){
        Threshold = 20000;
      }else if(Timeout < 1000){
        Timeout = 1000;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Timeout");
      lcd.setCursor(6,2);
      lcd.print(Timeout/1000);
      lcd.setCursor(15,2);
      lcd.print("sek");
  }
  button.tick();
  }while(!Clicked);
  MenuItem = 2; //goto parameter menu
  Clicked = false;
  EEPROM_writeAnything(10, Timeout);
}

void changeThreshold(){
  long encoderMovement;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Schwellwert");
  lcd.setCursor(6,2);
  lcd.print(Threshold,1);
  lcd.setCursor(15,2);
  lcd.print("bar");
  encoderMovement = encoder.getDirection();
  do{
  encoderMovement = encoder.getDirection();
    if (encoderMovement != 0){
      Threshold += (float)encoderMovement / 10.0;
      if (Threshold > 5.0){
        Threshold = 5.0;
      }else if(Threshold < 0.1){
        Threshold = 0.1;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Schwellwert");
      lcd.setCursor(6,2);
      lcd.print(Threshold,1);
      lcd.setCursor(15,2);
      lcd.print("bar");
  }
  button.tick();
  }while(!Clicked);
  MenuItem = 2; //goto parameter menu
  Clicked = false;
  EEPROM_writeAnything(20, Threshold);
}

void changeFilter(){
long encoderMovement;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Filter");
  lcd.setCursor(6,2);
  lcd.print(Filter / 10);
  lcd.setCursor(15,2);
  lcd.print("ms");
  encoderMovement = encoder.getDirection();
  do{
  encoderMovement = encoder.getDirection();
    if (encoderMovement != 0){
      Filter += encoderMovement + 10;
      if (Filter > 32767){
        Filter = 32767;
      }else if(Filter < 1){
        Filter = 1;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Filter");
      lcd.setCursor(6,2);
      lcd.print(Filter / 10);
      lcd.setCursor(15,2);
      lcd.print("ms");
  }
  button.tick();
  }while(!Clicked);
  MenuItem = 2; //goto parameter menu
  Clicked = false;
  EEPROM_writeAnything(30, Filter);
}


float getValue(int Pin){
  float Value = 0;
  Filter = constrain(Filter, 1, 32767);
  for(int i = 0; i < Filter; i++){
    Value += analogRead(analogInPin);
  }
  Value = Value / Filter;

  return(mapfloat(Value,100.0, 900.0, 0.0 , 10.0));

}


template <class T> int EEPROM_writeAnything(int ee, const T& value){
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value){
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}