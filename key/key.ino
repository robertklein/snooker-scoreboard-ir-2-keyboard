/*************************************
* This code is written by Laurens Wuyts
* For questions: laurens.wuyts@gmail.com
* 
* 
* Microcontroller: ATtiny85
* Dev board:       Digispark
* 
*************************************/
#include "DigiKeyboard.h"

uint8_t situation = 0;
uint8_t START = 0;
uint8_t x = 0;
uint8_t BIT = 0;
uint8_t Id = 0;
uint8_t Id_inv = 0;
uint8_t Data = 0;
uint8_t Data_back = 0;
uint8_t Data_inv = 0;
uint8_t Repeat = 0;
uint8_t sended = 0;

uint16_t Time_old = 0;
uint16_t Time = 0;
uint16_t TimeDelta = 0;
 
void setup(void) {
  attachInterrupt(0, IR_Read, FALLING);
  
  pinMode(1,OUTPUT);
  digitalWrite(1,LOW);
  pinMode(0,OUTPUT);
  digitalWrite(0,LOW);

  //DigiUSB.begin();
}
 
void loop(void) {
  if(sended == 1) {
    //DigiUSB.println(Data_back, DEC);
    DigiKeyboard.sendKeyStroke(0);
    //DigiKeyboard.print(Data_back, HEX);
    //DigiKeyboard.print(Data_back, DEC);
    
    // LG - na smartfone apka
    /*if(Data_back == 0x88) DigiKeyboard.print("a");
    if(Data_back == 0x48) DigiKeyboard.print("s");
    if(Data_back == 0xC8) DigiKeyboard.print("d");
    if(Data_back == 0x28) DigiKeyboard.print("f");
    if(Data_back == 0xA8) DigiKeyboard.print("g");
    if(Data_back == 0x68) DigiKeyboard.print("h");
    if(Data_back == 0xE8) DigiKeyboard.print("j");*/

    // Zo zasadacky ovladac
    /*if(Data_back == 0x20) DigiKeyboard.print("z");
    if(Data_back == 0xA0) DigiKeyboard.print("x");
    if(Data_back == 0xAA) DigiKeyboard.print("c");
    if(Data_back == 0xC0) DigiKeyboard.print("v");
    if(Data_back == 0x63) DigiKeyboard.print("b");
    if(Data_back == 0x2A) DigiKeyboard.print("n");
    if(Data_back == 0xE4) DigiKeyboard.print("m");
    // FOULS
    if(Data_back == 0x72) DigiKeyboard.print(",");
    if(Data_back == 0x5)  DigiKeyboard.print(".");
    if(Data_back == 0x8)  DigiKeyboard.print("/");
    if(Data_back == 0x92)  DigiKeyboard.print("]");
    // CHANGE PLAYER
    if(Data_back == 0x5D || Data_back == 0x7D) DigiKeyboard.print(" ");
    // BACK
    if(Data_back == 0xA4)  DigiKeyboard.print("=");
    // NEXT FRAME
    if(Data_back == 0xE8)  DigiKeyboard.println("");*/



    // Aliexpress mini | Genius RB repro
    if(Data_back == 0x1A)  DigiKeyboard.print("z");
    if(Data_back == 0x9A)  DigiKeyboard.print("x");
    if(Data_back == 0xA2)  DigiKeyboard.print("c");
    if(Data_back == 0x22)  DigiKeyboard.print("v");
    if(Data_back == 0x2A)  DigiKeyboard.print("b");
    if(Data_back == 0xAA)  DigiKeyboard.print("n");
    if(Data_back == 0x92)  DigiKeyboard.print("m");
    // FOULS
    if(Data_back == 0xA) DigiKeyboard.print(",");
    if(Data_back == 0x8A) DigiKeyboard.print(".");
    if(Data_back == 0xB2) DigiKeyboard.print("/");
    if(Data_back == 0x32)  DigiKeyboard.print("]");
    // CHANGE PLAYER
    if(Data_back == 0x2) DigiKeyboard.print(" ");
    // BACK
    if(Data_back == 0x3A) DigiKeyboard.print("=");
    // NEXT FRAME
    if(Data_back == 0x82)  DigiKeyboard.println("");
    // ADD BALL - REMOVE BALL
    if(Data_back == 0x28)  DigiKeyboard.print("9");
    if(Data_back == 0x8)  DigiKeyboard.print("0");
    // APPLAUSE
    if(Data_back == 0x30)  DigiKeyboard.print("1");
    if(Data_back == 0xB0)  DigiKeyboard.print("2");
    if(Data_back == 0x70)  DigiKeyboard.print("3");
    if(Data_back == 0xF0)  DigiKeyboard.print("4");
    if(Data_back == 0x10)  DigiKeyboard.print("5");
    if(Data_back == 0x90)  DigiKeyboard.print("6");
    if(Data_back == 0x50)  DigiKeyboard.print("7");

    if(Data_back == 0x1A
      || Data_back == 0x9A
      || Data_back == 0xA2
      || Data_back == 0x22
      || Data_back == 0x2A
      || Data_back == 0xAA
      || Data_back == 0x92
      || Data_back == 0xA
      || Data_back == 0x8A
      || Data_back == 0xB2
      || Data_back == 0x32
      || Data_back == 0x2
      || Data_back == 0x3A
      || Data_back == 0x82
      || Data_back == 0x28
      || Data_back == 0x8
      || Data_back == 0x30
      || Data_back == 0xB0
      || Data_back == 0x70
      || Data_back == 0xF0
      || Data_back == 0x10
      || Data_back == 0x90
      || Data_back == 0x50
    ){
      digitalWrite(0,HIGH);
      delay(120);
      digitalWrite(0,LOW);
    } else {
      digitalWrite(0,HIGH);
      delay(50);
      digitalWrite(0,LOW);
      delay(100);
      digitalWrite(0,HIGH);
      delay(50);
      digitalWrite(0,LOW);
      delay(100);
      digitalWrite(0,HIGH);
      delay(50);
      digitalWrite(0,LOW);
    }
    
    DigiKeyboard.delay(250);
    
    sended = 0;
  } else {
    //DigiUSB.delay(10);
  }
}

