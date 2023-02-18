#include "adc.h"

#define NVR_V25_ADDR  ((uint32_t)0x1FFFF7D2) 

/* Voltage value ,temperature sensor under 3.3V and 25 celsius */
struct ADC_Converted_value      ADC_Converted_Value = {0};
struct ADC_Calculation_value    ADC_Calculation_Value = {0};

void ADC_CLK_Init(void)
{
    //n32g430的adc需要配置三个时钟，工作时钟源（只能配置为AHB_CLK），采样时钟源（HCLK, PLL），内部计时时钟(只能为1MHz)
    /* Enable ADC clocks */
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_GPIOA | RCC_AHB_PERIPH_ADC);
    RCC_APB2_Peripheral_Clock_Enable(RCC_APB2_PERIPH_AFIO);//用于温度传感器的复用IO
    /* RCC_ADCHCLK_DIV16*/
    ADC_Clock_Mode_Config(ADC_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ADC_1M_Clock_Config(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8);  //selsect HSI as RCC ADC1M CLK Source
}

void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_Structure_Initialize(&GPIO_InitStructure);
    /* Configure adc input as analog input -------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_4 |GPIO_PIN_3 | GPIO_PIN_1 | GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_MODE_ANALOG;
    GPIO_Peripheral_Initialize(GPIOA, &GPIO_InitStructure);
}

void DMA_Configuration(void)
{
    RCC_AHB_Peripheral_Clock_Enable(RCC_AHB_PERIPH_DMA);
    /* DMA channel1 configuration ----------------------------------------------*/
    DMA_InitType DMA_InitStructure;
    DMA_Structure_Initializes(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)&ADC_Converted_Value;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;//由寄存器移动到内存
    DMA_InitStructure.BufSize        = 5;
    DMA_InitStructure.MemoryInc      = DMA_MEM_INC_MODE_ENABLE;
    DMA_InitStructure.CircularMode   = DMA_CIRCULAR_MODE_ENABLE;//传输完成后，自动重置地址与计数
    DMA_InitStructure.Mem2Mem        = DMA_MEM2MEM_DISABLE;
    DMA_InitStructure.MemDataSize    = DMA_MEM_DATA_WIDTH_HALFWORD;//16bit
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_MODE_DISABLE;
    DMA_InitStructure.Priority       = DMA_CH_PRIORITY_HIGH;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_HALFWORD;//16bit
    DMA_Initializes(DMA_CH1, &DMA_InitStructure);
    DMA_Channel_Request_Remap(DMA_CH1 ,DMA_REMAP_ADC);
    /* Enable DMA channel1 */
    DMA_Channel_Enable(DMA_CH1);
}

