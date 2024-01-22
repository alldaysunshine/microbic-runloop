extern "C" void delay ( unsigned int );

extern "C" { void PUT32 ( unsigned int, unsigned int ); }
extern "C" { unsigned int GET32 ( unsigned int ); }
extern "C" { void WFI ( ); }

extern "C" { void led_setup ( ); }
extern "C" { void led_on ( ); }
extern "C" { void led_off ( ); }
extern "C" { void timer_on ( ); }

#define GPIO_DIR0 0x50000514
#define GPIO_DIRSET0 0x50000518
#define GPIO_DIRCLR0 0x5000051C
#define GPIO_DIR1 0x50000814
#define GPIO_DIRSET1 0x50000818
#define GPIO_DIRCLR1 0x5000081C

#define GPIO_OUTSET0 0x50000508
#define GPIO_OUTSET1 0x50000808

#define GPIO_OUTCLR0 0x5000050C
#define GPIO_OUTCLR1 0x5000080C

#define GPIO_IN0 0x50000510

#define GPIO_CNF0 0x50000700