void IR_Read(void) {
  digitalWrite(1,HIGH);
  Time = micros();
  if (Time_old != 0) {
    TimeDelta = Time - Time_old;
    if ((TimeDelta > 12000)&&(TimeDelta < 14000)) {
      START = 1;
      x = 0;
      situation = 1;
      Id = 0;
      Id_inv = 0;
      Data = 0;
      Data_inv = 0;
    } else if ((TimeDelta > 10000)&&(TimeDelta < 12000)) {
      situation = 2; // repeat
    } else if ((TimeDelta > 1500)&&(TimeDelta < 2500)) {
      situation = 3; //"1"
      BIT = 1;
    } else if ((TimeDelta > 1000)&&(TimeDelta < 1500)) {
      situation = 3; //"0"
      BIT = 0;
    } else situation = 5; 
    if (situation == 3) {
      if (x < 8) {
        Id |= BIT;
        if (x < 7) Id <<= 1;  
        x++;
      } else if (x < 16) {
        Id_inv |= BIT;
        if (x < 15) Id_inv <<= 1;
        x++;
      } else if (x < 24) {
        Data |= BIT;
        if (x < 23) Data <<= 1;
        x++;
      } else if (x < 32) {
        Data_inv |= BIT;
        if (x < 31) {
          Data_inv <<= 1;
        } else {
          
          /* DO SOMETHING HERE */
          sended = 1;
          
          Data_back = Data;
          Repeat = 0;
        }
        x++;
      }
    } else if (situation == 2) {
      if(Repeat == 1) {
        
        /* DO SOMETHING HERE */
        /*sended = 1;*/
        
      } else {
        Repeat = 1;
      }
    }
  }
  Time_old = Time;
  digitalWrite(1,LOW);
}
