#include "main.h"

/********************************************************************************/
/***** Defines the interrupt service routines for CoreA						*****/
/********************************************************************************/


EX_INTERRUPT_HANDLER(PPI0_RxIsr) {

	*pDMA1_0_IRQ_STATUS |= DMA_DONE;		// acknowledge interrupt

	semaphore_frames_received = true;		// signal core B that a frame was received
	//semaphore_frames_received = false;
	//can_start=1;
	
	++current_in_Frame;

	current_in_Frame = (current_in_Frame) % 4;
	
/*	if(current_in_Frame == 3)StartDMA=1;
	else(current_in_Frame == 2)StartDMA=0;*/
	
	if(current_in_Frame == 0) background_in_Frame=3;
	else background_in_Frame = current_in_Frame-1;
    
}



EX_EXCEPTION_HANDLER(ex_handler_coreA) {
	while(1);
}

