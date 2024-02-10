#import "InterruptHandler.h"


extern "C" void arm_systick_isr(); 
extern "C" void arm_gpiote_isr(); 

extern "C" uint8_t __stack[];
extern "C"  void _start(); 

extern "C" void arm_hardfault_isr(); 
extern "C" void arm_pendsv_isr(); 
extern "C" void arm_debugmon_isr(); 
extern "C" void arm_svc_isr(); 
extern "C" void arm_usagefault_isr();
extern "C" void arm_busfault_isr(); 
extern "C" void arm_memmanage_isr(); 
extern "C" void arm_nmi_isr(); 
extern "C" void arm_ignore_isr(); 

/* Vector table */
extern "C" 
__section(".data.init.enter")
void (* const __my_interrupt_vector[])(void) __attribute((aligned(128))) = {
	[0] = (void(*)(void))__stack,
	[1] = (void(*)(void))_start,
	[2] = arm_nmi_isr, 
	[3] = arm_hardfault_isr, 
	[4] = arm_memmanage_isr, 
	[5] = arm_busfault_isr, 
	[6] = arm_usagefault_isr, 
	[11] = arm_svc_isr, 
	[12] = arm_debugmon_isr, 
	[14] = arm_pendsv_isr, 
	[15] = arm_systick_isr,
	[16 + 6] = arm_gpiote_isr,  // Interrupt 6
	
};


