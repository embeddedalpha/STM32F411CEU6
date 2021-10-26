# Console Driver


#### The driver is used to print and read data on and from a serial monitor (SM) via a UART port. Available UART ports for STM32F411CEUx are USART1, USART2 & USART 6. 
#### The user can choose any of these port for SM and use the other 2 for general application.


#### Functions available for users are:

```C
  void Console_Init(USART_TypeDef *port,int baudrate);
  void printConsole(USART_TypeDef *port,char *msg, ...);
  int scanConsole(char *msg,...);
  char * Console_Return(char *s);

```
