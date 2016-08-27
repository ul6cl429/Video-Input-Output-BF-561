#include "main.h"
#include "DMA_Init.h"
#include "time.h"
// set up DMA descriptors (one for each frame, then repeat)
// small descriptor model, only start address needs to be fetched

tDMA_descriptor DMA_PPI0_first = 	{&DMA_PPI0_second, sFrame0};
tDMA_descriptor DMA_PPI0_second = 	{&DMA_PPI0_third , sFrame1};
tDMA_descriptor DMA_PPI0_third = 	{&DMA_PPI0_fourth, sFrame2};
tDMA_descriptor DMA_PPI0_fourth = 	{&DMA_PPI0_first , sFrame3};
//************************************************************************************
char tFrame0[520*2];  		//處理位址1
char tFrame1[520*2];  		//處理位址2
char tFrame2[520*2];  		//處理位址3

char bFrame0[520*2];  		//背景
char bFrame1[520*2];  		//背景
char bFrame2[520*2];  		//背景

volatile short *frame_list[4]={	(short *)sFrame0,
								(short *)sFrame1,
								(short *)sFrame2,
								(short *)sFrame3};   

volatile char *MDMA_current[3]={tFrame0,tFrame1,tFrame2};  //處理位址
volatile char *MDMA_background[3]={bFrame0,bFrame1,bFrame2};

int LineBuffer=0;
//************************************************************************************
volatile int current_in_Frame  = -1;		// 0, 1, 2 or 3  ... indicates the last frame that was received COMPLETELY
volatile int background_in_Frame  = -1;
bool Set_PACK32 = false;
bool Set_Entire_Field = false;
//************************************************************************************
//volatile int can_start = 0;  //ppi 

