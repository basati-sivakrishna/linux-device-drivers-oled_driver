#define I2C_BUS_AVAILABLE       (          1 )              // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME       (    "OLED"  )              // Device and Driver Name
#define SSD1306_SLAVE_ADDR      (       0x3C )              // SSD1306 OLED Slave Address
#define SSD1306_MAX_SEG         (        128 )              // Maximum segment
#define SSD1306_MAX_LINE        (          7 )              // Maximum line
#define SSD1306_DEF_FONT_SIZE   (          5 )              // Default font size

extern int  I2C_Write( unsigned char *buf, unsigned int len );


void SSD1306_PrintChar( unsigned char c );
void SSD1306_String( unsigned char *str );
void SSD1306_InvertDisplay(bool need_to_invert);
void SSD1306_SetBrightness(uint8_t brightnessValue);
void SSD1306_StartScrollHorizontal( bool is_left_scroll,
                                           uint8_t start_line_no,
                                           uint8_t end_line_no
                                         );
void SSD1306_StartScrollVerticalHorizontal( bool is_vertical_left_scroll,
                                                   uint8_t start_line_no,
                                                   uint8_t end_line_no,
                                                   uint8_t vertical_area,
                                                   uint8_t rows
                                                 );
int  SSD1306_DisplayInit( void );
void SSD1306_Fill( unsigned char data );
void SSD1306_GoToNextLine( void );
void SSD1306_SetCursor( uint8_t lineNo, uint8_t cursorPos );
void SSD1306_Write(bool is_cmd, unsigned char data);
void SSD1306_PrintLogo(void);
