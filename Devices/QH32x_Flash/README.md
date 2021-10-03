# XM25QH32B
### SERIAL NOR FLASH WITH DUAL AND QUAD SPI&QPI

#### [Datasheet](https://datasheet.lcsc.com/lcsc/1811072025_XMC-XM25QH32BHIG_C328460.pdf)

![image](https://user-images.githubusercontent.com/38166489/135762626-63380dc0-3746-4f8d-a67c-26132dd45fa6.png)

#### Functions avaliable in the driver to the user
```C
bool QH32x_Init(SPI_TypeDef *SPI);
void QH32x_Reset();
void QH32x_Flash_Write_Enable();
void QH32x_Write_Flash(uint32_t addr, uint8_t data);
void QH32x_Write_Flash_Buffer(uint32_t addr, int len, uint8_t *data);
void QH32x_Read_Flash(uint32_t addr);
void QH32x_Read_Flash_Buffer(uint32_t addr, int len, uint8_t *data);
void QH32x_Test();
```
