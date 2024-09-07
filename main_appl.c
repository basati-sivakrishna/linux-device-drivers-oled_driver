#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>


#include "oled.h"

int  I2C_Write( unsigned char *buf, unsigned int len );

static struct i2c_adapter *i2c_adapter     = NULL;  // I2C Adapter Structure
static struct i2c_client  *i2c_client_oled = NULL;  // I2C Cient Structure (In our case it is OLED)


static const struct i2c_device_id oled_id[] = {
  { SLAVE_DEVICE_NAME, 0 },
  { }
};

MODULE_DEVICE_TABLE(i2c, oled_id);


static int oled_probe(struct i2c_client *client)
{

  SSD1306_DisplayInit();
  
  //Set cursor
  SSD1306_SetCursor(0,0);  

  //Write String to OLED
  SSD1306_String("Welcome\nTo\nIISC\n\n");
  
  pr_info("OLED Probed!!!\n");
  
  return 0;
}


static void oled_remove(struct i2c_client *client)
{

  SSD1306_String("ThanK YoU!!!");

  msleep(1000);

  //Set cursor
  SSD1306_SetCursor(0,0);
  //clear the display
  SSD1306_Fill(0x00);

  SSD1306_Write(true, 0xAE); // Entire Display OFF

  pr_info("OLED Removed!!!\n");

}


static struct i2c_driver oled_driver = {
  .driver = {
    .name   = SLAVE_DEVICE_NAME,
    .owner  = THIS_MODULE,
  },
  .probe          = oled_probe,
  .remove         = oled_remove,
  .id_table       = oled_id,
};

/*
** I2C Board Info strucutre
*/
static struct i2c_board_info oled_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, SSD1306_SLAVE_ADDR)
};



int I2C_Write(unsigned char *buf, unsigned int len)
{

  int ret_val = i2c_master_send(i2c_client_oled, buf, len);

  return ret_val;
}



static int __init oled_driver_init(void)
{
  int ret = -1;
  i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);

  if( i2c_adapter != NULL )
  {
    i2c_client_oled = i2c_new_client_device(i2c_adapter, &oled_i2c_board_info);

    if( i2c_client_oled != NULL )
    {
      i2c_add_driver(&oled_driver);
      ret = 0;
    }

      i2c_put_adapter(i2c_adapter);
  }

  pr_info("Driver Added!!!\n");

  SSD1306_SetCursor(0,0);
  SSD1306_InvertDisplay(true);
  SSD1306_Fill(0x00);  
  SSD1306_PrintLogo();
  msleep(10000);
  


  return ret;
}

/*
** Module Exit function
*/
static void __exit oled_driver_exit(void)
{
  i2c_unregister_device(i2c_client_oled);
  i2c_del_driver(&oled_driver);
  pr_info("Driver Removed!!!\n");
}

module_init(oled_driver_init);
module_exit(oled_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Basati Sivakrishna");
MODULE_DESCRIPTION("OLED Driver");
