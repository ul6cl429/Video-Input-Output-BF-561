#include "cdefBF561.h"
#include "ccblkfn.h"
#include "DMA_Init.h"

/*
	1. 參數
		source 		: source
		destination : destination
		pixel		: width
		lines		: height
		mod_32		: 是否啟動32bit資料傳輸模式
		x_modify	: x_modify
		
		mmr_base_addr	: MMR Base Address
		netxt_desc_ptr	: NEXT_DESC_PTR
		start_addr		: START_ADDR
		dma_config		: DMA_CONFIG
		x_count			: X_COUNT
		x_modify		: X_MODIFY
		y_count			: Y_COUNT
		y_modift		: Y_MODIFY
		
	2. 備註
		無
*/

void configureDMA(void *mmr_base_addr, void *netxt_desc_ptr, void *start_addr, int dma_config, int x_count, int x_modify, int y_count, int y_modify)
{
	volatile unsigned short *cmmr_base_addr = (volatile unsigned short *)(mmr_base_addr);
	
	*(_PTR_TO_VOL_VOID_PTR cmmr_base_addr)		= netxt_desc_ptr;	// NEXT_DESC_PTR
	*(_PTR_TO_VOL_VOID_PTR cmmr_base_addr + 1)	= start_addr;		// START_ADDR
	*(cmmr_base_addr + 4)						= dma_config;		// DMA_CONFIG 
	*(cmmr_base_addr + 8)						= x_count;			// X_COUNT
	*(cmmr_base_addr + 10)						= x_modify;			// X_MODIFY
	*(cmmr_base_addr + 12)						= y_count;			// Y_COUNT
	*(cmmr_base_addr + 14)						= y_modify;			// Y_MODIFY
	ssync();
}

void DisableDMA(void *mmr_base_addr)
{
	volatile unsigned short *cmmr_base_addr = (volatile unsigned short *)(mmr_base_addr);
	
	*(cmmr_base_addr + 4) &= ~DMAEN;			// DMA_CONFIG
	ssync();
}

void EnableDMA(void *mmr_base_addr)
{
	volatile unsigned short *cmmr_base_addr = (volatile unsigned short *)(mmr_base_addr);
	
	*(cmmr_base_addr + 4) |= DMAEN;				// DMA_CONFIG
	ssync();
}

void WaitDMA(void *mmr_base_addr)
{
	volatile unsigned short *cmmr_base_addr = (volatile unsigned short *)(mmr_base_addr);
	
	while(!(*(cmmr_base_addr + 20) & DMA_DONE));	//等待工作完成
	*(cmmr_base_addr + 20) |= DMA_DONE;
}

void IdleDMA(void *mmr_base_addr)
{
	volatile unsigned short *cmmr_base_addr = (volatile unsigned short *)(mmr_base_addr);
	
	while(*(cmmr_base_addr + 20) & DMA_RUN);		//空閒的DMA Channel
}
