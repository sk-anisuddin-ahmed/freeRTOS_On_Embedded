# FreeRTOS API

# 1. Mutex

## What it is
- A **lock** to protect a **shared resource** (UART, I2C, global variable, file, LCD)
- Only **one task** can own it at a time
- Has **priority inheritance** (important for real-time systems)

## When to use
- When **multiple tasks access the same resource**

## APIs
```c
SemaphoreHandle_t xSemaphoreCreateMutex(void);
BaseType_t xSemaphoreTake(SemaphoreHandle_t mtx, TickType_t timeout);
BaseType_t xSemaphoreGive(SemaphoreHandle_t mtx);
```

---

# 2. Binary Semaphore

## What it is
- A **signal flag** (0 or 1)
- Used for **task ↔ task** or **ISR ↔ task** signaling
- Does **NOT** provide priority inheritance

## When to use
- Event signaling (button pressed, DMA done, interrupt happened)

## APIs
```c
SemaphoreHandle_t xSemaphoreCreateBinary(void);
BaseType_t xSemaphoreTake(SemaphoreHandle_t sem, TickType_t timeout);
BaseType_t xSemaphoreGive(SemaphoreHandle_t sem);
BaseType_t xSemaphoreGiveFromISR(SemaphoreHandle_t sem, BaseType_t *hpw);
```

---

# 3. Counting Semaphore

## What it is
- A **counter-based semaphore** (0 ... N)
- Used to **count resources or events**

## When to use
- Limit access to **N identical resources** (buffers, connections, slots)

## APIs
```c
SemaphoreHandle_t xSemaphoreCreateCounting(UBaseType_t max, UBaseType_t init);
BaseType_t xSemaphoreTake(SemaphoreHandle_t sem, TickType_t timeout);
BaseType_t xSemaphoreGive(SemaphoreHandle_t sem);
```

---

# 4. Queue

## What it is
- A **FIFO buffer** for sending **data** between tasks or ISR
- Can send **int, struct, packets, messages**

## When to use
- When you need to **transfer data**, not just signal

## APIs
```c
QueueHandle_t xQueueCreate(UBaseType_t len, UBaseType_t item_size);
BaseType_t xQueueSend(QueueHandle_t q, const void *item, TickType_t timeout);
BaseType_t xQueueReceive(QueueHandle_t q, void *item, TickType_t timeout);
BaseType_t xQueueSendFromISR(QueueHandle_t q, const void *item, BaseType_t *hpw);
```

---

# 5. Task Notification

## What it is
- A **built-in signal variable inside each task**
- **Fastest IPC** in FreeRTOS
- Can replace **binary semaphore, counting semaphore, event flag**
- **No extra RAM object needed**

## When to use
- **1 task signals another task**
- High performance / ISR signaling

## APIs
```c
BaseType_t xTaskNotify(TaskHandle_t task, uint32_t val, eNotifyAction action);
uint32_t ulTaskNotifyTake(BaseType_t clear, TickType_t timeout);
BaseType_t xTaskNotifyFromISR(TaskHandle_t task, uint32_t val, eNotifyAction action, BaseType_t *hpw);
void vTaskNotifyGiveFromISR(TaskHandle_t task, BaseType_t *hpw);
```

---

# 6. Event Group

## What it is
- A **set of bits (flags)**
- Each bit represents **one event**
- A task can **wait for one or many events at once**

## When to use
- When task must wait for **multiple conditions**
  - Example: WIFI ready + MQTT ready + GPS ready

## APIs
```c
EventGroupHandle_t xEventGroupCreate(void);
EventBits_t xEventGroupSetBits(EventGroupHandle_t eg, EventBits_t bits);
EventBits_t xEventGroupWaitBits(EventGroupHandle_t eg,
                                EventBits_t bits,
                                BaseType_t clear_on_exit,
                                BaseType_t wait_all,
                                TickType_t timeout);
```

---

# 7. Stream Buffers & Message Buffers

## What they are
- **Stream Buffers:** byte-oriented FIFO for streaming data (useful for I/O streams).
- **Message Buffers:** record-oriented API on top of stream buffers for discrete messages (supports message length metadata).

## When to use
- Stream Buffers: continuous byte streams (e.g., serial RX) or variable-length chunks.
- Message Buffers: packetized messages with variable length.

## APIs
```c
// Stream Buffer
StreamBufferHandle_t xStreamBufferCreate(size_t xBufferSizeBytes, size_t xTriggerLevel);
size_t xStreamBufferSend(StreamBufferHandle_t xStreamBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait);
size_t xStreamBufferReceive(StreamBufferHandle_t xStreamBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait);

// Message Buffer
MessageBufferHandle_t xMessageBufferCreate(size_t xBufferSizeBytes);
size_t xMessageBufferSend(MessageBufferHandle_t xMessageBuffer, const void *pvTxData, size_t xDataLengthBytes, TickType_t xTicksToWait);
size_t xMessageBufferReceive(MessageBufferHandle_t xMessageBuffer, void *pvRxData, size_t xBufferLengthBytes, TickType_t xTicksToWait);
```

