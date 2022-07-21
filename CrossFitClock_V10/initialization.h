

#include "DS3231.h"
#include "IRRemote.h"
#include "WS2813LED.h"
#include "stm8s_clk.h"
#include "stm8s.h"
#include "stm8s_adc2.h"

uint8_t time_secbit = 0;
uint8_t time_Second = 0;
uint8_t time_Minute = 0;
uint8_t time_Hour = 0;



int time_Second_setting = 0;
int time_Minute_settin = 0;
int time_Hour_settin = 0;
int time_UnNormal = 120;
int time_TempShow = 0;
uint8_t time_update_all = 0;
uint8_t update_all = 1;

int time_Second_Cornometer = 0;
int time_Minute_Cornometer = 0;
int time_Hour_Cornometer = 0;
uint8_t cornometer_run = 0;


#define MODE_SET_CLOCK_HOUR     'H'
#define MODE_SET_CLOCK_MINUTE   'M'
#define MODE_CORNOMETER_UP      'U'
#define MODE_CORNOMETER_DN      'D'
#define MODE_NORMAL             'N'
#define BLINK                   'B'

uint8_t work_Mode = MODE_NORMAL;
uint8_t mode_show_12 = 0;
uint8_t mode_show_OFF = 0;
uint8_t mode_show_temp = 1;


void System_Clk_Config(void)
{

    CLK_DeInit();
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV2 | CLK_PRESCALER_CPUDIV1);

    /* Configure the Fcpu to DIV1*/
    //CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); 

    /* Configure the HSI prescaler to the optimal value */
    //CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);  
} 

void delay_ms(int time)
{
    int i;
    int j;
    int clock;
    clock = CLK_GetClockFreq()/20000;
    for ( j = 0; j < time; j++)
    {
        for (i = 0; i < clock; i++)
        {
            nop();
        }
    }
    
}


#define BUZZER_PIN         GPIOC,GPIO_PIN_4
void Buzz_Config(void)
{
    GPIO_Init(BUZZER_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
}



void Buzz(int time)
{
    GPIO_WriteHigh(BUZZER_PIN);
    delay_ms(time);
    GPIO_WriteLow(BUZZER_PIN);

}

#define NTC_PIN GPIOB,GPIO_PIN_1
void NTC_Init(void)
{
    ADC2_DeInit();
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
    GPIO_Init(NTC_PIN,GPIO_MODE_IN_FL_NO_IT);
    ADC2_Init(ADC2_CONVERSIONMODE_SINGLE,ADC2_CHANNEL_1 ,ADC2_PRESSEL_FCPU_D8, \
    ADC2_EXTTRIG_TIM,DISABLE,ADC2_ALIGN_RIGHT,ADC2_SCHMITTTRIG_CHANNEL1,DISABLE);
    
}

uint8_t NTC_Read(void)
{
    uint16_t ntc_adc = 0;
    int ret = 0;
    NTC_Init();
    ADC2_ClearFlag();
    ADC2_StartConversion();
    while(ADC2_GetFlagStatus() == RESET);
    ntc_adc = ADC2_GetConversionValue();

    ret = (ntc_adc/10) - 30;
    if(ret < 0)     ret  = 0 ;

    return (uint8_t)ret;

}

void StartUp_Show(void)
{
	int i;
	int j;
	

	for ( j = 0; j < 7; j++)
	{
		for (i = 0; i < j; i++)
		{	
			Segment(i,BLINK,SYSTEMCOLOR,LEVEL_FULL);		
		}
		delay_ms(1000);
	}
}

void Initializer(void)
{
    System_Clk_Config();
    Buzz_Config();
    Segment_Pins_Config();
    IRRemote_Config();
	NTC_Init();
    DS3231_I2CInit();
}

@far @interrupt void SQWHandledInterrupt (void)
{
	if (++time_Second > 59)
	{
		time_Second = 0;
		time_Minute++;
	}
	if(time_Minute > 59)
	{
		time_Minute = 0;
		time_Hour++;
	}
	if(time_Hour > 23)
	{
		time_Hour = 0;
	}
	

	if(time_secbit == 1)
	{
		time_secbit = 0;
	}
	else
	{
		time_secbit = 1;
	}

	if(++time_UnNormal > 60)
	{
		time_UnNormal = 60;
		work_Mode = MODE_NORMAL;
	}

	
	

	if(++time_update_all > 10)
	{
		time_update_all = 0;
		update_all = 1;
	}

	/*
	if(++time_TempShow > 20)
		time_TempShow = 0;
    */


}