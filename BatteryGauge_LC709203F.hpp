#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#include <Wire.h>
// LC709203F I2C HAL
#define I2C_READ  Wire.read  
#define I2C_WRITE Wire.write
#endif

// LC709203F address
#define LC709203F_ADDR 0x0B

// Current direction modes
typedef enum {
    AUTO_MODE       = 0x0,
    CHARGE_MODE     = 0x1,
    DISCHARGE_MODE  = 0xffff
} lc709203f_current_direction_t;

// Battery Profile Options
typedef enum {
    BAT_PROFILE_1   = 0,
    BAT_PROFILE_2   = 1
} lc709203f_battery_profile_t;

// Power mode choices
typedef enum {
    OPERATIONAL_MODE    = 1,
    SLEEP_MODE          = 2
} lc709203f_power_mode_t;

// Temperature obtaining mode options
typedef enum {
    I2C_MODE        = 0,
    THERMISTOR_MODE = 1
} lc709203f_temp_obtaining_mode_t;


// LC709203F register definitions
#define LC709203F_REG_CELL_VOLTAGE      0x09        /**< Register Cell Voltage */
#define LC709203F_REG_RSOC              0x0d        /**< Register RSOC (Relative State of Charge) */
#define LC709203F_REG_ITE               0x0f        /**< Register ITE (Indicator To Empty) */
#define LC709203F_REG_ID                0x11        /**< Register IC Version */
#define LC709203F_REG_CELL_TEMP         0x08        /**< Register Cell Temperature */
#define LC709203F_REG_STATUS            0x16        /**< Register Status Bit */
#define LC709203F_REG_POWER_MODE        0x15        /**< Register IC Power Mode */
#define LC709203F_REG_ALARM_VOLTAGE     0x14        /**< Register Alarm Low Cell Voltage */
#define LC709203F_REG_ALARM_RSOC        0x13        /**< Register Alarm Low RSOC */
#define LC709203F_REG_CHANGE_PARAMETER  0x12        /**< Register Change of the parameter */
#define LC709203F_REG_APT               0x0c        /**< Register APT (Adjustment Pack Thermistor) */
#define LC709203F_REG_APA               0x0b        /**< Register APA (Adjustment Pack Application) */
#define LC709203F_REG_CURRENT_DIRECTION 0x0a        /**< Register Current Direction */
#define LC709203F_REG_THERMISTOR        0x06        /**< Register Thermistor B */
#define LC709203F_REG_BEFORE_RSOC       0x04        /**< Register Before RSOC */
#define LC709203F_REG_INITIAL_RSOC      0x07        /**< Register Initial RSOC */ 

#define LC709203F_CRC_POLYNOMIAL        0x07        /**< CRC Polynomial */

class BatteryGauge_LC709203F
{
public:
    BatteryGauge_LC709203F();
    
    void lc709203f_set_thermistor_b(const unsigned int b_value);
    int16_t lc709203f_get_voltage();
    int16_t lc709203f_get_rsoc();
    int16_t lc709203f_get_cell_temp();
    lc709203f_temp_obtaining_mode_t lc709203f_get_status_bit();
    int16_t lc709203f_get_id();

    uint8_t get_crc(uint8_t *rec_values, uint8_t len);
    byte get_register(byte reg_addr);
    void set_register(unsigned char reg_addr, unsigned char reg_value);  
};
