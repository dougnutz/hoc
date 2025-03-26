#include <Wire.h>
#include "Ultrasound.h"

Ultrasound::Ultrasound()
{
  Wire.begin();
}


// This function writes a single byte to a specific I2C address.
// Parameters:
// - addr: The I2C address of the device.
// - val: The byte value to write.
// Returns:
// - true if the transmission was successful, false otherwise.
bool Ultrasound::wireWriteByte(uint8_t addr, uint8_t val)
{
    // Begin transmission to the specified I2C address.
    Wire.beginTransmission(addr);
    
    // Write the byte value to the I2C bus.
    Wire.write(val);
    
    // End the transmission and check for success.
    if( Wire.endTransmission() != 0 ) 
    {
        // If the transmission failed, return false.
        return false;
    }
    
    // If the transmission was successful, return true.
    return true;
}


// This function writes an array of bytes to a specific I2C address and register.
// Parameters:
// - addr: The I2C address of the device.
// - reg: The register address to write to.
// - val: Pointer to the array of byte values to write.
// - len: The number of bytes to write.
// Returns:
// - true if the transmission was successful, false otherwise.
bool Ultrasound::wireWriteDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len)
{
    unsigned int i;

    // Begin transmission to the specified I2C address.
    Wire.beginTransmission(addr);

    // Write the register address to the I2C bus.
    Wire.write(reg);

    // Write each byte in the array to the I2C bus.
    for(i = 0; i < len; i++) 
    {
        Wire.write(val[i]);
    }

    // End the transmission and check for success.
    if( Wire.endTransmission() != 0 ) 
    {
        // If the transmission failed, return false.
        return false;
    }

    // If the transmission was successful, return true.
    return true;
}


// This function reads an array of bytes from a specific I2C address and register.
// Parameters:
// - addr: The I2C address of the device.
// - reg: The register address to read from.
// - val: Pointer to the array where the read byte values will be stored.
// - len: The number of bytes to read.
// Returns:
// - The number of bytes successfully read, or -1 if an error occurred.
int Ultrasound::wireReadDataArray(uint8_t addr, uint8_t reg, uint8_t *val, unsigned int len)
{
    unsigned char i = 0;  

    // Indicate which register we want to read from by writing the register address.
    if (!wireWriteByte(addr, reg)) 
    {
        // If writing the register address fails, return -1 to indicate an error.
        return -1;
    }

    // Request the specified number of bytes from the I2C device.
    Wire.requestFrom(addr, len);

    // Read the requested bytes from the I2C bus.
    while (Wire.available()) 
    {
        // If more bytes are available than expected, return -1 to indicate an error.
        if (i >= len) 
        {
            return -1;
        }

        // Store the read byte in the provided array.
        val[i] = Wire.read();
        i++;
    }

    // Return the number of bytes successfully read.
    return i;
}



// This function sets the RGB LEDs to a breathing mode with specified colors.
// Parameters:
// - r1, g1, b1: RGB values for the first LED (0-255).
// - r2, g2, b2: RGB values for the second LED (0-255).
void Ultrasound::Breathing(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
    uint8_t breathing[6]; // Array to hold RGB values for both LEDs.
    uint8_t value = RGB_WORK_BREATHING_MODE; // Set the mode to breathing.

    // Write the breathing mode to the device.
    wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE, &value, 1);

    // Assign RGB values for the first LED.
    breathing[0] = r1;
    breathing[1] = g1;
    breathing[2] = b1;

    // Assign RGB values for the second LED.
    breathing[3] = r2;
    breathing[4] = g2;
    breathing[5] = b2;

    // Send the RGB values to the device for breathing mode.
    wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R_BREATHING_CYCLE, breathing, 6);
}


// This function sets the RGB LEDs to a static color mode with specified colors.
// Parameters:
// - r1, g1, b1: RGB values for the first LED (0-255).
// - r2, g2, b2: RGB values for the second LED (0-255).
void Ultrasound::Color(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t r2, uint8_t g2, uint8_t b2)
{
    uint8_t RGB[6]; // Array to hold RGB values for both LEDs.
    uint8_t value = RGB_WORK_SIMPLE_MODE; // Set the mode to static color.

    // Write the static color mode to the device.
    wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB_WORK_MODE, &value, 1);

    // Assign RGB values for the first LED.
    RGB[0] = r1;
    RGB[1] = g1;
    RGB[2] = b1;

    // Assign RGB values for the second LED.
    RGB[3] = r2;
    RGB[4] = g2;
    RGB[5] = b2;

    // Send the RGB values to the device for static color mode.
    wireWriteDataArray(ULTRASOUND_I2C_ADDR, RGB1_R, RGB, 6);
}


// This function retrieves the distance measured by the ultrasonic sensor.
// Returns:
// - The distance value as a 16-bit unsigned integer in mm.
u16 Ultrasound::GetDistance()
{
    u16 distance; // Variable to store the distance value.

    // Read 2 bytes of data from the ultrasonic sensor starting at register 0.
    wireReadDataArray(ULTRASOUND_I2C_ADDR, 0, (uint8_t *)&distance, 2);

    // Return the distance value.
    return distance;
}
