


#include "DS3231.h"

void DS3231_I2CInit(void)
{
    I2C_DeInit();
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C,ENABLE);
    I2C_Init(100000, 0x00, I2C_DUTYCYCLE_2, I2C_ACK_NONE, I2C_ADDMODE_7BIT, 2);
    
    I2C_Cmd(ENABLE);
    DS3231_SetupSQW();

    GPIO_Init(SWQ_PIN,GPIO_MODE_IN_FL_IT); 
    EXTI_DeInit();
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOE,EXTI_SENSITIVITY_FALL_ONLY);
    
}


void I2CWrite(uint8_t slave, uint8_t addr, uint8_t * buffer, uint8_t size)
{
    // need to read regs to clear some flags
    volatile uint8_t reg;
    uint8_t index = 0;

    I2C_Cmd(ENABLE);
    I2C_GenerateSTART(ENABLE);
    // wait until start is sent
    while(!(I2C->SR1 & I2C_SR1_SB));
    // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.

    I2C_Send7bitAddress(slave, I2C_DIRECTION_TX);
    // wait addr bit, if set - we have ACK
    while(!(I2C->SR1 & I2C_SR1_ADDR));
    // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR3
    reg = I2C->SR1;
    reg = I2C->SR3;
    // EV8_1: TXE=1, shift register empty, data register empty, write DR register.

    I2C_SendData(addr);
    while(!(I2C->SR1 & I2C_SR1_TXE));

    
    while(size)
    {
        size--;
        I2C_SendData(buffer[index]);
        index++;
        // wait TXE, set after data moved to shift reg
        while(!(I2C->SR1 & I2C_SR1_TXE));
        // EV8: TXE=1, shift register not empty, data register empty, cleared by writing DR register
    }
    // wait bte
    while(!(I2C->SR1 & I2C_SR1_BTF));
    //EV8_2: TXE=1, BTF = 1, Program STOP request. TXE and BTF are cleared by HW by stop condition

    //stop after this byte
    I2C_GenerateSTOP(ENABLE);

    // wait MSL
    while((I2C->SR3 & I2C_SR3_MSL));
    I2C_Cmd(DISABLE);
}


void I2CRead(uint8_t slave, uint8_t addr, uint8_t *buffer, uint8_t size)
{
    // need to read regs to clear some flags
    volatile uint8_t reg;
    uint8_t index = 0;

    I2C_Cmd(ENABLE);
    I2C_GenerateSTART(ENABLE);
    // wait until start is sent
    //printf("I2CRead: wait tx SB\r\n");
    while(!(I2C->SR1 & I2C_SR1_SB));
    // EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
    
    I2C_Send7bitAddress(slave, I2C_DIRECTION_TX);
    // wait addr bit, if set - we have ACK
    //printf("I2CRead: wait tx ADDR\r\n");
    while(!(I2C->SR1 & I2C_SR1_ADDR));
    // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR3
    reg = I2C->SR1;
    reg = I2C->SR3;
    // EV8_1: TXE=1, shift register empty, data register empty, write DR register.

    I2C_SendData(addr);
    //printf("I2CRead: wait tx addr TXE\r\n");
    while(!(I2C->SR1 & I2C_SR1_TXE));
    //printf("I2CRead: wait tx addr BTF\r\n");
    while(!(I2C->SR1 & I2C_SR1_BTF));

    // we should ACK received data
    I2C->CR2 |= I2C_CR2_ACK;

    I2C_GenerateSTART(ENABLE);
    //printf("I2CRead: wait rx SB\r\n");
    while(!(I2C->SR1 & I2C_SR1_SB));

    I2C_Send7bitAddress(slave, I2C_DIRECTION_RX);
    // wait addr bit, if set - we have ACK
    //printf("I2CRead: wait rx ADDR\r\n");
    while(!(I2C->SR1 & I2C_SR1_ADDR));
    // EV6: ADDR=1, cleared by reading SR1 register followed by reading SR3
    reg = I2C->SR1;
    reg = I2C->SR3;

    
    while(size)
    {
        size--;
        if(size == 0)
        {
            // we should NACK last byte
            I2C->CR2 &= ~I2C_CR2_ACK;
        }
        //printf("I2CRead: wait rx RXNE\r\n");
        while(!(I2C->SR1 & I2C_SR1_RXNE));
        buffer[index] = I2C_ReceiveData();
        index++;
    }

    //stop after this byte
    I2C_GenerateSTOP(ENABLE);

    // wait MSL
    //printf("I2CRead: wait MSL\r\n");
    while((I2C->SR3 & I2C_SR3_MSL));
    I2C_Cmd(DISABLE);
}

void DS3231_SetupSQW(void)
{
    uint8_t value[1];
    value[0] = 0x00;
    I2CWrite(DS3231_ADDR, DS3231_CONTROL, value, 1);
}

void DS3231_GetTime(uint8_t *hour , uint8_t *minute , uint8_t *second)
{
    uint8_t time[3];

    I2CRead(DS3231_ADDR, DS3231_SECONDS, time, 3);

    *second = ((time[0]/16)*10) + (time[0]%16);
    *minute = ((time[1]/16)*10) + (time[1]%16);
    *hour = ((time[2]/16)*10) + (time[2]%16);
}

void DS3231_SetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    uint8_t time[3];

    time[0] = (second /10)*16 + (second % 10);
    time[1] = (minute /10)*16 + (minute % 10);
    time[2] = (hour /10)*16 + (hour % 10);
    I2CWrite(DS3231_ADDR, DS3231_SECONDS, time, 3);
}

void DS3231_GetAlarm(uint8_t *hour , uint8_t *minute , uint8_t *status)
{
    uint8_t time[2];

    I2CRead(DS3231_ADDR, DS3231_A1_MINUTES, time, 2);

    if(time[1] > 128)
    {
        time[1] -=128; 
        *status = 1;
    }
    else
        *status = 0;

    *minute = ((time[0]/16)*10) + (time[0]%16);
    *hour = ((time[1]/16)*10) + (time[1]%16);
}

void DS3231_SetAlarm(uint8_t hour, uint8_t minute , uint8_t status)
{
    uint8_t time[2];

    time[0] = (minute /10)*16 + (minute % 10);
    time[1] = (hour /10)*16 + (hour % 10);
    if(status == 1)
        time[1] += 128;
    I2CWrite(DS3231_ADDR, DS3231_A1_MINUTES, time, 2);
}


uint8_t DS3231_GetTemp(void)
{
    uint8_t tmp[1];
    I2CRead(DS3231_ADDR, DS3231_TEMP_MSB, tmp, 1);
    return (tmp[0] & 0x7F);
      
}




