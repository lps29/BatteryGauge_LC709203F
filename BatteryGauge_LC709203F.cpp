#include "BatteryGauge_LC709203F.hpp"


/*
 * does a crc check and returns the checksum
 */
uint8_t BatteryGauge_LC709203F::get_crc(uint8_t *rec_values, uint8_t len)
{
    uint8_t crc = 0x00;
    uint8_t current_byte;
    uint8_t bit;

    for (current_byte = 0; current_byte < len; current_byte++) {
        crc ^= (rec_values[current_byte]);
        for (bit = 8; bit > 0; bit--) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ LC709203F_CRC_POLYNOMIAL;
            }
            else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}


int16_t BatteryGauge_LC709203F::lc709203f_get_voltage()
{
    uint8_t  rec_buf[3];
    
    // Read voltage value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CELL_VOLTAGE);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // Voltage MSB
    rec_buf[1] = I2C_READ();  // Voltage LSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_CELL_VOLTAGE, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_rsoc()
{
    uint8_t rec_buf[3];

    // Read RSOC value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_RSOC);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_RSOC, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_cell_temp()
{
    uint8_t rec_buf[3];
    
    // Read Cell Temperature value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CELL_TEMP);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_CELL_TEMP, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return ((((unsigned int)rec_buf[1] << 8) | rec_buf[0]) - 2731.5);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_status_bit()
{
    uint8_t rec_buf[3];
 
    // Read Status bit value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_STATUS );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_STATUS, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

int16_t BatteryGauge_LC709203F::lc709203f_get_ite()
{
    uint8_t rec_buf[3];
    
    // Read ITE bit value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ITE );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    
    uint8_t crc_buf[5] = {LC709203F_ADDR << 1, LC709203F_REG_ITE, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

int16_t BatteryGauge_LC709203F::lc709203f_get_power_mode()
{
    uint8_t rec_buf[3];
    
    // Read power mode value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_POWER_MODE );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_POWER_MODE, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_alarm_low_voltage()
{
    uint8_t rec_buf[3];
    
    // Read alarm voltage value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ALARM_VOLTAGE );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_ALARM_VOLTAGE, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_alarm_low_rsoc()
{
    uint8_t rec_buf[3];
    
    // Read alarm RSOC value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ALARM_RSOC );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_ALARM_RSOC, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_change_of_parameter()
{
    uint8_t rec_buf[3];
    
    // Read change of parameter (battery profile) value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CHANGE_PARAMETER );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_CHANGE_PARAMETER, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_apt()
{
    uint8_t rec_buf[3];
    
    // Read APT (Adjustment Pack Thermistor) value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_APT );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_APT, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

int16_t BatteryGauge_LC709203F::lc709203f_get_apa()
{
    uint8_t rec_buf[3];
    
    // Read APA (Adjustment Pack Application) value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_APA );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_APA, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

int16_t BatteryGauge_LC709203F::lc709203f_get_current_direction()
{
    uint8_t rec_buf[3];
    
    // Read current direction mode value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CURRENT_DIRECTION );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_CURRENT_DIRECTION, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

int16_t BatteryGauge_LC709203F::lc709203f_get_thermistor_b()
{
    uint8_t rec_buf[3];
    
    // Read current direction mode value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_THERMISTOR );  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8 
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_THERMISTOR, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}


int16_t BatteryGauge_LC709203F::lc709203f_get_id()
{
    uint8_t rec_buf[3];
    
    // Read RSOC value
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ID);  // set register pointer
    Wire.endTransmission(false);

    Wire.requestFrom(LC709203F_ADDR, 3);
    rec_buf[0] = I2C_READ();  // LSB
    rec_buf[1] = I2C_READ();  // MSB
    rec_buf[2] = I2C_READ();  // CRC-8
    
    uint8_t crc_buf[5] = { LC709203F_ADDR << 1, LC709203F_REG_ID, ((LC709203F_ADDR << 1) | 0x01), rec_buf[0], rec_buf[1] };
    if (get_crc(crc_buf, 5) != rec_buf[2]) {
        //DEBUG("CRC Error \n");
        return -1;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
}

void BatteryGauge_LC709203F::lc709203f_set_rsoc_before()
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_BEFORE_RSOC, 0x55, 0xAA };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_BEFORE_RSOC );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_thermistor_b(const unsigned int value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_THERMISTOR, (uint8_t)value, (uint8_t)(value >> 8) };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };

    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_THERMISTOR );  // set register pointer
    //I2C_WRITE(send_buf,3);
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_rsoc_initial()
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_INITIAL_RSOC, 0x55, 0xAA };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_INITIAL_RSOC );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

int8_t BatteryGauge_LC709203F::lc709203f_set_cell_temp(const unsigned int value)
{
    if (!(value >= 0x9e4 && value <= 0xD04)) {
        //DEBUG("gauge_set_cell_temp(): temp outside of range \n");
        return LC709203F_CELL_TEMP_INVALID;
    }
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_CELL_TEMP, (uint8_t)value, (uint8_t)(value >> 8) };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CELL_TEMP );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_current_direction(const lc709203f_current_direction_t direction)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_CURRENT_DIRECTION, (uint8_t)direction, (uint8_t)(direction >> 8) };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };

    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CURRENT_DIRECTION );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_apa(uint8_t value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_APA, (uint8_t)value, 0 };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };

    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_APA );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_apt(const unsigned int value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_APT, (uint8_t)value, (uint8_t)(value >> 8) };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_APT );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_change_of_parameter(const lc709203f_battery_profile_t value)
{
    uint8_t crc_buf[4] = {LC709203F_ADDR << 1, LC709203F_REG_CHANGE_PARAMETER, (uint8_t)value, 0 };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_CHANGE_PARAMETER );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_alarm_low_rsoc(const uint8_t value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_ALARM_RSOC, (uint8_t)value, 0 };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ALARM_RSOC );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_alarm_low_cell_voltage(const unsigned int value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_ALARM_VOLTAGE, (uint8_t)(value), (uint8_t)(value >> 8) };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_ALARM_VOLTAGE );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}