void ADC_Configuration(void)
{
    ADC_CLK_Init();
    GPIO_Configuration();
    DMA_Configuration();

    ADC_InitType ADC_InitStructure;
    
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = ADC_REGULAR_LEN_5;
    ADC_Initializes(&ADC_InitStructure);
    /* ADC enable temperature  */
    ADC_Temperature_Sensor_And_Vrefint_Channel_Enable();
    
    /* ADC regular sequence configuration */
    ADC_Channel_Sample_Time_Config(SampleVoltage_IOPin ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(SampleVoltage_IOPin , ADC_REGULAR_NUMBER_1);
    ADC_Channel_Sample_Time_Config(SampleCurrent_IOPin ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(SampleCurrent_IOPin , ADC_REGULAR_NUMBER_2);
    ADC_Channel_Sample_Time_Config(SampleVoltageDP_IOPin ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(SampleVoltageDP_IOPin , ADC_REGULAR_NUMBER_3);
    ADC_Channel_Sample_Time_Config(SampleVoltageDN_IOPin ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(SampleVoltageDN_IOPin , ADC_REGULAR_NUMBER_4);
    ADC_Channel_Sample_Time_Config(ADC_CH_TEMP_SENSOR ,ADC_SAMP_TIME_55CYCLES5);
    ADC_Regular_Sequence_Conversion_Number_Config(ADC_CH_TEMP_SENSOR , ADC_REGULAR_NUMBER_5);
    

    /* Enable ADC DMA */
    ADC_DMA_Transfer_Enable();

    /* Enable ADC */
    ADC_ON();
    /* Check ADC Ready */
    while(ADC_Flag_Status_Get(ADC_RD_FLAG, ADC_FLAG_JENDCA, ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC calibration */
    ADC_Calibration_Operation(ADC_CALIBRATION_ENABLE);
    /* Check the end of ADC calibration */
    while (ADC_Calibration_Operation(ADC_CALIBRATION_STS) == SET)
        ;
}

void Start_ADC_Convert_Once(void)
{
    // 启动ADC转换
	ADC_Regular_Channels_Software_Conversion_Operation(ADC_EXTRTRIG_SWSTRRCH_ENABLE);
	// 等待ADC转换完成
	while (ADC_Flag_Status_Get(ADC_RUN_FLAG, ADC_FLAG_ENDC, ADC_FLAG_RDY) == 0)
	{
		__NOP();
	}
	ADC_Flag_Status_Clear(ADC_FLAG_ENDC);
	ADC_Flag_Status_Clear(ADC_FLAG_STR);
}

#define AVG_SLOPE  0.004f //温度曲线平均斜率
float TempCal(uint16_t TempAdVal)
{ 
	uint16_t V25Voltage = *((uint16_t*)NVR_V25_ADDR);
    float Temperate,tempValue;
    /* Voltage value of temperature sensor */
	  tempValue=TempAdVal*(3.3/4095);
    /* Get the temperature inside the chip */
	  Temperate=(V25Voltage-(tempValue*1000))/(AVG_SLOPE*1000)+25.0f;
    return Temperate;
}


void Get_Average_ADC_Converted_Value(void)
{
	ADC_Calculation_Value.SampleCurrent 	= 0;
	ADC_Calculation_Value.SampleVoltage 	= 0;
    ADC_Calculation_Value.SampleVoltageDP 	= 0;
    ADC_Calculation_Value.SampleVoltageDN 	= 0;
	int i;
    int maxNumber = 100;
	for(i=0;i<maxNumber;i++)
	{
		Start_ADC_Convert_Once();
		ADC_Calculation_Value.SampleCurrent		+= ADC_Converted_Value.SampleCurrent;
		ADC_Calculation_Value.SampleVoltage 	+= ADC_Converted_Value.SampleVoltage;
    	ADC_Calculation_Value.SampleVoltageDP	+= ADC_Converted_Value.SampleVoltageDP;
    	ADC_Calculation_Value.SampleVoltageDN 	+= ADC_Converted_Value.SampleVoltageDN;
		ADC_Calculation_Value.Temperature		+= ADC_Converted_Value.Temperature;
		SysTick_Delay_Us(10);
	}
	ADC_Calculation_Value.SampleCurrent 	/= maxNumber;
	ADC_Calculation_Value.SampleVoltage 	/= maxNumber;
    ADC_Calculation_Value.SampleVoltageDP 	/= maxNumber;
    ADC_Calculation_Value.SampleVoltageDN 	/= maxNumber;
	ADC_Calculation_Value.Temperature		/= maxNumber;

	ADC_Calculation_Value.SampleCurrent = ADC_Converted_Value.SampleCurrent*(3.3f/50/0.01f/4095);//INA199电压放大50倍
	ADC_Calculation_Value.SampleVoltage = ADC_Converted_Value.SampleVoltage*(3.3f*10.1f/4095);
    ADC_Calculation_Value.SampleVoltageDP = ADC_Calculation_Value.SampleVoltageDP*3.3f/4095;
    ADC_Calculation_Value.SampleVoltageDN = ADC_Calculation_Value.SampleVoltageDN*3.3f/4095;
	ADC_Calculation_Value.Temperature = TempCal(ADC_Converted_Value.Temperature);
}

