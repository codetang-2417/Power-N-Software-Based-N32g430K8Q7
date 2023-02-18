
#include "sysclk.h"

/**
 * @brief 设置时钟源为HSI内部8MHz时钟，启用锁相环倍频至128MHz
 *
 * @param NULL
 */
void Set_SysClock_To_PLL128MHz(void)
{

	ErrorStatus HSIStartUpStatus;
	RCC_Reset(); /* Enable HSI */
	RCC_HSI_Enable();

	/* Wait till HSI is ready */
	HSIStartUpStatus = RCC_HSI_Stable_Wait();

	if (HSIStartUpStatus != SUCCESS)
	{
		/* If HSI fails to start-up, the application will have wrong clock
		   configuration. User can add here some code to deal with this
		   error */

		/* Go to infinite loop */
		while (1)
			;
	}
	FLASH_Latency_Set(FLASH_AC_LATENCY_3);

	/* HCLK = SYSCLK/2 */
	RCC_Hclk_Config(RCC_SYSCLK_DIV1);

	/* PCLK2 = HCLK MAX 64MHz*/
	RCC_Pclk2_Config(RCC_HCLK_DIV2);

	/* PCLK1 = HCLK MAX 32MHz*/
	RCC_Pclk1_Config(RCC_HCLK_DIV4);

	RCC_PLL_Config(RCC_PLL_SRC_HSI_DIV2, RCC_PLL_MUL_32); //128MHz

	/* Enable PLL */
    RCC_PLL_Enable();

    /* Wait till PLL is ready */
   // while (RCC_Flag_Status_Get(RCC_FLAG_PLLRD) == RESET);
     /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }
    /* Select PLL as system clock source */
    RCC_Sysclk_Config(RCC_SYSCLK_SRC_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_Sysclk_Source_Get() != RCC_CFG_SCLKSTS_PLL);
}
