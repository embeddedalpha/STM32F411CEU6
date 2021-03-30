# SPI Driver v1.1

### SPI driver for STM32F411CEU6


#### Structures are provided to facilitate seemless and easy hardware configuration. SPI has 5 master and a slave modes from SPI1 to SPI5. 

```
typedef struct SPI_Config;
```

#### Description of members of the SPI_Master_Config structure:
```
SPI_TypeDef *SPI;           //Hardware SPI you wish to use : SPI1 or SPI2
uint8_t mode;               //SPI mode: Bidirectional by passing '1' or Unidirectional by passing '0'. 
                            //In Bidirectional, onlyTX by passing '1' or onlyRX by passing '0' can be selected.
bool onlyTX;
bool onlyRX;
bool frame_format;          //Frame format can be set to 8-bit by passing '0' or to 16-bit by passing '1'
uint8_t clock_speed;        //Clock Speeds are defined in the SPI.h file. Any of those values can be passed.
uint8_t lsb_or_msb;         //Pass '1' for LSB to be transmitted first or '0' for MSB to be transmitted first
bool crc;                   //This enables Hardware SPI CRC. Passing '1' sets Hardware CRC.
bool interrupts;            //Passing '1' enables interrupts
bool tx_int;                //Enable Tx buffer empty interrupt
bool err_int;               //Enable Error interrupt. Helps in error detection when CRC, Mode fault, overrun and 
                            //underrun occurs
bool rx_int;                //Enable RX buffer not empty interrupt
bool clock_phase;           //Pass '1' or '0' according to the application
bool clock_polarity;        //Pass '1' or '0' according to the application
bool txDMA;                 //Enable transmit buffer DMA by passing '1'
bool rxDMA;                 //Enable receiver buffer DMA by passing '1'
```

#### Initiate the structure 
 ```
 struct SPI_Config SPI_Master_Test;
 ```

#### Pass the structure in the SPI_Master_Init function

```
void SPI_Master_Init(SPI_Master_Test);
```

#### Transmit data by using the SPI_Master_TX function

```
SPI_Master_TX(SPI_Master_Test, 0x45);
```

#### Receive data by using the SPI_Master_RX function

```
uint16_t var1 = SPI_Master_RX(SPI_Master_Test);
```

#### To initialize SPI in slave mode, initiate the structure like that in the master mode.

```
struct SPI_Config SPI_Slave_Test;
 SPI_Slave_Init(SPI_Slave_Test);
 
```

#### To send and receive data :

```
SPI_Slaver_TX(SPI_Slave_Test, 0x45);
uint16_t var1 = SPI_Slave_RX(SPI_Slave_Test);

```

#### NSS / CSS pins are GPIOA_4 and GPIOB_12 for SPI1 & SPI2.

```
SPI1_CSS_HIGH();
SPI1_CSS_LOW();
SPI2_CSS_HIGH();
SPI2_CSS_LOW();
SPI3_CSS_HIGH();
SPI3_CSS_LOW();
SPI4_CSS_HIGH();
SPI5_CSS_LOW();
SPI5_CSS_HIGH();
SPI5_CSS_LOW();
```

##### Disable the peripheral by calling SPI_Disable()

```
void SPI_Disable(SPI_Config SPI);
```

#### Interrupts can be implemented by adding the following lines of code. This snippet is commented at the end of SPI.c 
#### and be used in application's main.c file.

```
void SPI1_IRQHandler(void)
{
	if(SPI1->SR & SPI_SR_TXE)
	{
		//Your code goes here
	}

	if(SPI1->SR & SPI_SR_RXNE)
	{
		//Your code goes here
	}

	if(SPI1->SR & SPI_SR_OVR)
	{
		//Your code goes here
	}

	if(SPI1->SR & SPI_SR_MODF)
	{
		//Your code goes here
	}

	if(SPI1->SR & SPI_SR_CRCERR)
	{
		//Your code goes here
	}

	if(SPI1->SR & SPI_SR_UDR)
	{
		//Your code goes here
	}

}

	NVIC_EnableIRQ(SPI1_IRQn);
```

