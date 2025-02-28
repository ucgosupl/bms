#set(CMAKE_TOOLCHAIN_FILE ../cmake/toolchain-arm-gcc.cmake)
include(../cmake/compiler_flags.cmake)

add_subdirectory(infra/hal/Drivers)

set(INCLUDE_DIRS
    .
)

set(C_SRCS
    #app
    app/startup/stm32f4xx_hal_msp.c
    app/startup/stm32f4xx_it.c
    app/startup/system_stm32f4xx.c
    app/startup/hal_startup.c

    app/stdlib/syscalls.c
    app/stdlib/sysmem.c
    main.c

    #gateway
    gateway/controller_data/controller_data.c
    gateway/updater/updater.c
    gateway/server/server.c

    infra/server_protocol/server_protocol.c
)

set(ASM_SRCS
app/startup/startup_stm32f411retx.s
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