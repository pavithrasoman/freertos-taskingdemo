cmake_minimum_required(VERSION 3.13)
project(freertos_iot_gateway C)

set(CMAKE_C_STANDARD 99)

set(FREERTOS_KERNEL_PATH /home/pavithra/FreeRTOS-Kernel)

include_directories(
    include
    ${FREERTOS_KERNEL_PATH}/include
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/Posix
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/Posix/utils
)

add_executable(freertos_demo
    app/main.c

    # Core FreeRTOS files
    ${FREERTOS_KERNEL_PATH}/tasks.c
    ${FREERTOS_KERNEL_PATH}/queue.c
    ${FREERTOS_KERNEL_PATH}/list.c
    ${FREERTOS_KERNEL_PATH}/timers.c
    ${FREERTOS_KERNEL_PATH}/event_groups.c
    ${FREERTOS_KERNEL_PATH}/stream_buffer.c

    # Memory manager
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c

    # POSIX port
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/Posix/port.c

    # POSIX utils (VERY IMPORTANT)
    ${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
)

target_link_libraries(freertos_demo pthread m)
