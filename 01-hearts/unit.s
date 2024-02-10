.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
	ldr r1, [r0]
	mov r0, r1
	bx lr

.thumb_func
.globl WFI
WFI:
	WFI
	bx lr

.thumb_func
.globl delay
delay:                          @ Delay in microseconds (64MHz clock)
    lsls r0, r0, #4             @ 62.5ns per iteration
repeat: 
    subs r0, #1                 @ One iteration takes 4 cycles
    nop
    bhi repeat
    bx lr


.thumb_func
.globl led_setup
led_setup:
	## Set LED MASK 
    ldr r0, =0x50000514         @ GPIO0_DIR register
    ldr r1, =0xd1688800        	@ LED pins as outputs
    str r1, [r0]
     bx lr

 .thumb_func
.globl led_on
led_on:                         @ Delay in microseconds (64MHz clock)
    ldr r4, =0x50000508         @ Address of GPIO0_OUT register
    ldr r5, =0x5000050C         @ Address of GPIO1_OUT register
    ldr r6, =0x50008800         @ Bit pattern 0 for dot
    str r6, [r4]                @ Light an LED
    bx lr
    

.thumb_func
.globl led_off
led_off:                          @ Delay in microseconds (64MHz clock)
    ldr r4, =0x50000508         @ Address of GPIO0_OUT register
    ldr r5, =0x5000050C         @ Address of GPIO1_OUT register
    ldr r6, =0x50008800         @ Bit pattern 0 for dot
    str r6, [r5]                @ All LEDs off
    bx lr

.thumb_func
.globl timer_on
timer_on:                          @ Delay in microseconds (64MHz clock)
    bx lr
    
.thumb_func
.globl arm_systick_isr
arm_systick_isr:         
	PUSH {R4-R11}
	PUSH {LR} 
	PUSH {R0}
	bl display_systick_isr
	POP {R0}
	POP {LR} 
	POP {R4-R11}
	bx lr
