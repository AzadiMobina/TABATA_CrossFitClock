#include"WS2813LED.h"


unsigned char segmentdata[14][3];
unsigned char dotpointdata[14][3];

void Segment_Pins_Config(void)
{
    GPIO_Init(SEGMENT_1_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_2_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_3_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_4_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_5_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_6_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_7_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_8_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_9_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(SEGMENT_0_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
}

void delay_offSure(void)
{
    uint8_t i;
    for ( i = 0; i < 250; i++)
    {
        nop();
    }
    
}

// Setting up the RGB LED
void Segment_0_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOB->ODR |= (uint8_t)GPIO_PIN_0;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOB->ODR &= (uint8_t)(~GPIO_PIN_0);
      /*  nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOB->ODR |= (uint8_t)GPIO_PIN_0;
        nop();
        nop();
        //

        GPIOB->ODR &= (uint8_t)(~GPIO_PIN_0);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_0_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_0_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_0_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_0_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_1_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOE->ODR |= (uint8_t)GPIO_PIN_7;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_7);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOE->ODR |= (uint8_t)GPIO_PIN_7;
        nop();
        nop();
        //

        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_7);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_1_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_1_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_1_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_1_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}


void Segment_2_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOE->ODR |= (uint8_t)GPIO_PIN_6;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_6);
      /*  nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOE->ODR |= (uint8_t)GPIO_PIN_6;
        nop();
        nop();
        //

        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_6);
       /* nop();
        nop();
        nop();
        nop();*//**/
        //
     


    }
}

void Segment_2_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_2_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_2_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_2_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}


void Segment_3_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOE->ODR |= (uint8_t)GPIO_PIN_5;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_5);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOE->ODR |= (uint8_t)GPIO_PIN_5;
        nop();
        nop();
        //

        GPIOE->ODR &= (uint8_t)(~GPIO_PIN_5);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_3_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_3_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_3_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_3_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_4_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_1;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_1);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_1;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_1);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_4_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_4_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_4_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_4_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_5_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_2;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_2);
      /*  nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_2;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_2);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_5_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_5_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_5_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_5_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_6_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_3;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_3);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_3;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_3);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_6_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_6_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_6_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_6_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_7_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_5;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_5);
        /*nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_5;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_5);
       /* nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_7_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_7_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_7_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_7_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_8_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_6;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_6);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_6;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_6);
       /* nop();
        nop();
        nop();
        nop();
        */
     


    }
}

void Segment_8_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_8_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_8_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_8_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}

void Segment_9_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_7;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_7);
       /* nop();
        nop();
        nop();
        nop();*/
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_7;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_7);
      /*  nop();
        nop();
        nop();
        nop();*/
        //
     


    }
}

void Segment_9_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            Segment_9_SetBit(((segmentdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_9_SetBit(((segmentdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            Segment_9_SetBit(((segmentdata[j][2] & i) == i));
        }
    }
}


void DotPoints_SetBit(uint8_t state)
{
    if(state)
    { 

        GPIOC->ODR |= (uint8_t)GPIO_PIN_5;
        nop(); //62.5ns
        nop();
        nop();
        nop();
        nop();
        nop();
        //
        
        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_5);
        nop();
        nop();
        nop();
        nop();
        //
 
      

    }
    else
    {
        GPIOC->ODR |= (uint8_t)GPIO_PIN_5;
        nop();
        nop();
        //

        GPIOC->ODR &= (uint8_t)(~GPIO_PIN_5);
        nop();
        nop();
        nop();
        nop();
        //
     


    }
}

void DotPoints_Update(void)
{
    int i;
    int j;

    for(j=0;j<14;j++)
    {
        for(i=128;i>=1;i=i/2)
        {
            DotPoints_SetBit(((dotpointdata[j][0] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            DotPoints_SetBit(((dotpointdata[j][1] & i) == i));
        }
        for(i=128;i>=1;i=i/2)
        {
            DotPoints_SetBit(((dotpointdata[j][2] & i) == i));
        }
    }
}

void Segment_SetData(uint8_t segId , uint8_t state)
{

    segId = segId*2;
    if(state == ON)
    {
        segmentdata[segId][0] = 1;
        segmentdata[segId][1] = 1;
        segmentdata[segId][2] = 1;

        segmentdata[segId+1][0] = 1;
        segmentdata[segId+1][1] = 1;
        segmentdata[segId+1][2] = 1;
    }
    else
    {
        segmentdata[segId][0] = 0;
        segmentdata[segId][1] = 0;
        segmentdata[segId][2] = 0;

        segmentdata[segId+1][0] = 0;
        segmentdata[segId+1][1] = 0;
        segmentdata[segId+1][2] = 0;
    }
}

void Segment_Map(uint8_t num)
{
    switch (num)
    {
        case 0:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 1:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , ON );
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , OFF);
            break;
        case 2:
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , OFF);
            break;
        case 3:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , OFF);
            break;
        case 4:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , ON );
            break;
        case 5:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 6:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 7:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , OFF);
            break;
        case 8:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 9:
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        
        case 'C':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        
        case 'o':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        
        case 'O':
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        
        case 'I':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , ON );
            break;
        
        case 'H':
            Segment_SetData(0 , ON );
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , ON );
            break;
        
        case 'L':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , ON );
            break;
        
        case 'U':
            Segment_SetData(0 , ON );
            Segment_SetData(1 , ON );
            Segment_SetData(2 , ON );
            Segment_SetData(3 , OFF);
            Segment_SetData(4 , ON );
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , ON );
            break;
        
        case 'P':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , ON );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 'F':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , ON );
            Segment_SetData(3 , ON );
            Segment_SetData(4 , OFF );
            Segment_SetData(5 , ON );
            Segment_SetData(6 , ON );
            break;
        case 'N':
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , OFF);
            break;

        default:
            Segment_SetData(0 , OFF);
            Segment_SetData(1 , OFF);
            Segment_SetData(2 , OFF);
            Segment_SetData(3 , ON );
            Segment_SetData(4 , OFF);
            Segment_SetData(5 , OFF);
            Segment_SetData(6 , OFF);
            break;
    }

}


