#ifndef _ADC_H
#define _ADC_H

#include "n32g430.h"
#include "bsp_delay.h"


#define SampleVoltageDP_IOPin ADC_Channel_01_PA0
#define SampleVoltageDN_IOPin ADC_Channel_02_PA1
#define SampleCurrent_IOPin   ADC_Channel_04_PA3
#define SampleVoltage_IOPin   ADC_Channel_05_PA4

struct ADC_Converted_value
{
    uint16_t SampleVoltage;
    uint16_t SampleCurrent;
    uint16_t SampleVoltageDP;
    uint16_t SampleVoltageDN;
    uint16_t Temperature;
};

struct ADC_Calculation_value
{
    float SampleVoltage;
    float SampleCurrent;
    float SampleVoltageDP;
    float SampleVoltageDN;
    float Temperature;
};

extern struct ADC_Converted_value   ADC_Converted_Value;
extern struct ADC_Calculation_value ADC_Calculation_Value;

void ADC_Configuration(void);
void Start_ADC_Convert_Once(void);
float TempCal(uint16_t TempAdVal);
void Get_Average_ADC_Converted_Value(void);

#endif /* _ADC_H */