void BatteryGauge_LC709203F::lc709203f_set_power_mode(const lc709203f_power_mode_t value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_POWER_MODE, (uint8_t) value, 0 };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };
    
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_POWER_MODE );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();    
}

void BatteryGauge_LC709203F::lc709203f_set_status_bit(const lc709203f_temp_obtaining_mode_t value)
{
    uint8_t crc_buf[4] = { LC709203F_ADDR << 1, LC709203F_REG_STATUS, (uint8_t)value, 0 };
    uint8_t send_buf[3] = { crc_buf[2], crc_buf[3], get_crc(crc_buf, 4) };

    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE( (uint8_t)LC709203F_REG_STATUS );  // set register pointer
    I2C_WRITE(send_buf[0]);
    I2C_WRITE(send_buf[1]);
    I2C_WRITE(send_buf[2]);
    Wire.endTransmission();
}



void BatteryGauge_LC709203F::set_register(unsigned char reg_addr, unsigned char reg_value)
{
    Wire.beginTransmission(LC709203F_ADDR);
    I2C_WRITE(reg_addr);                               // set register pointer
    I2C_WRITE(reg_value);
    Wire.endTransmission();
}

unsigned char BatteryGauge_LC709203F::get_register(unsigned char reg_addr)
{
   unsigned char buf;
   Wire.beginTransmission(LC709203F_ADDR);
   I2C_WRITE( (uint8_t)reg_addr );                    // set register pointer
   Wire.endTransmission();
   Wire.requestFrom(LC709203F_ADDR, 1);               // request one byte from LTC294x
   while( Wire.available() == 0 );
   return I2C_READ();
}

BatteryGauge_LC709203F::BatteryGauge_LC709203F()
{
}
