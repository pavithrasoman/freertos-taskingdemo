# FreeRTOS Tasking Demo (Linux POSIX)

This is a demonstration project showcasing **FreeRTOS features** on a Linux (POSIX) simulation.

It demonstrates:

- Tasks with different priorities
- Queue communication between tasks
- Mutex for thread-safe printing
- Event Groups
- Software Timers

## Tasks

1. **Sensor Task**  
   - Simulates a sensor reading every second  
   - Sends values to a queue  
   - Sets an event group bit signaling data is ready  

2. **Monitor Task**  
   - Waits for the sensor event  
   - Reads data from the queue  
   - Prints sensor value and free heap size  

## Timer

- A software timer triggers every 5 seconds and prints a message.

## FreeRTOS Features Demonstrated

- **Tasks** (`xTaskCreate`)  
- **Queues** (`xQueueCreate`, `xQueueSend`, `xQueueReceive`)  
- **Mutexes** (`xSemaphoreCreateMutex`, `xSemaphoreTake`, `xSemaphoreGive`)  
- **Event Groups** (`xEventGroupCreate`, `xEventGroupSetBits`, `xEventGroupWaitBits`)  
- **Software Timer** (`xTimerCreate`, `xTimerStart`)

## Build & Run

```bash
git clone <your-github-repo>
cd freertos-tasking-demo
mkdir build
cd build
cmake ..
make
./freertos_demo

Output:
[Monitor] Sensor Value: 1, Free Heap: 10240
[Monitor] Sensor Value: 2, Free Heap: 10192
[Timer] Sensor timer triggered!
[Monitor] Sensor Value: 3, Free Heap: 10144
...

Project Structure:

freertos-tasking-demo/
├─ app/
│  └─ main.c
├─ include/
│  └─ FreeRTOSConfig.h
├─ CMakeLists.txt
└─ README.md


