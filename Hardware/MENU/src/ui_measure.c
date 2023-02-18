#include "ui_measure.h"
#include "adc.h"
#include "lcd.h"
#include "menu.h"
#include <stdio.h>

bool ConnectFlag = false;
bool MeasureFlag = false;
void UI_Measure_Load(void)
{
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 初始化 */
    MeasureFlag=true;
    ConnectFlag = false;
}

void UI_Measure_Exit(void)
{
    MeasureFlag=false;
    
    LCD_Fill(0, 0, 160, 80, BLACK); /*! 160*80 初始化 */
}

void UI_Measure_Task(void)
{
    if (ConnectFlag)
    {
        char strbuf[256];
        float Power;
        Get_Average_ADC_Converted_Value();

        sprintf(strbuf, "%.2fV ", ADC_Calculation_Value.SampleVoltage);
        LCD_ShowString(4, 0, (u8 *)strbuf, LIGHTGREEN, BLACK, 24, 0); //

        sprintf(strbuf, "%.2fA ", ADC_Calculation_Value.SampleCurrent);
        LCD_ShowString(4, 26, (u8 *)strbuf, LGRAY, BLACK, 24, 0); //

        Power = ADC_Calculation_Value.SampleCurrent * ADC_Calculation_Value.SampleVoltage;
        sprintf(strbuf, "%.2fW ", Power);
        LCD_ShowString(4, 52, (u8 *)strbuf, BRRED, BLACK, 24, 0); //

        sprintf(strbuf, "D+:%.2fV ", ADC_Calculation_Value.SampleVoltageDP);
        LCD_ShowString(92, 0, (u8 *)strbuf, GREEN, BLACK, 12, 0); //

        sprintf(strbuf, "D-:%.2fV ", ADC_Calculation_Value.SampleVoltageDN);
        LCD_ShowString(92, 12, (u8 *)strbuf, GREEN, BLACK, 12, 0); //

        sprintf(strbuf, "%.2f() ", ADC_Calculation_Value.Temperature);
        LCD_ShowString(92, 24, (u8 *)strbuf, RED, BLACK, 12, 0); //

        LCD_Fill(0, 8, 3, 70, LGRAY);
        LCD_Fill(86, 8, 89, 48, LGRAY);
    }
    else
    {
        LCD_ShowString(0, 16, "please connect the ", WHITE, BLACK, 16, 0); //
        LCD_ShowString(0, 32, "device,then push the", WHITE, BLACK, 16, 0); //
        LCD_ShowString(0, 48, " OK key.", WHITE, BLACK, 16, 0); //
    }
}
