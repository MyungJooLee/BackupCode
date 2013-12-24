#include "../inc/ioconf.h"




//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////





//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////
void initGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// PORT A

	// PORT B

	// PORT C

	// PORT D

	// PORT E

	// PORT F

	// PORT G


	/* ADC Input Pin Setting Example
  	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  	  GPIO_Init(GPIOF, &GPIO_InitStructure);
	 */

	/* GPIO Output Pin Setting Example
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	 */


	/* I2C Pin Setting Example
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =	 GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	 */
}
void setDefaultValueofGPIO(void)
{
	// Initial Value Setting for GPIO Pin
	// Peripheral Pin set 0.
	// Input pin set 0.
	// Output pin set Pre-Defined Default Value.

	// PORT A
	GPIO_Write(GPIOA, 0x0000);
	// PORT B
	GPIO_Write(GPIOB, 0x0000);
	// PORT C
	GPIO_Write(GPIOC, 0x0000);
	// PORT D
	GPIO_Write(GPIOD, 0x0000);
	// PORT E
	GPIO_Write(GPIOE, 0x0000);
	// PORT F
	GPIO_Write(GPIOF, 0x0000);
	// PORT G
	GPIO_Write(GPIOG, 0x0000);
}
