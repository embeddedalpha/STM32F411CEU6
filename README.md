# STM32F411x  ![visitors](https://visitor-badge.glitch.me/badge?page_id=embeddedalpha.stm32f411ceu6)

### [Reference Manual](https://github.com/embeddedalpha/STM32F411x/files/5899226/dm00119316-stm32f411xc-e-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) | [Datasheet](https://www.st.com/resource/en/datasheet/stm32f411re.pdf)

![image](https://user-images.githubusercontent.com/38166489/106320631-2712e480-6299-11eb-9f9f-81f4b142b13a.png)

### To enable serial console:

```
Console_Init(9600); //PA9 -> TX and PA10 -> RX
printConsole("Print what you want \n\r" );
```
