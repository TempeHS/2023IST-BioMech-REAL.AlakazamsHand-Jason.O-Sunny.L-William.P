#include <MUIU8g2.h>
#include <U8g2lib.h>
#include <U8x8lib.h>

#include <Wire.h>
#include "paj7620.h"
#include <Arduino.h>
#include <U8g2lib.h>

/* 
Notice: When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME  500    // You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME   800    // When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME   1000


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High speed I2C

void setup()
{

 Serial.begin(9600);
  u8g2.begin();
uint8_t error = 0;
 u8g2.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

 error = paj7620Init();   // initialize Paj7620 registers
 if (error) 
 {
  u8g2.print("INIT ERROR,CODE:");
  u8g2.println(error);
 }
 else
 {
  u8g2.println("INIT OK");
 }
 u8g2.println("Please input your gestures:\n");
}






void loop() {
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  u8g2.setCursor(0, 10);              // Set cursor to first line

  
  
  
  uint8_t data = 0, data1 = 0, error;
 
 error = paj7620ReadReg(0x43, 1, &data);    // Read Bank_0_Reg_0x43/0x44 for gesture result.
 if (!error) 
 {
  switch (data)          // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data).
  {
   case GES_RIGHT_FLAG:
    delay(GES_ENTRY_TIME);
    paj7620ReadReg(0x43, 1, &data);
    if(data == GES_FORWARD_FLAG) 
    {
     u8g2.println("Forward");
     delay(GES_QUIT_TIME);
    }
    else if(data == GES_BACKWARD_FLAG) 
    {
     u8g2.println("Backward");
     delay(GES_QUIT_TIME);
    }
    else
    {
     u8g2.println("Right");
    }          
    break;
   case GES_LEFT_FLAG: 
    delay(GES_ENTRY_TIME);
    paj7620ReadReg(0x43, 1, &data);
    if(data == GES_FORWARD_FLAG) 
    {
     u8g2.println("Forward");
     delay(GES_QUIT_TIME);
    }
    else if(data == GES_BACKWARD_FLAG) 
    {
     u8g2.println("Backward");
     delay(GES_QUIT_TIME);
    }
    else
    {
     u8g2.println("Left");
    }          
    break;
   case GES_UP_FLAG:
    delay(GES_ENTRY_TIME);
    paj7620ReadReg(0x43, 1, &data);
    if(data == GES_FORWARD_FLAG) 
    {
     u8g2.println("Forward");
     delay(GES_QUIT_TIME);
    }
    else if(data == GES_BACKWARD_FLAG) 
    {
     u8g2.println("Backward");
     delay(GES_QUIT_TIME);
    }
    else
    {
     u8g2.println("Up");
    }          
    break;
   case GES_DOWN_FLAG:
    delay(GES_ENTRY_TIME);
    paj7620ReadReg(0x43, 1, &data);
    if(data == GES_FORWARD_FLAG) 
    {
     u8g2.println("Forward");
     delay(GES_QUIT_TIME);
    }
    else if(data == GES_BACKWARD_FLAG) 
    {
     u8g2.println("Backward");
     delay(GES_QUIT_TIME);
    }
    else
    {
     u8g2.println("Down");
    }          
    break;
   case GES_FORWARD_FLAG:
    u8g2.println("Forward");
    delay(GES_QUIT_TIME);
    break;
   case GES_BACKWARD_FLAG:    
    u8g2.println("Backward");
    delay(GES_QUIT_TIME);
    break;
   case GES_CLOCKWISE_FLAG:
    u8g2.println("Clockwise");
    break;
   case GES_COUNT_CLOCKWISE_FLAG:
    u8g2.println("anti-clockwise");
    break;  
   default:
    paj7620ReadReg(0x44, 1, &data1);
    if (data1 == GES_WAVE_FLAG) 
    {
     u8g2.println("wave");
    }
    break;
  }
 }
 

  u8g2.sendBuffer();                  // transfer internal memory to the display
 delay(400);
}
 
  
