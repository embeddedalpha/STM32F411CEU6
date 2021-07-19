## MPU6050 Driver

#### By default, fast mode of I2C is selected with Fs = 400KHz
#### Functions

```C
void MPU6050_I2C_Init(I2C_TypeDef *I2C);
void MPU6050_I2C_Write_Single(uint8_t reg, uint8_t data);
void MPU6050_I2C_Write_Burst(uint8_t reg, uint8_t *data, int len);
char MPU6050_I2C_Read_Single(uint8_t reg_address);
void MPU6050_I2C_Read_Burst(uint8_t reg, uint8_t *data, int len);
void MPU6050_I2C_Get_Raw_Data(uint16_t *accl_x, uint16_t *accl_y, uint16_t *accl_z,
                              uint16_t *gyro_x, uint16_t *gyro_y, uint16_t *gyro_z);
void MPU6050_I2C_Get_Filtered_Data(uint16_t *accl_x, uint16_t *accl_y, uint16_t *accl_z,
                                   uint16_t *gyro_x, uint16_t *gyro_y, uint16_t *gyro_z);
```

#### Setup
```C
MPU6050_I2C_Init(I2C1);
```

#### Send Data
```C
MPU6050_I2C_Write_Single(0xAA, 0xAA);
```

#### Receive Data
```C
char s;
s = MPU6050_I2C_Read_Single(0xAA);
```

#### Get Raw Data
```C
uint16_t accl_x;
uint16_t accl_y;
uint16_t accl_z;
uint16_t gyro_x;
uint16_t gyro_y;
uint16_t gyro_z;

MPU6050_I2C_Get_Raw_Data(&accl_x, &accl_y, &accl_z, &gyro_x, &gyro_y, &gyro_z);
MPU6050_I2C_Get_Filtered_Data(&accl_x, &accl_y, &accl_z, &gyro_x, &gyro_y, &gyro_z);
```
