# DMA (Direct Memory Access)

### STM32F411CE has 2 DMA controllers with 6 streams per controller and 7 channels ber stream.

### Note: No two channels on same stream can be used at the same time.

### Functions available for users

``` C
void DMA_Init(DMA_Config DMA);
void DMA_Interrupt(DMA_Config DMA);
void DMA_Enable(DMA_Config DMA);
```

### Each function requries a struct to be passed with user settings. The members of the structure are:
```C
typedef struct DMA_Config
{
	DMA_Stream_TypeDef *DMA_Stream;
	uint8_t channel;
	uint32_t *source_address;
	uint32_t *destination_address;
	uint8_t priority_level;
	uint8_t memory_size;
	uint8_t peripheral_size;
	uint8_t circular_mode;
	uint8_t direction;
	uint8_t packet_length;
	uint8_t interrupt_priority;
	uint8_t transfer_complete_interrupt;
	uint8_t half_transfer_interrupt;
	uint8_t transfer_error_interrupt;
	uint8_t direct_mode_error_interrupt;
}DMA_Config;
```

### To help the user insert right values in the members of the structure, the following constants are declared.
```C
#define DMA_Peripheral_To_Memory 0
#define DMA_Memory_To_Peripheral 1
#define DMA_Memory_To_Memory     2

#define Enable 1
#define Disable 0

#define DMA_Priority_Low           0
#define DMA_Priority_Medium        1
#define DMA_Priority_High          2
#define DMA_Priority_Very_High     3

#define DMA_memory_size_8	0
#define DMA_memory_size_16	1
#define DMA_memory_size_32	2

#define DMA_peripheral_size_8	0
#define DMA_peripheral_size_16	1
#define DMA_peripheral_size_32	2
```

### Example of structure is shown below:
```C
DMA_Config DMA_I2S1;
```

### Simplified Example:
```C
int data1,data2;

DMA_Config DMA;

DMA.DMA_Stream = DMA2_Stream2;
DMA.channel = 3;
DMA.circular_mode = Enable;
DMA.destination_address = &data1;
DMA.source_address = &data2;
DMA.direction = DMA_Memory_To_Memory;
DMA.memory_size = DMA_memory_size_8;
DMA.peripheral_size = DMA_peripheral_size_8;
DMA.packet_length = 100;
DMA_Init(DMA);
```
