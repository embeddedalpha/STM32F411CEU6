# I2C Bare Metal Driver

### To better understand the code, read the [Medium](https://kunalsalvi63.medium.com/bare-metal-i2c-driver-for-stm32f411cex-3cc600fdcc05) article I wrote! ✨

### Functions:

```c
void I2C_Master_Init(I2C_Config I2C);
void I2C_Master_Start(I2C_Config I2C);
void I2C_Master_Address(I2C_Config I2C, uint8_t address, uint8_t read_write);
void I2C_Master_Send_Byte(I2C_Config I2C, uint8_t data);
void I2C_Master_Send_Buffer(I2C_Config I2C, uint8_t *data, int length);
void I2C_Master_Write_Register(I2C_Config I2C, uint8_t device_address, uint8_t reg_address, uint8_t data);
int I2C_Master_Receive_Byte(I2C_Config I2C);
void I2C_Master_NACK(I2C_Config I2C);
void I2C_Master_ACK(I2C_Config I2C);
void I2C_Master_Stop(I2C_Config I2C);
```

### Add the below function to the driver initialization to setup the clocks
```C
MCU_Clock_Setup();
```

### Declare a struct of type I2C_Config.
```c
struct I2C_Config X;
X.I2C = I2C1 (or I2C2, I2C3);
x.mode = I2C_Fast_Mode (or I2C_Normal_Mode)
```

### Pass the struct to intialization function.
```
I2C_Master_Init(X);
```