short temp[1]={0};
//************************************************************************************
void main() 
{
	int j;
	// unblock Core B if dual core operation is desired	
#ifndef RUN_ON_SINGLE_CORE
	*pSICA_SYSCR &= 0xFFDF; // clear bit 5 to unlock  
#endif

	// set Clocks
	Set_PLL( (short)(CORECLK/CLKIN), (short)(CORECLK/SYSCLK));			// sets Core and System Clocks to the values defined in system.h 

	// initialise SDRAM
	InitSDRAM();
	*pTC_PER = 0x0770;			// set DMA traffic control register to favour unidirectional transfers to SDRAM
	
	Reset_ADV7179();			// initialise Video Encoder ADV7179	
	Reset_ADV7183();			// initialise Video Decoder ADV7183	
	
	// initialise PPI0 and associated DMA channel for Video IN
	current_in_Frame  = -1;				// no frames received yet
	semaphore_frames_received = false;	// do not start output stream yet

	Set_Entire_Field = false;
#ifdef ENTIRE_FIELD_MODE
	Set_Entire_Field = true;
#endif

	Set_PACK32 = false;
#ifdef PACK_32
	Set_PACK32 = true;
#endif
	
	InitPPI0(Set_Entire_Field, Set_PACK32, &DMA_PPI0_first, PIXEL_PER_LINE, LINES_PER_FRAME);			
	
	InitInterrupts_coreA();		// initialise Interrupts
	//*********************************************************************
	//read background
	configureDMA(	MDMA1_S0_base_addr,		NULL,               
					temp,					WDSIZE_32,
					/*1440/4*/130*2,			4,
					0,						0);	
					
	configureDMA(	MDMA1_D0_base_addr,		NULL,               
					temp,					WDSIZE_32 | DI_EN | WNR ,
					130*2,						4,
					0,						0);
	//read current
	configureDMA(	MDMA2_S0_base_addr,		NULL,               
					temp,					WDSIZE_32,
					/*1440/4*/130*2,			4,
					0,						0);	
					
	configureDMA(	MDMA2_D0_base_addr,		NULL,               
					temp,					WDSIZE_32 | DI_EN | WNR ,
					130*2,						4,
					0,						0);		
    //**********************************************************************
	//write 
	configureDMA(	MDMA1_S1_base_addr,		NULL, 				
					temp,					WDSIZE_32,
					130*2,						4,
					0,						0);						

	configureDMA(	MDMA1_D1_base_addr,		NULL,			
					temp,					WDSIZE_32 | DI_EN | WNR ,
					130*2,						4,
					0,						0);				
						
	configureDMA(	MDMA2_S1_base_addr,		NULL,				
					temp,					WDSIZE_32,
					130*2,						4,
					0,						0);						

	configureDMA(	MDMA2_D1_base_addr,		NULL,				
					temp,					WDSIZE_32 | DI_EN | WNR ,
					130*2,						4,
					0,						0);
	//***********************************************************************
	EnablePPI0();						
	while(1)
	{
		idle();
		if(semaphore_frames_received)
		{	
			//read background			
			*pMDMA1_S0_START_ADDR = (void *)(frame_list[background_in_Frame]+110+5284);//Read address (sframe0 sframe1) 
			*pMDMA1_D0_START_ADDR = (void *)(MDMA_background[(LineBuffer%3)]);	//處理位址(tFrame0 tFrame1 tFrame2)		
		 	EnableDMA( 	MDMA1_S0_base_addr);
	 	 	EnableDMA( 	MDMA1_D0_base_addr);
	        //read current
			*pMDMA2_S0_START_ADDR = (void *)(frame_list[current_in_Frame]+110+5284);//Read address (sframe0 sframe1) 
			*pMDMA2_D0_START_ADDR = (void *)(MDMA_current[(LineBuffer%3)]);	//處理位址(tFrame0 tFrame1 tFrame2)		
		 	EnableDMA( 	MDMA2_S0_base_addr);
	 	 	EnableDMA( 	MDMA2_D0_base_addr);	 	    
	 	 	
	 	 	for (LineBuffer=0 ;LineBuffer<250;LineBuffer++)
	 	 	{
	 	 		IdleDMA(MDMA1_D0_base_addr);
	 	 		//read background
				*pMDMA1_S0_START_ADDR = (void *)(frame_list[background_in_Frame]+(LineBuffer+1)*858+110+5284);
				*pMDMA1_D0_START_ADDR = (void *)(MDMA_background[((LineBuffer+1)%3)]);	
			 	EnableDMA( 	MDMA1_S0_base_addr);
	 		 	EnableDMA( 	MDMA1_D0_base_addr);
	 	 		//read current
	 	 		*pMDMA2_S0_START_ADDR = (void *)(frame_list[current_in_Frame]+(LineBuffer+1)*858+110+5284);
				*pMDMA2_D0_START_ADDR = (void *)(MDMA_current[((LineBuffer+1)%3)]);
		 		EnableDMA( 	MDMA2_S0_base_addr);
	 	 		EnableDMA( 	MDMA2_D0_base_addr);
	 	 		
	 	 		//motion dection	 ****	 				
	 	 		for(j=1;j<(520*2);j+=2)
	 	 		{
	 	 			if(	(*(MDMA_current[(LineBuffer%3)] + j  ) >= (*(MDMA_background[(LineBuffer%3)] + j  )+10)) 
	 	 				||
	 	 				(*(MDMA_current[(LineBuffer%3)] + j  ) <= (*(MDMA_background[(LineBuffer%3)] + j  )-10)))
	 	 			{	
	 	 				*(MDMA_current[(LineBuffer%3)] + j  ) = 0x80;
	 	 				*(MDMA_current[(LineBuffer%3)] + (j-1)  ) = 0x00;
	 	 			}
	 	 			//else *(MDMA_current[(LineBuffer%3)] + j  ) = 0x00;
	 	 		}
	 	 		//***************************** 	 				
	 	 		IdleDMA(MDMA1_D1_base_addr);
	 	 		IdleDMA(MDMA2_D1_base_addr);
	 	 		//write		
				*pMDMA1_S1_START_ADDR = (void *)(MDMA_current[(LineBuffer%3)]);
				*pMDMA1_D1_START_ADDR = (void *)(frame_list[background_in_Frame]+LineBuffer*858+110+5284);//858 = 1716 / 2 (char is 2 bytes)
				*pMDMA2_S1_START_ADDR = (void *)(MDMA_current[(LineBuffer%3)]);
				*pMDMA2_D1_START_ADDR = (void *)(frame_list[background_in_Frame]+LineBuffer*858+110+230938);//858 = 1716 / 2 (char is 2 bytes)	   					   						
		 		EnableDMA( 	MDMA1_S1_base_addr);
	 	 		EnableDMA( 	MDMA1_D1_base_addr);
		 		EnableDMA( 	MDMA2_S1_base_addr);
	 	 		EnableDMA( 	MDMA2_D1_base_addr);			
	 	 	}	 	 	
		}	

		// check for PPI framing error
		if (*pPPI0_STATUS & FT_ERR)
		{
			// error occurred -- clear error and restart video transfer
			*pPPI0_STATUS &= ~FT_ERR;
			semaphoreResetVideo = true;
			
			while(semaphoreResetVideo);     // wait for core B to reset video
			
			DisablePPI0();
			current_in_Frame  = -1;         // no frames received yet
			semaphore_frames_received = false;
			
			InitPPI0(Set_Entire_Field, Set_PACK32, &DMA_PPI0_first, PIXEL_PER_LINE, LINES_PER_FRAME);
			
			EnablePPI0();
		}
		//idle();		//   do nothing
	}	//while	
}	    //main

