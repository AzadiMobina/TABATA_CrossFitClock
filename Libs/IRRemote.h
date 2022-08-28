
#ifndef _IRRemote_
#define _IRRemote_

#include <stdio.h>
#include"stm8s_gpio.h"


//#define IRREMOTE GPIOB,GPIO_PIN_2
#define IRREMOTE GPIOB,GPIO_PIN_3


// ***************** Key Mapp of Remote
#define KEY_ON       0xF7C03F
#define KEY_OFF      0xF740BF
#define KEY_DECREASE 0xF7807F
#define KEY_INCREASE 0xF700FF
#define KEY_WHITE    0xF7E01F
#define KEY_BLUE     0xF7609F
#define KEY_GREEN    0xF7A05F
#define KEY_RED      0xF720DF
#define KEY_FLASH    0xF7D02F
#define KEY_B1       0xF750AF
#define KEY_G1       0xF7906F
#define KEY_R1       0xF710EF
#define KEY_STORB    0xF7F00F
#define KEY_B2       0xF7708F
#define KEY_G2       0xF7B04F
#define KEY_R2       0xF730CF
#define KEY_FADE     0xF7C837
#define KEY_B3       0xF748B7
#define KEY_G3       0xF78877
#define KEY_R3       0xF708F7
#define KEY_SMOOTH   0xF7E817
#define KEY_B4       0xF76897
#define KEY_G4       0xF7A857
#define KEY_R4       0xF728D7


#define DETECT_LOW_EDGE_FOS 0x10
// Mean of it is 2100
#define LOW_EDGE_FOS_MIN 1900
#define LOW_EDGE_FOS_MAX 2300

#define DETECT_HIGH_EDGE_FOS 0x20
// Mean of it is 1000
#define HIGH_EDGE_FOS_MIN 800
#define HIGH_EDGE_FOS_MAX 1200

#define DETECT_DATA 0x30

#define BIT_SIZE 32
// mean of it is 130
#define MINIMUM_DISTANCE_LENGH 100
// mean of it is 125
#define ZERO_DISTANCE_LENGH 160
// mean of it is 385
#define ONE_DISTANCE_LENGH 500

#define MAX_LENGH 3000


#define IRRemote_Ready (GPIO_ReadInputPin(IRREMOTE) == RESET)

  

#define COLOR_HISTORY_DEPTH 10


#define INCREASE    'I'
#define DECREASE    'D'
#define KEY_1       '1'
#define KEY_2       '2'
#define KEY_3       '3'
#define KEY_4       '4'
#define COLORCHANGE 'C'
#define ONN_STATUS 'N'
#define OFF_STATUS 'F'




uint8_t  IRRemote_Read(void);
void IRRemote_Config(void);
void Color_Save(uint8_t color);
uint8_t Color_Get(uint8_t historylevel);



#endif /* _IRRemote_*/

