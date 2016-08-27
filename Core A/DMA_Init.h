#ifndef  __DMA_INIT_DEFINED
#define __DMA_INIT_DEFINED

/* DMA1 Controller registers (0xFFC0 1C00-0xFFC0 1FFF) */
#define DMA1_0_base_addr 	(void *)0xFFC01C00 		/* DMA1 Channel 0 Next Descripter Ptr Reg */
#define DMA1_1_base_addr 	(void *)0xFFC01C40 		/* DMA1 Channel 1 Next Descripter Ptr Reg */
#define DMA1_2_base_addr 	(void *)0xFFC01C80 		/* DMA1 Channel 2 Next Descripter Ptr Reg */
#define DMA1_3_base_addr 	(void *)0xFFC01CC0 		/* DMA1 Channel 3 Next Descripter Ptr Reg */
#define DMA1_4_base_addr 	(void *)0xFFC01D00 		/* DMA1 Channel 4 Next Descripter Ptr Reg */
#define DMA1_5_base_addr 	(void *)0xFFC01D40 		/* DMA1 Channel 5 Next Descripter Ptr Reg */
#define DMA1_6_base_addr 	(void *)0xFFC01D80 		/* DMA1 Channel 6 Next Descripter Ptr Reg */
#define DMA1_7_base_addr 	(void *)0xFFC01DC0 		/* DMA1 Channel 7 Next Descripter Ptr Reg */
#define DMA1_8_base_addr 	(void *)0xFFC01E00 		/* DMA1 Channel 8 Next Descripter Ptr Reg */
#define DMA1_9_base_addr 	(void *)0xFFC01E40		/* DMA1 Channel 9 Next Descripter Ptr Reg */
#define DMA1_10_base_addr 	(void *)0xFFC01E80 		/* DMA1 Channel 10 Next Descripter Ptr Reg */
#define DMA1_11_base_addr 	(void *)0xFFC01EC0 		/* DMA1 Channel 11 Next Descripter Ptr Reg */

/* Memory DMA1 Controller registers (0xFFC0 1E80-0xFFC0 1FFF) */
#define MDMA1_D0_base_addr 	(void *)0xFFC01F00 		/*MemDMA1 Stream 0 Destination Next Descriptor Ptr Reg */
#define MDMA1_S0_base_addr 	(void *)0xFFC01F40 		/*MemDMA1 Stream 0 Source Next Descriptor Ptr Reg */
#define MDMA1_D1_base_addr 	(void *)0xFFC01F80 		/*MemDMA1 Stream 1 Destination Next Descriptor Ptr Reg */
#define MDMA1_S1_base_addr 	(void *)0xFFC01FC0 		/*MemDMA1 Stream 1 Source Next Descriptor Ptr Reg */

/* DMA2 Controller registers (0xFFC0 0C00-0xFFC0 0DFF) */
#define DMA2_0_base_addr 	(void *)0xFFC00C00 		/*DMA2 Channel 0 Next Descripter Ptr Reg */
#define DMA2_1_base_addr 	(void *)0xFFC00C40 		/*DMA2 Channel 1 Next Descripter Ptr Reg */
#define DMA2_2_base_addr 	(void *)0xFFC00C80 		/*DMA2 Channel 2 Next Descripter Ptr Reg */
#define DMA2_3_base_addr 	(void *)0xFFC00CC0 		/*DMA2 Channel 3 Next Descripter Ptr Reg */
#define DMA2_4_base_addr 	(void *)0xFFC00D00 		/*DMA2 Channel 4 Next Descripter Ptr Reg */
#define DMA2_5_base_addr 	(void *)0xFFC00D40 		/*DMA2 Channel 5 Next Descripter Ptr Reg */
#define DMA2_6_base_addr 	(void *)0xFFC00D80 		/*DMA2 Channel 6 Next Descripter Ptr Reg */
#define DMA2_7_base_addr 	(void *)0xFFC00DC0 		/*DMA2 Channel 7 Next Descripter Ptr Reg */
#define DMA2_8_base_addr 	(void *)0xFFC00E00 		/*DMA2 Channel 8 Next Descripter Ptr Reg */
#define DMA2_9_base_addr 	(void *)0xFFC00E40 		/*DMA2 Channel 9 Next Descripter Ptr Reg */
#define DMA2_10_base_addr	(void *)0xFFC00E80 		/*DMA2 Channel 10 Next Descripter Ptr Reg */
#define DMA2_11_base_addr 	(void *)0xFFC00EC0 		/*DMA2 Channel 11 Next Descripter Ptr Reg */

/* Memory DMA2 Controller registers (0xFFC0 0E80-0xFFC0 0FFF) */
#define MDMA2_D0_base_addr 	(void *)0xFFC00F00 		/*MemDMA2 Stream 0 Destination Next Descriptor Ptr Reg */
#define MDMA2_S0_base_addr 	(void *)0xFFC00F40 		/*MemDMA2 Stream 0 Source Next Descriptor Ptr Reg */
#define MDMA2_D1_base_addr 	(void *)0xFFC00F80 		/*MemDMA2 Stream 1 Destination Next Descriptor Ptr Reg */
#define MDMA2_S1_base_addr 	(void *)0xFFC00FC0 		/*MemDMA2 Stream 1 Source Next Descriptor Ptr Reg */

/* Internal Memory DMA Registers (0xFFC0_1800 - 0xFFC0_19FF) */
#define IMDMA_D0_base_addr 	(void *)0xFFC01800 		/*IMDMA Stream 0 Destination Next Descriptor Ptr Reg */
#define IMDMA_S0_base_addr 	(void *)0xFFC01840 		/*IMDMA Stream 0 Source Next Descriptor Ptr Reg */
#define IMDMA_D1_base_addr 	(void *)0xFFC01880 		/*IMDMA Stream 1 Destination Next Descriptor Ptr Reg */
#define IMDMA_S1_base_addr 	(void *)0xFFC018C0 		/*IMDMA Stream 1 Source Next Descriptor Ptr Reg */

//configure DMA, IMDMA
void configureDMA(void *mmr_base_addr, void *netxt_desc_ptr, void *start_addr, int dma_config, int x_count, int x_modify, int y_count, int y_modify);
void DisableDMA(void *mmr_base_addr);
void EnableDMA(void *mmr_base_addr);
void WaitDMA(void *mmr_base_addr);
void IdleDMA(void *mmr_base_addr);

#endif
