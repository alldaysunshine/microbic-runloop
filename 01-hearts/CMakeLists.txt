

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)

# which compilers to use for C and C++
set(CMAKE_ASM_COMPILER /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin/bin/clang)
set(CMAKE_C_COMPILER   /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin/bin/clang)
set(CMAKE_CXX_COMPILER /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin/bin/clang++)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH  /Applications/LLVMEmbeddedToolchainForArm-17.0.1-Darwin)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS_INIT "--target=armv6m-none-eabi -mcpu=cortex-m4 -mthumb -Wall -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS_INIT "--target=armv6m-none-eabi -mcpu=cortex-m4 -mthumb -Wall -fno-exceptions -fno-rtti")
set(CMAKE_ASM_FLAGS_INIT "--target=armv6m-none-eabi -mcpu=cortex-m4 -mthumb -Wall -fno-exceptions -fno-rtti")
set(CMAKE_EXE_LINKER_FLAGS_INIT "--target=armv6m-none-eabi -mcpu=cortex-m4 -mthumb -lcrt0 -lcrt0-hosted  -lsemihost")


project(01-hearts C CXX ASM)

add_executable(hearts Button.cc ButtonSource.cc ImageMatrix.cc InterruptHandler.cc 
	LEDDisplay.cc Observer.cc RunLoop.cc ScheduledBlock.cc Source.cc 
	SysTick.cc Timer.cc UART.cc main.cc unit.s)

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/main.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

add_custom_command(
    TARGET hearts
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex hearts hearts.hex
)