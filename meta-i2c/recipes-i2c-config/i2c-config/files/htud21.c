#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <stdint.h>

#define I2C_DEV_PATH 	("/dev/i2c-1")

int main()

{

 int fdev = open("/dev/i2c-1", O_RDWR); // open i2c bus

if (fdev < 0) {
    fprintf(stderr, "Failed to open I2C interface %s Error: %s\n", I2C_DEV_PATH, strerror(errno));
    return -1;
}

unsigned char i2c_addr = 0x40;

// set slave device address 0x40
if (ioctl(fdev, I2C_SLAVE, i2c_addr) < 0) {
    fprintf(stderr, "Failed to select I2C slave device! Error: %s\n", strerror(errno));
    return -1;
}

uint8_t buf[1];
buf[0] = 0xE3;

write(fdev, buf, 1);


// device response, 14-bit ADC value:
//  first 8 bit part ACK  second 8 bit part        CRC
// [0 1 2 3 4 5 6 7] [8] [9 10 11 12 13 14 15 16] [17 18 19 20 21 22 23 24]
// bit 15 - measurement type (‘0’: temperature, ‘1’: humidity)
// bit 16 - currently not assigned

uint8_t buf2[3] = { 0 };

read(fdev, buf2, 3);

uint16_t sensor_data = (buf2 [0] << 8 | buf2 [1]) & 0xFFFC;

// temperature
double sensor_tmp = sensor_data / 65536.0;
double result = -46.85 + (175.72 * sensor_tmp);

printf("Temperature: %.2f C\n", result);


// humidity
result = -6.0 + (125.0 * sensor_tmp);

printf("Humidity: %.2f %%\n", result);


}
