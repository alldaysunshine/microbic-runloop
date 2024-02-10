#import "AsmBridge.h"
#import "ThreadScheduler.h"
#include <functional>

#define STCSR 0xE000E010
#define STRVR 0xE000E014

extern char __stack;


ThreadScheduler::ThreadScheduler() {
	
}

ThreadScheduler& ThreadScheduler::getInstance()
{
	static ThreadScheduler instance; // Guaranteed to be destroyed.
						  // Instantiated on first use.
	return instance;
}

void ThreadScheduler::enable() {

}

void ThreadScheduler::disable() {

}

void ThreadScheduler::yield() {

}

void ThreadScheduler::switchContext() {

}
/*
void ThreadScheduler::createThread(std::function<void>(void)function) {
	Thread thread;
	
	int i = 0;
    int *stackIterator = 0;

    stackIterator = &amp;(thread->stack[(thread->stacksize>>2) - 1]);

    // This is the xPSR register. Should be set to 0x21000000
    *stackIterator = 0x21000000;
    stackIterator--;


    // This is the PC (Program Counter). This should point to the thread start function
    *stackIterator = (int*)threadFunc;
    stackIterator--;

    // This stack position is the LR (Link Return). This should point to the thread Stop function
    *stackIterator = ThreadStopFunc;
    stackIterator--;

    // r12 should be set to 0.
    *stackIterator = 0;
    stackIterator--;

    // Registers r1, r2 and r3 are function arguments,
    // but we set them to 0. Argument is passed in r0
    *stackIterator = 0; stackIterator--; // r1
    *stackIterator = 0; stackIterator--; // r2
    *stackIterator = 0; stackIterator--; // r3

    // Sets the register r0 position of the stack - This is the thread function argument
    *stackIterator = threadArgs;
    stackIterator--;

    // Sets to 0 the software stack frame of the registers r4-r11. This is needed because
    // when the switch context recovers this thread it will pop the software stack frame.
    for(i = 4; i &lt;= 11; i++){
        *stackIterator = 0;
        stackIterator--;
    }
}
*/