void DotPoints_Map(uint8_t dotnum,uint8_t state)
{
    switch (dotnum)
    {
        case 1:
            if(state == 1)
            {
                dotpointdata[0][0] = 1 ;
                dotpointdata[0][1] = 1 ;
                dotpointdata[0][2] = 1 ;
            }
            else
            {
                dotpointdata[0][0] = 0 ;
                dotpointdata[0][1] = 0 ;
                dotpointdata[0][2] = 0 ;
            }
            break;
        
        case 2:
            if(state == 1)
            {
                dotpointdata[1][0] = 1 ;
                dotpointdata[1][1] = 1 ;
                dotpointdata[1][2] = 1 ;
            }
            else
            {
                dotpointdata[1][0] = 0 ;
                dotpointdata[1][1] = 0 ;
                dotpointdata[1][2] = 0 ;
            }
            break;
        
        case 3:
            if(state == 1)
            {
                dotpointdata[2][0] = 1 ;
                dotpointdata[2][1] = 1 ;
                dotpointdata[2][2] = 1 ;
            }
            else
            {
                dotpointdata[2][0] = 0 ;
                dotpointdata[2][1] = 0 ;
                dotpointdata[2][2] = 0 ;
            }
            break;
        
        case 4:
            if(state == 1)
            {
                dotpointdata[3][0] = 1 ;
                dotpointdata[3][1] = 1 ;
                dotpointdata[3][2] = 1 ;
            }
            else
            {
                dotpointdata[3][0] = 0 ;
                dotpointdata[3][1] = 0 ;
                dotpointdata[3][2] = 0 ;
            }
            break;
        
        default:
            break;
    }
}

void Segment_SetColor(uint8_t colornum , uint8_t lightlevel)
{
    int i;
    uint8_t greenLevel;
    uint8_t redLevel;
    uint8_t blueLevel;
    
    if(colornum == SYSTEMCOLOR)
        colornum = Color_Get(0);
    else if(colornum == COLOR_HISTORY_1)
        colornum = Color_Get(1);
    else if(colornum == COLOR_HISTORY_2)
        colornum = Color_Get(2);

    switch (colornum)
    {
    case 0:
        greenLevel = 0;
        redLevel = 0;
        blueLevel = 0;
        break;
    
    case 1:
        greenLevel = COLOR_100;
        redLevel = COLOR_100;
        blueLevel = COLOR_100;
        break;
    
    case 2:
        greenLevel = COLOR_0;
        redLevel = COLOR_0;
        blueLevel = COLOR_100;
        break;
    
    case 3:
        greenLevel = COLOR_0;
        redLevel = COLOR_100;
        blueLevel = COLOR_0;
        break;
    
    case 4:
        greenLevel = COLOR_100;
        redLevel = COLOR_0;
        blueLevel = COLOR_0;
        break;
    
    case 5:
        greenLevel = COLOR_10;
        redLevel = COLOR_0;
        blueLevel = COLOR_90;
        break;
    
    case 6:
        greenLevel = COLOR_0;
        redLevel = COLOR_80;
        blueLevel = COLOR_20;
        break;
    
    case 7:
        greenLevel = COLOR_100;
        redLevel = COLOR_20;
        blueLevel = COLOR_0;
        break;
    
    case 8:
        greenLevel = COLOR_20;
        redLevel = COLOR_0;
        blueLevel = COLOR_90;
        break;
    
    case 9:
        greenLevel = COLOR_0;
        redLevel = COLOR_60;
        blueLevel = COLOR_40;
        break;
    
    case 10:
        greenLevel = COLOR_100;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    case 11:
        greenLevel = COLOR_40;
        redLevel = COLOR_0;
        blueLevel = COLOR_40;
        break;
    
    case 12:
        greenLevel = COLOR_0;
        redLevel = COLOR_40;
        blueLevel = COLOR_40;
        break;
    
    case 13:
        greenLevel = COLOR_80;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    case 14:
        greenLevel = COLOR_60;
        redLevel = COLOR_0;
        blueLevel = COLOR_20;
        break;
    
    case 15:
        greenLevel = COLOR_0;
        redLevel = COLOR_40;
        blueLevel = COLOR_60;
        break;
    
    case 16:
        greenLevel = COLOR_60;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    default:
        greenLevel = COLOR_100;
        redLevel = COLOR_100;
        blueLevel = COLOR_100;
        break;
    }



    redLevel *= lightlevel;
    greenLevel *= lightlevel;
    blueLevel *= lightlevel;


    for (i = 0; i < 14; i++)
    {
        segmentdata[i][0] *= redLevel;
        segmentdata[i][1] *= greenLevel;
        segmentdata[i][2] *= blueLevel;

    }
    

}

