#  WS2812B Addressable LEDs

### Intelligent control LED Integrated Light Source

### [Datasheet](https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf)

### Functions available to the user:

```C
void WS2811_Init(SPI_Typedef *WS2811);
void WS2811_Set_Color(int led_number, int red, int blue, int green);
void WS2811_Send(int led_no, int red, int blue, int green);
```

### For initialization, the user calls WS2811_Init and passes the instance of SPI instance, i.e, SPI1, SPI2, etc...
```C
void WS2811_Init(SPI);
```

### The number of leds can be set by 
