#set(CMAKE_TOOLCHAIN_FILE ../cmake/toolchain-arm-gcc.cmake)
include(../cmake/compiler_flags.cmake)

add_subdirectory(Drivers)

set(INCLUDE_DIRS

    Core/Inc
   
    .
)

set(C_SRCS
    #Cube Generated
    Core/Src/stm32f4xx_hal_msp.c
    Core/Src/stm32f4xx_it.c
    Core/Src/system_stm32f4xx.c
    Core/Src/syscalls.c
    Core/Src/sysmem.c

    Core/Src/main.c

    #User Code

)

set(ASM_SRCS
    Core/Startup/startup_stm32f411retx.s
)

set(GLOBAL_DEFINES
    -DSTM32F411xE
    -DUSE_HAL_DRIVER
)

set(LINKED_LIBS

)

link_directories(

)

include_directories(${INCLUDE_DIRS})
add_definitions(${GLOBAL_DEFINES})

# generate elf file
add_arm_executable(${CMAKE_PROJECT_NAME} ${C_SRCS} ${ASM_SRCS})
arm_link_libraries(${CMAKE_PROJECT_NAME} ${LINKED_LIBS} PUBLIC STM32_HAL)