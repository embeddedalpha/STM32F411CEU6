# I2S Baremetal Driver

### I2S hardware block can be configured by passing appropriate values in I2S_Config struct.
```C
I2S_Config INMP441;

INMP441.I2S = I2S1;
INMP441.audio_frequency = 48000;
INMP441.channel_length = Channel_32bit;
INMP441.data_length = Frame_24bit;
INMP441.mode = I2S_Master_RX;
INMP441.standard = Philips_Standard;
```

### Pass the struct into I2S_Master_Init() to enable the peripheral
```C
I2S_Master_Init(INMP441);
```

### To read the left channel of the bus, call I2S_Master_Receive_Left_Channel()
```C
int32_t data = I2S_Master_Receive_Left_Channel(INMP441);
```

### To read the right channel of the bus, call I2S_Master_Receive_Right_Channel()
```C
int32_t data = I2S_Master_Receive_Right_Channel(INMP441);
```

### Examples
#### [I2S_Mono](https://github.com/embeddedalpha/STM32F411CEU6/blob/main/I2S/Example/I2S_Mono.c)  