---

# 8. Software Timers

## What it is
- Timers provide deferred execution via the timer service task. Useful for periodic or one-shot callbacks executed in task context.

## When to use
- Periodic tasks, debouncing, timeouts, deferred work that should not run in ISR.

## APIs & Notes
```c
// Create
TimerHandle_t xTimerCreate(const char * const pcName, TickType_t xPeriodInTicks, UBaseType_t uxAutoReload, void * pvTimerID, TimerCallbackFunction_t pxCallbackFunction);
TimerHandle_t xTimerCreateStatic(const char * const pcName, TickType_t xPeriodInTicks, UBaseType_t uxAutoReload, void * pvTimerID, TimerCallbackFunction_t pxCallbackFunction, StaticTimer_t * pxTimerBuffer);

// Control
BaseType_t xTimerStart(TimerHandle_t xTimer, TickType_t xTicksToWait);
BaseType_t xTimerStop(TimerHandle_t xTimer, TickType_t xTicksToWait);
BaseType_t xTimerChangePeriod(TimerHandle_t xTimer, TickType_t xNewPeriod, TickType_t xTicksToWait);
BaseType_t xTimerReset(TimerHandle_t xTimer, TickType_t xTicksToWait);
BaseType_t xTimerDelete(TimerHandle_t xTimer, TickType_t xTicksToWait);

// Callback prototype
void vTimerCallback( TimerHandle_t xTimer );
```

---

# 9. Hooks (Application Callbacks)

## What they are
- Optional user callbacks invoked by the kernel for key events (tick, idle, malloc-fail, stack overflow, etc.). Enable via FreeRTOSConfig.h (e.g., configUSE_IDLE_HOOK).

## Common Hooks
- `void vApplicationIdleHook(void);`        // when idle task runs
- `void vApplicationTickHook(void);`        // at each tick (keep short)
- `void vApplicationMallocFailedHook(void);`// called on pvPortMalloc failure
- `void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);` // stack overflow

## Notes
- Keep hooks short and ISR-safe as appropriate. Use trace macros or set configASSERT to catch issues.

---

# 10. Mailbox patterns (Queue as mailbox)

## What it is
- A mailbox is commonly implemented as a single-slot queue (or message buffer) to hold the latest message for a consumer.

## When to use
- When only the most recent message matters (e.g., setpoint updates), and producers can overwrite old values.

## APIs / Patterns
```c
// Single-slot queue mailbox
QueueHandle_t xMailbox = xQueueCreate(1, sizeof(MyMsg_t));
// Producer
xQueueOverwrite(xMailbox, &newMsg); // fast overwrite single slot
// Consumer
MyMsg_t msg;
if(xQueueReceive(xMailbox, &msg, portMAX_DELAY) == pdTRUE) { /* handle */ }

// Alternatively use message buffers for variable-length mailbox messages
xMessageBufferSend(msgbuf, &data, len, 0);
```

---

# 11. Recursive mutex

## What it is
- Mutex that the same task can take multiple times without deadlock. Useful for reentrant access within same task.

## APIs
```c
SemaphoreHandle_t xSemaphoreCreateRecursiveMutex(void);
BaseType_t xSemaphoreTakeRecursive(SemaphoreHandle_t xMutex, TickType_t xTicksToWait);
BaseType_t xSemaphoreGiveRecursive(SemaphoreHandle_t xMutex);
```

---

# 12. Useful Misc APIs (quick reference)

```c
// Tasks and scheduler
BaseType_t xTaskCreate(TaskFunction_t pxTaskCode, const char * const pcName, uint16_t usStackDepth, void *pvParameters, UBaseType_t uxPriority, TaskHandle_t *pxCreatedTask);
void vTaskDelay(const TickType_t xTicksToDelay);
void vTaskDelayUntil(TickType_t *pxPreviousWakeTime, TickType_t xTimeIncrement);

// Task inspection
void vTaskList(char * pcWriteBuffer);
UBaseType_t uxTaskGetStackHighWaterMark(TaskHandle_t xTask);

// Heap
size_t xPortGetFreeHeapSize(void);

// Notifications
BaseType_t xTaskNotify(TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction);
uint32_t ulTaskNotifyTake(BaseType_t xClearCountOnExit, TickType_t xTicksToWait);

// ISR-safe variants
BaseType_t xQueueSendFromISR(QueueHandle_t xQueue, const void *pvItemToQueue, BaseType_t *pxHigherPriorityTaskWoken);
BaseType_t xTaskNotifyFromISR(TaskHandle_t xTaskToNotify, uint32_t ulValue, eNotifyAction eAction, BaseType_t *pxHigherPriorityTaskWoken);
```

---

*Notes: For safety-critical systems favor static allocation (xTaskCreateStatic, xTimerCreateStatic, static queues) and enable configASSERT and stack checking.*
