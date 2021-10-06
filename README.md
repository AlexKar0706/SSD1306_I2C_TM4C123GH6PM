# SSD1306_I2C_TM4C123GH6PM
In this program, a driver is written for the SSD1306 128x64 OLED display with I2C protocol.
Also in the program was written a code for using the I2C module in the TM4C123HG6PM microcontroller.
Currently, the driver can print text and draw pixels to the SSD1306 displays.
Full datasheet for SSD1306 display can be found [here](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf "here")

## I2C
There is 8 usable functions for I2C module
1. **void I2C_Init(void)**
2. **TransmissionStatus I2C_Start_Transmission(unsigned const char byte, unsigned const char address)**
3. **TransmissionStatus I2C_Transmit_Byte(unsigned const char byte)**
4. **TransmissionStatus I2C_Stop_Transmission(void)**
5. **TransmissionStatus I2C_Send_Byte(unsigned const char byte, unsigned const char address)**
6. **TransmissionStatus I2C_Send_Bytes(unsigned const char\* buffer, unsigned long n_Bytes, unsigned const char address)**
7. **TransmissionStatus I2C_Recive_Byte(unsigned char\* buffer, unsigned const char  address)**
8. **TransmissionStatus I2C_Recive_Bytes(unsigned char\* buffer, unsigned const char  address)**

### Start I2C
To activate I2C protocol as master device, *I2C_Init()* function must be called. This function activate third I2C module (I2C3) in the microcontroller
I2C3 module use Port D for SDA/SCL lines:
- PD0 = SCL(clock) line of I2C3 module
- PD1 = SDA(data) line of I2C3 module
I2C3 module use HS mode (High-speed mode), and can transsmit 3.33 Mbps
### Low level transmission
This option allows direct control of the I2C connection for data transfer.
This option consists of 3 functions:

1. **TransmissionStatus I2C_Start_Transmission(unsigned const char byte, unsigned const char address)**
2. **TransmissionStatus I2C_Transmit_Byte(unsigned const char byte)**
3. **TransmissionStatus I2C_Stop_Transmission(void)**

In order to transfer information using this option without any errors, you need to perform the following algorithm:

1. Start initial transmission by calling *I2C_Start_Transmission* function.
2. Transmit as much bytes, as you want by calling *I2C_Transmit_Byte* function as much, as it needs.
3. Do not forget to stop transmission by calling *I2C_Stop_Transmission* function.

### High level transmission
This option performs all the necessary operations for data transfer itself, thus you do not need to worry about starting and stopping data transfer via the I2C protocol. (as it was with low level transmission)
This option consists of 2 functions:

1. **TransmissionStatus I2C_Send_Byte(unsigned const char byte, unsigned const char address)**
2. **TransmissionStatus I2C_Send_Bytes(unsigned const char\* buffer, unsigned long n_Bytes, unsigned const char address)**

### Recive data
***!This option is not yet tested!***
This option performs all the necessary operations for data reciving.
This option consists of 2 functions:

1. **TransmissionStatus I2C_Recive_Byte(unsigned char\* buffer, unsigned const char  address)**
2. **TransmissionStatus I2C_Recive_Bytes(unsigned char\* buffer, unsigned const char  address)**

To recive data, initial buffer needs to be loaded as functions first parameter.

### TransmissionStatus Enum
This enum represents a possible set of statuses for functions associated with the I2C protocol. 
At the moment, this enum has two possible statuses:

1. I2COK = 0
2. I2CERROR = 1

## SSD1306

There is 8 usable functions for SSD1306 display
1. **SSD1306Status SSD1306_Send_Commands(unsigned const char\* buffer, unsigned long n_Bytes)**
2. **SSD1306Status SSD1306_Init(void)**
3. **SSD1306Status SSD1306_SetCursor(unsigned short newX, unsigned short newY)**
4. **SSD1306Status SSD1306_SetPixel(unsigned short x, unsigned short y)**
5. **SSD1306Status SSD1306_Draw(void)**
6. **SSD1306Status SSD1306_Write_Char(const char ch)**
7. **SSD1306Status SSD1306_Write_Str(const char\* str)**
8. **SSD1306Status SSD1306_Clear_Display(void)**

### Initialise SSD1306 Display
To activate SSD1306 display, *SSD1306_Init()* function must be called. This function activate master device I2C3 module in the microcontroller. And then function loads number of commands, that was described in the SSD1306 datasheet. Also the function will prepare a data buffer and a command buffer for further use.

### Send commands to SSD1306 display
To send number of commands to the display, *SSD1306_Send_Commands* function can be called.
Therefore, to send commands, you need to prepare an ***array*** of commands and then use function *SSD1306_Send_Commands*(***array***, *sizeof*(***array***))

### Display pixel manipulations
*SSD1306_SetPixel* function allow to write pixel to any point of display. This function only saves data in a buffer, but does not display this pixel immediately on the screen!
To display all buffer data on the display, use *SSD1306_Draw* function. To clear buffer and display, use *SSD1306_Clear_Display* function.

### Display text manipulations
To position the cursor at a certain position on the screen, you need to use *SSD1306_SetCursor* function. This function has its own coordinates, which are different from the real coordinates of the screen!
To display text on the display, you need to use *SSD1306_Write_Str* function. This function also immediately displays the text on the display by calling *SSD1306_Draw* function
