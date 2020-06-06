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


void BatteryGauge_LC709203F::lc709203f_set_thermistor_b(const unsigned int b_value)
{
    //set_register( LC709203F_REG_THERMISTOR, b_value );
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
        return 0;
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
        return 0;
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
        return 0;
    }
    return ((((unsigned int)rec_buf[1] << 8) | rec_buf[0]) - 2731.5);
}


lc709203f_temp_obtaining_mode_t BatteryGauge_LC709203F::lc709203f_get_status_bit()
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
        return 0;
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
        return 0;
    }
    return (((unsigned int)rec_buf[1] << 8) | rec_buf[0]);
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
   Wire.endTransmission(false);
   Wire.requestFrom(LC709203F_ADDR, 1);               // request one byte from LTC294x
   while( Wire.available() == 0 );
   return I2C_READ();
}

BatteryGauge_LC709203F::BatteryGauge_LC709203F()
{
}
