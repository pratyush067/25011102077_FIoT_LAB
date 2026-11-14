#ifndef BME280_DEFS_H_
#define BME280_DEFS_H_

#include <stdint.h>
#include <stddef.h>

#define BME280_OK                   INT8_C(0)
#define BME280_E_NULL_PTR           INT8_C(-1)
#define BME280_E_DEV_NOT_FOUND      INT8_C(-2)
#define BME280_E_INVALID_LEN        INT8_C(-3)
#define BME280_E_COMM_FAIL          INT8_C(-4)
#define BME280_E_SLEEP_MODE_FAIL    INT8_C(-5)
#define BME280_E_NVM_COPY_FAILED    INT8_C(-6)

#define BME280_I2C_ADDR_PRIM        UINT8_C(0x76)
#define BME280_I2C_ADDR_SEC         UINT8_C(0x77)
#define BME280_CHIP_ID              UINT8_C(0x60)

#define BME280_CHIP_ID_ADDR         UINT8_C(0xD0)
#define BME280_RESET_ADDR           UINT8_C(0xE0)

#define BME280_OVERSAMPLING_1X      UINT8_C(1)
#define BME280_FILTER_COEFF_OFF     UINT8_C(0)
#define BME280_MODE_NORMAL          UINT8_C(0x03)

#define BME280_ALL                  UINT8_C(0x07)
#define BME280_SEL_OSR_PRESS        UINT8_C(0x01)
#define BME280_SEL_OSR_TEMP         UINT8_C(0x02)
#define BME280_SEL_OSR_HUM          UINT8_C(0x04)
#define BME280_SEL_FILTER           UINT8_C(0x10)

enum bme280_intf { BME280_SPI_INTF, BME280_I2C_INTF };

typedef int8_t (*bme280_read_fptr_t)(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
typedef int8_t (*bme280_write_fptr_t)(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
typedef void (*bme280_delay_us_fptr_t)(uint32_t period, void *intf_ptr);

struct bme280_settings {
    uint8_t osr_p;
    uint8_t osr_t;
    uint8_t osr_h;
    uint8_t filter;
    uint8_t standby_time;
};

struct bme280_data {
    float temperature;
    float pressure;
    float humidity;
};

struct bme280_dev {
    uint8_t chip_id;
    void *intf_ptr;
    enum bme280_intf intf;
    bme280_read_fptr_t read;
    bme280_write_fptr_t write;
    bme280_delay_us_fptr_t delay_us;
    struct bme280_settings settings;
};

#endif
