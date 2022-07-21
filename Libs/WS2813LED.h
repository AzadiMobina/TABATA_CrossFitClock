#ifndef _WS2813LED_
#define _WS2813LED_

#include "stm8s_gpio.h"
#include "IRRemote.h"



#define SEGMENT_0_PIN  GPIOE,GPIO_PIN_7     
#define SEGMENT_1_PIN  GPIOE,GPIO_PIN_6 
#define SEGMENT_2_PIN  GPIOE,GPIO_PIN_5 
#define SEGMENT_3_PIN  GPIOC,GPIO_PIN_1 
#define SEGMENT_4_PIN  GPIOC,GPIO_PIN_2 
#define SEGMENT_5_PIN  GPIOC,GPIO_PIN_3
#define SEGMENT_6_PIN  GPIOC,GPIO_PIN_5 
#define SEGMENT_7_PIN  GPIOC,GPIO_PIN_6 
#define SEGMENT_8_PIN  GPIOC,GPIO_PIN_7 
#define SEGMENT_9_PIN GPIOG,GPIO_PIN_0 

#define SEGMENT_0  '0'     
#define SEGMENT_1  '1' 
#define SEGMENT_2  '2' 
#define SEGMENT_3  '3' 
#define SEGMENT_4  '4' 
#define SEGMENT_5  '5'
#define SEGMENT_6  '6' 
#define SEGMENT_7  '7' 
#define SEGMENT_8  '8' 
#define SEGMENT_9  '9' 

#define COLOR_100  10
#define COLOR_90   9
#define COLOR_80   8
#define COLOR_70   7
#define COLOR_60   6 
#define COLOR_50   5 
#define COLOR_40   4 
#define COLOR_30   3 
#define COLOR_20   2 
#define COLOR_10   1  
#define COLOR_0    0 

#define ON 1
#define OFF 0

#define SYSTEMCOLOR 'Y'
#define COLOR_HISTORY_1 'X'

#define LEVEL_FULL 25


void Segment_Pins_Config(void);

void delay_offSure(void);

// Setting up the RGB LED
void Segment_0_SetBit(uint8_t state);

void Segment_0_Update(void);

void Segment_1_SetBit(uint8_t state);

void Segment_1_Update(void);

void Segment_2_SetBit(uint8_t state);

void Segment_3_SetBit(uint8_t state);

void Segment_3_Update(void);

void Segment_4_SetBit(uint8_t state);

void Segment_4_Update(void);

void Segment_5_SetBit(uint8_t state);

void Segment_5_Update(void);

void Segment_6_SetBit(uint8_t state);

void Segment_6_Update(void);

void Segment_7_SetBit(uint8_t state);

void Segment_7_Update(void);

void Segment_8_SetBit(uint8_t state);

void Segment_8_Update(void);

void Segment_9_SetBit(uint8_t state);

void Segment_9_Update(void);


void Segment_SetData(uint8_t segId , uint8_t state);

void Segment_Map(uint8_t num);

void Segment_SetColor(uint8_t colornum , uint8_t lightlevel);

void Segment(uint8_t segmentnum,uint8_t value, uint8_t colornum,uint8_t lightlevel);


void DotPoints(uint8_t dotnum,uint8_t state, uint8_t colornum,uint8_t lightlevel);
void DotPoints_Map(uint8_t dotnum,uint8_t state);
void DotPoints_SetColor(uint8_t colornum , uint8_t lightlevel);
void DotPoints_Update(void);






#endif /* _WS2813LED_ */
