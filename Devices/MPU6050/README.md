## MPU6050 Driver

##### Functions

``` c
void MPU6050_I2C_Init(I2C_TypeDef *I2C);
void MPU6050_I2C_Write_Single(uint8_t reg, uint8_t data);
void MPU6050_I2C_Write_Burst(uint8_t reg, uint8_t *data, int len);
char MPU6050_Register_Read(uint8_t reg_address);
void MPU6050_I2C_Read_Burst(uint8_t reg, uint8_t *data, int len);
void MPU6050_I2C_Get_Raw_Data(uint16_t *accl_x, uint16_t *accl_y, uint16_t *accl_z, uint16_t *gyro_x, uint16_t *gyro_y, uint16_t *gyro_z);
void MPU6050_I2C_Get_Filtered_Data(uint16_t *accl_x,  uint16_t *accl_y, uint16_t *accl_z, uint16_t *gyro_x, uint16_t *gyro_y, uint16_t *gyro_z);
```

##### Setup
```c
MPU6050_I2C_Init(I2C1);
```

##### Get Data
```C
uint16_t accl_x;
uint16_t accl_y;
uint16_t accl_z;
uint16_t gyro_x;
uint16_t gyro_y;
uint16_t gyro_z;
MPU6050_I2C_Get_Raw_Data(&accl_x, &accl_y, &accl_z, &gyro_x, &gyro_y, &gyro_z);
```
