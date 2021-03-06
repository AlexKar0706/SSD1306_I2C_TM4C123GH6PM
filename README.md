# SSD1306_I2C_TM4C123GH6PM
In this program, a driver is written for the SSD1306 display with I2C protocol.
Also in the program was written a code for using the I2C module in the TM4C123HG6PM microcontroller.
Currently, the driver can print text and draw pixels to the SSD1306 displays.
Full datasheet for SSD1306 display can be found [here](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf "here")

## I2C
There is 8 usable functions for I2C module
1. **void I2C_Init(status)**
2. **TransmissionStatus I2C_StartTransmission(unsigned const char byte, unsigned const char address)**
3. **TransmissionStatus I2C_TransmitByte(unsigned const char byte)**
4. **TransmissionStatus I2C_ReciveByte(unsigned char\* buffer)**
5. **TransmissionStatus I2C_StopTransmission(void)**
6. **TransmissionStatus I2C_SendByte(unsigned const char byte, unsigned const char address)**
7. **TransmissionStatus I2C_SendBytes(unsigned const char\* buffer, unsigned long bufferSize, unsigned const char address)**
8. **TransmissionStatus I2C_ReadByte(unsigned char\* buffer,  unsigned char\* command, unsigned long commandSize, unsigned const char  address)**
9. **TransmissionStatus I2C_ReadBytes(unsigned char\* buffer, unsigned long bufferSize,  unsigned char\* command, unsigned long commandSize, unsigned const char  address)**

### Start I2C
To activate I2C protocol as master device, *I2C_Init()* function must be called. This function activate third I2C module (I2C3) in the microcontroller
I2C3 module use Port D for SDA/SCL lines:
- PD0 = SCL(clock) line of I2C3 module
- PD1 = SDA(data) line of I2C3 module
I2C3 module can use either HS mode (High-speed mode) with 80MHz PLL, that can transsmit 3.33 Mbps or use Fast mode with 16MHz MOSC, that can transsmit 300 kBps.
To use HS mode, call *I2C_Init()* function with predefined value **I2C_WITH_PLL** or use insteed **I2C_WITHOUT_PLL**
### Low level transmission
This option allows direct control of the I2C connection for data transfer.
This option consists of 4 functions:

1. **TransmissionStatus I2C_StartTransmission(unsigned const char byte, unsigned const char address)**
2. **TransmissionStatus I2C_TransmitByte(unsigned const char byte)**
3. **TransmissionStatus I2C_ReciveByte(unsigned char\* buffer)**
4. **TransmissionStatus I2C_StopTransmission(void)**

In order to transfer information using this option without any errors, you need to perform the following algorithm:

1. Start initial transmission by calling *I2C_StartTransmission* function.
2. Transmit as much bytes, as you want by calling *I2C_TransmitByte* function as much, as it needs.
3. Do not forget to stop transmission by calling *I2C_StopTransmission* function.

In order to read information using this option without any errors, you need to perform the following algorithm:

1. Start initial transmission by calling *I2C_StartTransmission* function.
2. Read as much bytes, as you want by calling *I2C_RecieveByte* function as much, as it needs.
3. Do not forget to stop transmission by calling *I2C_StopTransmission* function.

### High level transmission
This option performs all the necessary operations for data transfer itself, thus you do not need to worry about starting and stopping data transfer via the I2C protocol. (as it was with low level transmission)
This option consists of 2 functions:

1. **TransmissionStatus I2C_SendByte(unsigned const char byte, unsigned const char address)**
2. **TransmissionStatus I2C_SendBytes(unsigned const char\* buffer, unsigned long n_Bytes, unsigned const char address)**

### Read data
This option performs all the necessary operations for data reading.
This option consists of 2 functions:

8. **TransmissionStatus I2C_ReadByte(unsigned char\* buffer,  unsigned char\* command, unsigned long commandSize, unsigned const char  address)**
9. **TransmissionStatus I2C_ReadBytes(unsigned char\* buffer, unsigned long bufferSize,  unsigned char\* command, unsigned long commandSize, unsigned const char  address)**

To read data, initial buffer needs to be loaded as functions first parameter (and buffer size as function second parameter, if you want read multiple data).
You need to specify "command" parameter, which is buffer with needed commands that has to be transmitted firstly before read operation, and you need to specify size of this buffer command with "commandSize" parameter.

### TransmissionStatus Enum
This enum represents a possible set of statuses for functions associated with the I2C protocol. 
At the moment, this enum has two possible statuses:

1. I2COK = 0
2. I2CERROR = 1

## SSD1306

There is 8 usable functions for SSD1306 display
1. **SSD1306Status SSD1306_SendCommands(unsigned const char\* buffer, unsigned long n_Bytes)**
2. **SSD1306Status SSD1306_Init(unsigned short PLLoption)**
3. **SSD1306Status SSD1306_SetCursor(unsigned short newX, unsigned short newY)**
4. **SSD1306Status SSD1306_SetPixel(unsigned short x, unsigned short y)**
5. **SSD1306Status SSD1306_Draw(void)**
6. **SSD1306Status SSD1306_WriteChar(const char ch)**
7. **SSD1306Status SSD1306_WriteStr(const char\* str)**
8. **SSD1306Status SSD1306_ClearDisplay(void)**

### Initialise SSD1306 Display
To activate SSD1306 display, *SSD1306_Init()* function must be called. This function activate master device I2C3 module in the microcontroller. And then function loads number of commands, that was described in the SSD1306 datasheet.

### Send commands to SSD1306 display
To send number of commands to the display, *SSD1306_SendCommands* function can be called.
Therefore, to send commands, you need to prepare an ***array*** of commands and then use function *SSD1306_SendCommands*(***array***, *sizeof*(***array***))

### Display pixel manipulations
*SSD1306_SetPixel* function allow to write pixel to any point of display. This function only saves data in a buffer, but does not display this pixel immediately on the screen!
To display all buffer data on the display, use *SSD1306_Draw* function. To clear buffer and display, use *SSD1306_ClearDisplay* function.

### Display text manipulations
To position the cursor at a certain position on the screen, you need to use *SSD1306_SetCursor* function. This function has its own coordinates, which are different from the real coordinates of the screen!
To display text on the display, you need to use *SSD1306_WriteStr* function. This function also immediately displays the text on the display by calling *SSD1306_Draw* function