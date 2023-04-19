/* This code was based off of C code from ControlEverything.com */

// LSM9DS0
// This code is designed to work with the LSM9DS0_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM9DS0_I2CS#tabs-0-product_tabset-2
// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "accel.h"

Accelerometer::Accelerometer()
{
    x_val = 0;
    file = -1;
    //y_val = 0;
    //z_val = 0;
}

int Accelerometer::accel_init()
{
    char config[2] = {0};
    // Create I2C bus
    const char *bus = "/dev/i2c-2";
    if((this->file = open(bus, O_RDWR)) < 0)
    {
        printf("Failed to open the bus. \n");
        return 1;
    }
    else printf("Opened bus \n");
    // Get I2C device, LSM9DSO Accelero Magneto I2C address is 0x1D(29)
    ioctl(this->file, I2C_SLAVE, 0x1D);

    // Select control register1(0x20)
    // X, Y and Z Axis enable, power on mode, data rate o/p 100 Hz(0x67)
    config[0] = 0x20;
    config[1] = 0x67;
    write(this->file, config, 2);

    // Select control register2(0x21)
    // Full scale selection, +/- 16g(0x20)
    config[0] = 0x21;
    config[1] = 0x20;
    write(this->file, config, 2);

    // Select control register5(0x24)
    // Magnetic high resolution, o/p data rate 50 Hz(0x70)
    config[0] = 0x24;
    config[1] = 0x70;
    write(this->file, config, 2);

    // Select control register6(0x25)
    // Magnetic full scale selection, +/- 12 gauss(0x60)
    config[0] = 0x25;
    config[1] = 0x60;
    write(this->file, config, 2);

    // Select control register7(0x26)
    // Normal mode, magnetic continuous conversion mode(0x00)
    config[0] = 0x26;
    config[1] = 0x00;
    write(this->file, config, 2);
    return 0;
}

int Accelerometer::get_x()
{
    if (this->file == -1) {
        printf("Accelerometer not initialized.\n");
        return -1;
    }
    else printf("Initialized accelerometer\n");
    // Read xGyro lsb data from register(0x28)
    char reg[1] = {0x28};
    write(this->file, reg, 1);
    char data[1] = {0};
    if(read(this->file, data, 1) != 1)
    {
        return -1;
    }
    char data_0 = data[0];
    // Read xGyro msb data from register(0x29)
    reg[0] = 0x29;
    write(this->file, reg, 1);
    read(this->file, data, 1);
    char data_1 = data[0];
    // Convert the data
    int xAccl = (data_1 * 256 + data_0);
    if(xAccl > 32767)
    {
        xAccl -= 65536;
    }

    return xAccl;
}

void Accelerometer::stop() {
    close(this->file);
    this->file = -1;
}

Accelerometer::~Accelerometer()
{}

