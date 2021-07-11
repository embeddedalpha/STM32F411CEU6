# I2C Bare Metal Driver

### Functions:
```
int I2C_Master_Init(I2C_Config I2C);
void I2C_Master_Start(I2C_Config I2C);
void I2C_Master_Send_Address(I2C_Config I2C, char address);
void I2C_Master_Send_Data(I2C_Config I2C, char data);
char I2C_Master_Receive_Data(I2C_Config I2C);
void I2C_Master_Stop(I2C_Config I2C);
void I2C_Master_Send_NACK(I2C_Config I2C);
```

### Add the below function to the driver initialization to setup the clocks
```
MCU_Clock_Setup();
```

### Declare a struct of type I2C_Config.
```
struct I2C_Config X;
X.I2C = I2C1 (or I2C2, I2C3);
x.mode = Fast_Mode (or Normal Mode)
```

### Pass the struct to intialization function.
```
I2C_Master_Init(X);
```

