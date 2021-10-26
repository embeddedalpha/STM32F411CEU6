## US100 Ultrasonic Sensor

![image](https://user-images.githubusercontent.com/38166489/135722878-838effc1-8d68-4ad7-96e1-74f571c5c614.png)


#### Functions available for users:

```C
void US100_UART_Init(USART_TypeDef *USART);
uint8_t US100_UART_Read_Temp(USART_TypeDef *USART);
float US100_UART_Get_Distance_mm(USART_TypeDef *USART);
float US100_UART_Get_Distance_cm(USART_TypeDef *USART);
```

