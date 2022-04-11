/*
 * Reference: https://olegkutkov.me/2018/02/21/htu21d-raspberry-pi/    
 * Modified by Abhishek Suryawanshi
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>


#define I2C_DEV_PATH    ("/dev/i2c-1")

int main()
{
 int fdev = open("/dev/i2c-1", O_RDWR); // open i2c bus

  if (fdev < 0) 
  {
    fprintf(stderr, "Failed to open I2C interface %s Error: %s\n", I2C_DEV_PATH, strerror(errno));
    return -1;
  }
  
  unsigned char i2c_addr = 0x40;
// set slave device address 0x40
  if (ioctl(fdev, I2C_SLAVE, i2c_addr) < 0) 
 {
    fprintf(stderr, "Failed to select I2C slave device! Error: %s\n", strerror(errno));
    return -1;
 }
   uint8_t buf[1];
   buf[0] = 0xFE;
   int retval=write(fdev, buf, 1);
   if (retval < 0)
    {
      printf ("\n\rError in writing (Soft reset).");
    }

  //17 ms delay after soft-reset 
  usleep (17000);

   while (1)
   {
     
    //Hold master mode for measuring humidity
      buf[0] = 0xE5;
     retval=write(fdev, buf, 1);
   if (retval < 0)
    {
      printf ("\n\rError in writing (Soft reset).");
    }

  // 2 sec delay before performing read operation
      sleep (2);


// device response, 14-bit ADC value:
//  first 8 bit part ACK  second 8 bit part        CRC
// [0 1 2 3 4 5 6 7] [8] [9 10 11 12 13 14 15 16] [17 18 19 20 21 22 23 24]
// bit 15 - measurement type (‘0’: temperature, ‘1’: humidity)
// bit 16 - currently not assigned

   uint8_t buf2[3] = { 0 };

   retval=read(fdev, buf2, 3);
   if (retval < 0)
    {
      printf ("\n\rError in reading.");
    }
    
    else if (retval == 0)
	{
	  printf ("\n\rNo data to read.");
	}
      else
	{
	  printf ("\n\rData successfully read.");
	}

      usleep (4000);

   //uint16_t sensor_data = (buf2 [0] << 8 | buf2 [1]) & 0xFFFC;
      uint16_t sensor_data = 0;
      sensor_data = buf2[0] << 8;
      sensor_data += buf[1];
      sensor_data &= ~0x003;

     
// temperature
//double sensor_tmp = sensor_data / 65536.0;
//double result = -46.85 + (175.72 * sensor_tmp);
//printf("Temperature: %.2f C\n", result);
// humidity
double result = (-6.0 + 125.0 / 65536 * (double) sensor_data);

      printf ("Humidity: %.2f %%\n", result);
      sleep (1);

  }
}
