#include "main.h"
#include "bme280.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
struct bme280_dev dev;
struct bme280_data comp_data;
int8_t rslt = BME280_OK;

float temperature, pressure, humidity;

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, 
                         reg_data, len, HAL_MAX_DELAY) == HAL_OK) {
        return BME280_OK;
    }
    return BME280_E_COMM_FAIL;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t*)intf_ptr;
    if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, 
                          (uint8_t*)reg_data, len, HAL_MAX_DELAY) == HAL_OK) {
        return BME280_OK;
    }
    return BME280_E_COMM_FAIL;
}

void user_delay_us(uint32_t period, void *intf_ptr) {
    HAL_Delay((period / 1000) + 1);
}

void bme280_setup(void) {
    static uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    rslt = bme280_init(&dev);

    dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    dev.settings.osr_p = BME280_OVERSAMPLING_1X;
    dev.settings.osr_t = BME280_OVERSAMPLING_1X;
    dev.settings.filter = BME280_FILTER_COEFF_OFF;

    rslt = bme280_set_sensor_settings(BME280_SEL_OSR_PRESS | BME280_SEL_OSR_TEMP | 
                                      BME280_SEL_OSR_HUM | BME280_SEL_FILTER, &dev);
    rslt = bme280_set_sensor_mode(BME280_MODE_NORMAL, &dev);
}
