#import "InterruptHandler.h"


extern "C" void arm_systick_isr(); 
extern "C" void arm_gpiote_isr(); 

extern "C" uint8_t __stack[];
extern "C"  void _start(); 

#define i(addr,name)	[(addr)/4] = (void(*)(void)) arm_ ## name ## _isr

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
	i(0x08, nmi),
	i(0x0c, hardfault),
	i(0x10, memmanage),
	i(0x14, busfault),
	i(0x18, usagefault),
	i(0x2c, svc),
	i(0x30, debugmon),
	i(0x38, pendsv),
	i(0x3c, systick),
	[16 + 6] = arm_gpiote_isr,  // Interrupt 6
	
};


