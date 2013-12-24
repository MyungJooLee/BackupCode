#include "../inc/isr.h"


//////////////////////////////////////////////////////
// Global Variable Define Section					//
//////////////////////////////////////////////////////





//////////////////////////////////////////////////////
// Function	Define Section							//
//////////////////////////////////////////////////////
void USART1_IRQHandler(void)
{
	UARTErrorType eUartError = UARTNormal;

	//__DEBUG("UART\r\n\n");

	if ((DEBUG_PORT->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
		eUartError = recieveUARTData_toQueue(DEBUG_PORT, &g_stDebugRecieveQueue);
		if(eUartError != UARTNormal)
		{
			__DEBUG("DEBUG ISR Receive Error Code : %03d\r\n", eUartError);
		}
		USART_ClearITPendingBit(DEBUG_PORT, USART_IT_RXNE);
	}
}

void TIM1_UP_IRQHandler(void)
{
	//if interrupt happens the do this
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET){
		//clear interrupt and start counting again to get precise freq
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

		//real job here
		//What is This ISR's JOB?
	}
}
void TIM2_IRQHandler(void)
{
	//if interrupt happens the do this
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		//clear interrupt and start counting again to get precise freq
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//real job here
	}

}

void TIM3_IRQHandler(void)
{
	//if interrupt happens the do this
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		//clear interrupt and start counting again to get precise freq
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

		// Shceduler Timer Real Job - 125ms
			//Start Sampling For CL!!


	}

}

void TIM4_IRQHandler(void)
{
	//if interrupt happens the do this
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
		//clear interrupt and start counting again to get precise freq
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		//real job here

	}

}

void TIM5_IRQHandler(void)
{
	//if interrupt happens the do this
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET){
		//clear interrupt and start counting again to get precise freq
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

		//real job here
	}

}
void CAN1_RX0_IRQHandler(void)
{
	QueueErrorType eQueueError = recieveCANData_toQueue(CAN_PORT, CAN_FIFO, &g_stCANRecieveQueue);
	if(eQueueError != QueueNormal)
	{
		__DEBUG("CAN ISR Receive Queue Error Code : %03d\r\n\n", eQueueError);
	}

	//CAN_ClearITPendingBit(CAN_PORT, CAN_IRQn);	// No Needs?
}

void EXTI0_IRQHandler(void)
{
	ITStatus bitstatus = RESET;
	bitstatus = EXTI_GetITStatus(EXTI_Line0);
	if(bitstatus == SET)
	{// Real Job(SET)

	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	ITStatus bitstatus = RESET;
	bitstatus = EXTI_GetITStatus(EXTI_Line1);
	if(bitstatus == SET)
	{// Real Job(SET)

	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