void DotPoints_SetColor(uint8_t colornum , uint8_t lightlevel)
{
    int i;
    uint8_t greenLevel;
    uint8_t redLevel;
    uint8_t blueLevel;
    
    if(colornum == SYSTEMCOLOR)
        colornum = Color_Get(0);
    else if(colornum == COLOR_HISTORY_1)
        colornum = Color_Get(1);
    else if(colornum == COLOR_HISTORY_2)
        colornum = Color_Get(2);

    switch (colornum)
    {
    case 0:
        greenLevel = 0;
        redLevel = 0;
        blueLevel = 0;
        break;
    
    case 1:
        greenLevel = COLOR_100;
        redLevel = COLOR_100;
        blueLevel = COLOR_100;
        break;
    
    case 2:
        greenLevel = COLOR_0;
        redLevel = COLOR_0;
        blueLevel = COLOR_100;
        break;
    
    case 3:
        greenLevel = COLOR_0;
        redLevel = COLOR_100;
        blueLevel = COLOR_0;
        break;
    
    case 4:
        greenLevel = COLOR_100;
        redLevel = COLOR_0;
        blueLevel = COLOR_0;
        break;
    
    case 5:
        greenLevel = COLOR_10;
        redLevel = COLOR_0;
        blueLevel = COLOR_90;
        break;
    
    case 6:
        greenLevel = COLOR_0;
        redLevel = COLOR_80;
        blueLevel = COLOR_20;
        break;
    
    case 7:
        greenLevel = COLOR_100;
        redLevel = COLOR_20;
        blueLevel = COLOR_0;
        break;
    
    case 8:
        greenLevel = COLOR_20;
        redLevel = COLOR_0;
        blueLevel = COLOR_90;
        break;
    
    case 9:
        greenLevel = COLOR_0;
        redLevel = COLOR_60;
        blueLevel = COLOR_40;
        break;
    
    case 10:
        greenLevel = COLOR_100;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    case 11:
        greenLevel = COLOR_40;
        redLevel = COLOR_0;
        blueLevel = COLOR_40;
        break;
    
    case 12:
        greenLevel = COLOR_0;
        redLevel = COLOR_40;
        blueLevel = COLOR_40;
        break;
    
    case 13:
        greenLevel = COLOR_80;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    case 14:
        greenLevel = COLOR_60;
        redLevel = COLOR_0;
        blueLevel = COLOR_20;
        break;
    
    case 15:
        greenLevel = COLOR_0;
        redLevel = COLOR_40;
        blueLevel = COLOR_60;
        break;
    
    case 16:
        greenLevel = COLOR_60;
        redLevel = COLOR_40;
        blueLevel = COLOR_0;
        break;
    
    default:
        greenLevel = COLOR_100;
        redLevel = COLOR_100;
        blueLevel = COLOR_100;
        break;
    }



    redLevel *= lightlevel;
    greenLevel *= lightlevel;
    blueLevel *= lightlevel;


    for (i = 0; i < 4; i++)
    {
        dotpointdata[i][0] *= redLevel;
        dotpointdata[i][1] *= greenLevel;
        dotpointdata[i][2] *= blueLevel;

    }
    
}



void Segment(uint8_t segmentnum,uint8_t value, uint8_t colornum,uint8_t lightlevel)
{
    
    Segment_Map(value);
    Segment_SetColor(colornum,lightlevel);

    switch (segmentnum)
    {
    case 0:
        Segment_0_Update();
        break;
    case 1:
        Segment_1_Update();
        break;
    case 2:
        Segment_2_Update();
        break;
    case 3:
        Segment_3_Update();
        break;
    case 4:
        Segment_4_Update();
        break;
    case 5:
        Segment_5_Update();
        break;
    case 6:
        Segment_6_Update();
        break;
    case 7:
        Segment_7_Update();
        break;
    /*case 8:
        Segment_8_Update();
        break;*/
    case 9:
        Segment_9_Update();
        break;
    
    default:
        break;
    }

}


void DotPoints(uint8_t dotnum,uint8_t state, uint8_t colornum,uint8_t lightlevel)
{
   /* DotPoints_Map(dotnum,state);
    DotPoints_SetColor(colornum,lightlevel);
    DotPoints_Update();
    delay_us(10);*/

    if(state == 1)
        Segment(6,8,SYSTEMCOLOR,LEVEL_FULL);
    else
        Segment(6,8,0,LEVEL_FULL);

}
