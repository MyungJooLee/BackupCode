#include "mon_timer.h"


//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////





//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////

void initTimer(TIM_TypeDef* TIMx , uint32_t nPeriod_us, bool bInterrupt, uint8_t NVIC_IRQChannel, uint32_t nIRQPriority)
{
	if(bInterrupt)
	{
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = NVIC_IRQChannel;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = nIRQPriority;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = nIRQPriority;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);	//  TIM IT enable
	}

	uint32_t nPeriod_ms = 0;

	if(nPeriod_us % 1000 == 0)
		nPeriod_ms = nPeriod_us/1000;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	if(nPeriod_ms)
	{
		TIM_TimeBaseStructure.TIM_Prescaler = 35999 ;
		TIM_TimeBaseStructure.TIM_Period = nPeriod_ms - 1;
	}
	else
	{
		TIM_TimeBaseStructure.TIM_Prescaler = 35;
		TIM_TimeBaseStructure.TIM_Period = nPeriod_us - 1;
	}

	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);


}

inline void startTimer(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx, ENABLE);
}
inline inline void stopTimer(TIM_TypeDef* TIMx)
{
	TIM_Cmd(TIMx, DISABLE);
}

