
#include "IRRemote.h"


color_history[COLOR_HISTORY_DEPTH];

void IRRemote_Config(void)
{
    GPIO_Init(IRREMOTE,GPIO_MODE_IN_FL_NO_IT);
    color_history[0] = 4;
    color_history[1] = 14;
}



uint8_t Color_Get(uint8_t historylevel)
{
    return color_history[historylevel]; 

}

void Color_Save(uint8_t color)
{
    int i;
    uint8_t temp;
    for (i = 0; i < COLOR_HISTORY_DEPTH; i++)
    {
        temp = color_history[i+1];
        color_history[i+1] = color_history[i];
    }

    color_history[0] = color;

    

}

uint8_t  IRRemote_Read(void)
{

    int step ;
    unsigned long irRemotedata;
    int databitlenth;
    int bit_Count;
    
    uint8_t ret;

    irRemotedata = 0;
    bit_Count = 0;
    ret = 0 ;


    step = DETECT_LOW_EDGE_FOS;
    databitlenth = 0;
    while((GPIO_ReadInputPin(IRREMOTE) == 0) && (databitlenth < MAX_LENGH))
    {
        databitlenth++;
    }
    if((databitlenth > LOW_EDGE_FOS_MIN) && (databitlenth < LOW_EDGE_FOS_MAX))
    {
        step = DETECT_HIGH_EDGE_FOS;
    }
    else
    {
        irRemotedata =  100;

    }

    if(step == DETECT_HIGH_EDGE_FOS)
    {
        databitlenth = 0;
        while((GPIO_ReadInputPin(IRREMOTE) != 0) && (databitlenth < MAX_LENGH))
        {
            databitlenth++;
        }
        if((databitlenth > HIGH_EDGE_FOS_MIN) && (databitlenth < HIGH_EDGE_FOS_MAX))
        {
            step = DETECT_DATA;
        }
        else
        {
            irRemotedata =  200;

        }
    }

    if(step == DETECT_DATA)
    {
        for ( bit_Count = 0; bit_Count < BIT_SIZE; bit_Count++)
        {
            databitlenth = 0;
            while((GPIO_ReadInputPin(IRREMOTE) == 0) && (databitlenth < MAX_LENGH))
            {
                databitlenth++;
            }
            databitlenth = 0;
            while((GPIO_ReadInputPin(IRREMOTE) != 0) && (databitlenth < MAX_LENGH))
            {
                databitlenth++;
            }
            if(databitlenth < MINIMUM_DISTANCE_LENGH)
            {
                step = 0;
                databitlenth = 100; 
                break;  
            }
            else if(databitlenth < ZERO_DISTANCE_LENGH)
            {
                irRemotedata = (irRemotedata << 1);   
            }
            else if(databitlenth < ONE_DISTANCE_LENGH)
            {
                irRemotedata = (irRemotedata << 1);
                irRemotedata += 1;
                
            }
            else
            {
                step = 0;
                databitlenth = 200;
                break;
            }
        }

        switch (irRemotedata)
        {
            case KEY_ON:
                ret = ONN_STATUS;
                break;
            case KEY_OFF:
                ret = OFF_STATUS;
                break;
            case KEY_DECREASE:
                ret = DECREASE;
                break;
            case KEY_INCREASE:
                ret = INCREASE;
                break;
            case KEY_WHITE:
                Color_Save(1);
                ret = COLORCHANGE;
                break;
            case KEY_BLUE:
                Color_Save(2);
                ret = COLORCHANGE;
                break;
            case KEY_GREEN:
                Color_Save(3);
                ret = COLORCHANGE;
                break;
            case KEY_RED:
                Color_Save(4);
                ret = COLORCHANGE;
                break;
            case KEY_FLASH:
                ret = KEY_1;
                break;
            case KEY_B1:
                Color_Save(5);
                ret = COLORCHANGE;
                break;
            case KEY_G1:
                Color_Save(6);
                ret = COLORCHANGE;
                break;
            case KEY_R1:
                Color_Save(7);
                ret = COLORCHANGE;
                break;
            case KEY_STORB:
                ret = KEY_2;
                break;
            case KEY_B2:
                Color_Save(8);
                ret = COLORCHANGE;
                break;
            case KEY_G2:
                Color_Save(9);
                ret = COLORCHANGE;
                break;
            case KEY_R2:
                Color_Save(10);
                ret = COLORCHANGE;
                break;
            case KEY_FADE:
                ret = KEY_3;
                break;
            case KEY_B3:
                Color_Save(11);
                ret = COLORCHANGE;
                break;
            case KEY_G3:
                Color_Save(12);
                ret = COLORCHANGE;
                break;
            case KEY_R3:
                Color_Save(13);
                ret = COLORCHANGE;
                break;
            case KEY_SMOOTH:
                ret = KEY_4;
                break;
            case KEY_B4:
                Color_Save(14);
                ret = COLORCHANGE;
                break;
            case KEY_G4:
                Color_Save(15);
                ret = COLORCHANGE;
                break;
            case KEY_R4:
                Color_Save(16);
                ret = COLORCHANGE;
                break;
            
            default:
                break;
        } 
        return ret;		
    }
    

}


