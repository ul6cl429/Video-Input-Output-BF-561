#ifndef  __MAIN_DEFINED
#define __MAIN_DEFINED

#include "..\system.h"

/********************************************************************************/
/***** Current Global variables	and types									*****/
/***** All global variables are defined in main.c							*****/
/********************************************************************************/

// scalars
extern volatile int current_in_Frame;
extern volatile int background_in_Frame;

// DMA descriptor lists 

struct sDMA_descriptor {struct sDMA_descriptor* next_descriptor;
					    volatile short *start_address;
};
typedef struct sDMA_descriptor tDMA_descriptor;


extern tDMA_descriptor DMA_PPI0_first;
extern tDMA_descriptor DMA_PPI0_second;
extern tDMA_descriptor DMA_PPI0_third;
extern tDMA_descriptor DMA_PPI0_fourth;

extern volatile int can_start;
extern volatile int count;
extern volatile int count2;

/********************************************************************************/
/***** Prototypes functions													*****/
/********************************************************************************/


void InitPPI0(bool entire_field, bool pack32, tDMA_descriptor* First_Header, short pixel, short lines);
void DisablePPI0(void);
void EnablePPI0(void);
void Reset_ADV7183(void );
void Reset_ADV7179(void );

void InitSDRAM(void);
void Set_PLL(short CoreCLOCK_multiplier, short SCLK_divider);


/********************************************************************************/
/***** Prototypes interrupts												*****/
/********************************************************************************/

void InitInterrupts_coreA(void);

EX_INTERRUPT_HANDLER(PPI0_RxIsr);

EX_EXCEPTION_HANDLER(ex_handler_coreA);



#endif

